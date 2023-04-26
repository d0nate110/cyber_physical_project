/*
 * Copyright (C) 2020  Christian Berger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Include the single-file, header-only middleware libcluon to create high-performance microservices
#include "cluon-complete.hpp"
#include <ctime>
// Include the OpenDLV Standard Message Set that contains messages that are usually exchanged for automotive or robotic applications 
#include "opendlv-standard-message-set.hpp"

// Include the GUI and image processing header files from OpenCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int32_t main(int32_t argc, char **argv) {
    int32_t retCode{1};
    // Parse the command line parameters as we require the user to specify some mandatory information on startup.
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
    if ( (0 == commandlineArguments.count("cid")) ||
         (0 == commandlineArguments.count("name")) ||
         (0 == commandlineArguments.count("width")) ||
         (0 == commandlineArguments.count("height")) ) {
        std::cerr << argv[0] << " attaches to a shared memory area containing an ARGB image." << std::endl;
        std::cerr << "Usage:   " << argv[0] << " --cid=<OD4 session> --name=<name of shared memory area> [--verbose]" << std::endl;
        std::cerr << "         --cid:    CID of the OD4Session to send and receive messages" << std::endl;
        std::cerr << "         --name:   name of the shared memory area to attach" << std::endl;
        std::cerr << "         --width:  width of the frame" << std::endl;
        std::cerr << "         --height: height of the frame" << std::endl;
        std::cerr << "Example: " << argv[0] << " --cid=253 --name=img --width=640 --height=480 --verbose" << std::endl;
    }
    else {
        // Extract the values from the command line parameters
        const std::string NAME{commandlineArguments["name"]};
        const uint32_t WIDTH{static_cast<uint32_t>(std::stoi(commandlineArguments["width"]))};
        const uint32_t HEIGHT{static_cast<uint32_t>(std::stoi(commandlineArguments["height"]))};
        const bool VERBOSE{commandlineArguments.count("verbose") != 0};

        // Attach to the shared memory.
        std::unique_ptr<cluon::SharedMemory> sharedMemory{new cluon::SharedMemory{NAME}};
        if (sharedMemory && sharedMemory->valid()) {
            std::clog << argv[0] << ": Attached to shared memory '" << sharedMemory->name() << " (" << sharedMemory->size() << " bytes)." << std::endl;

            // Interface to a running OpenDaVINCI session where network messages are exchanged.
            // The instance od4 allows you to send and receive messages.
            cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};

            opendlv::proxy::GroundSteeringRequest gsr;
            std::mutex gsrMutex;
            auto onGroundSteeringRequest = [&gsr, &gsrMutex](cluon::data::Envelope &&env){
                // The envelope data structure provide further details, such as sampleTimePoint as shown in this test case:
                // https://github.com/chrberger/libcluon/blob/master/libcluon/testsuites/TestEnvelopeConverter.cpp#L31-L40
                std::lock_guard<std::mutex> lck(gsrMutex);
                gsr = cluon::extractMessage<opendlv::proxy::GroundSteeringRequest>(std::move(env));
                std::cout << "lambda: groundSteering = " << gsr.groundSteering() << std::endl;
            };

            od4.dataTrigger(opendlv::proxy::GroundSteeringRequest::ID(), onGroundSteeringRequest);

            // Endless loop; end the program by pressing Ctrl-C.
            while (od4.isRunning()) {
                // OpenCV data structure to hold an image.
                cv::Mat img;

                // Wait for a notification of a new frame.
                sharedMemory->wait();

                // Lock the shared memory.
                sharedMemory->lock();
                {
                     // Copy the pixels from the shared memory into our own data structure.
                                        // Copy the pixels from the shared memory into our own data structure.
                    cv::Mat wrapped(HEIGHT, WIDTH, CV_8UC4, sharedMemory->data());
                    img = wrapped.clone();
                    
 // this resource was used partially to draw the contours for cones: https://learnopencv.com/contour-detection-using-opencv-python-c/

                    cv::Mat hsvImg;
                    cv::cvtColor(img, hsvImg, cv::COLOR_BGR2HSV);
                    
                    // Defining HSV color ranges for blue and yellow cones
                     cv::Scalar blueMin(102, 96, 40);
                     cv::Scalar blueMax(135, 255, 134);
                     cv::Scalar yellowMin(9, 0, 147);
                     cv::Scalar yellowMax(76, 255, 255);
                     
                    // Apply color thresholding to extract only blue and yellow cones
                    cv::Mat blueMask, yellowMask;
                    cv::inRange(hsvImg, blueMin, blueMax, blueMask);
                    cv::inRange(hsvImg, yellowMin, yellowMax, yellowMask);
                    // Include either blue mask or yellow mask.
                    cv::Mat coneMask = blueMask | yellowMask;

                    // find contours, using vector classes for them. 
                    std::vector<std::vector<cv::Point>> contours;
                    std::vector<cv::Vec4i> hierarchy;
                    cv::findContours(coneMask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

                    // Clone image to contoursImg
                    cv::Mat contoursImg = img.clone();
                    
                    for (size_t i = 0; i < contours.size(); i++)
                    {
                        // Compute the bounding box for the contour, which will put the cone contours in a reactangle.
                        cv::Rect bRect = cv::boundingRect(contours[i]);

                        // Filter out small boxes that might be noise
                        if (bRect.width < 20 || bRect.height < 20)
                            continue;

                        // Draw the bounding box on the image and around cones
                        cv::rectangle(contoursImg, bRect, cv::Scalar(0, 255, 0), 2);
                    }

                    // Show image
                    cv::imshow("Cones detection", contoursImg);

                }
                // TODO: Here, you can add some code to check the sampleTimePoint when the current frame was captured.
                

                //Method obtained from link provided 
                std::string frameTimeStamp = std::to_string(static_cast<__int64_t>(sharedMemory->getTimeStamp().second.seconds()) * static_cast<__int64_t>(1000*1000) + static_cast<__int64_t>(sharedMemory->getTimeStamp().second.microseconds()));

                sharedMemory->unlock();

                /*cluon::data::TimeStamp before{cluon::time::now()};
                std::time_t now = std::time(nullptr);
                now += before.seconds();
                now += before.microseconds() / 1000000;

                std::tm utc_time;
                gmtime_r(&now, &utc_time);

                std::ostringstream oss;
                oss << std::put_time(&utc_time, "%Y-%m-%d %H:%M:%S");
                std::string utc_str = oss.str();

                std::cout << "UTC time: " << utc_str << std::endl;
                */

                //Get the current time using the system clock provided by the standard library in C++
                auto now = std::chrono::system_clock::now();
                //Truncate the time point to the last second so that it stays there and not in the middle for instance
                auto now_seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
                //Get the number of seconds since the epoch
                auto value = now_seconds.time_since_epoch().count();

                //Convert the number of seconds to a UTC structure using gmtime_r()
                std::tm utc_time;
                gmtime_r(&value, &utc_time);

                std::ostringstream oss;
                oss << std::put_time(&utc_time, "%Y-%m-%dT%H:%M:%SZ");
                std::string currentUtcTime = oss.str();

                std::string finalString = "Now " + currentUtcTime + "; ts: " + frameTimeStamp + "; Reina, Oscar";


                // TODO: Do something with the frame.
                // Example: Draw a red rectangle and display image.
                cv::rectangle(img, cv::Point(100, 50), cv::Point(50, 100), cv::Scalar(50,0,255));

                cv::Point position;
                position.x = img.rows / 16;
                position.y = img.cols / 20;

                cv::Scalar color(255, 255, 255);

                cv::Scalar font = cv::Scalar(255, 255, 255);

                cv::putText(img, finalString, position, cv::QT_FONT_NORMAL, 0.5, color, 1.5);


                // If you want to access the latest received ground steering, don't forget to lock the mutex:
                {
                    std::lock_guard<std::mutex> lck(gsrMutex);
                    std::cout << "main: groundSteering = " << gsr.groundSteering() << std::endl;
                }

                // Display image on your screen.
                if (VERBOSE) {
                    cv::imshow(sharedMemory->name().c_str(), img);
                    cv::waitKey(1);
                }
            }
        }
        retCode = 0;
    }
    return retCode;
}

