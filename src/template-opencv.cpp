/*
* Copyright (C) 2020  Christian Berger
*
* Modified by Oscar Reina Gustafsson on 4th of May
* Modified by Anton Golubenko on 15th of May
* Modified by Dragos Florinel Isar on 21st of May
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
#include <cstdlib>


// Include the GUI and image processing header files from OpenCV
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "cone_detector/cone_detector.hpp"
#include "algorithm/algorithm.hpp"
#include "utility"

int32_t main(int32_t argc, char **argv) {
  
   std::vector<double> coneData;
   coneData.resize(2);

    bool display_provided = false;
  
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

        // Checks whether the DISPLAY argument is provided or not by accessing the environment variables
        const char* display_env = std::getenv("DISPLAY");
        if (display_env != nullptr){
            display_provided = true;
        }

     // Create an OD4Session object with the specified command line argument for the CID
    cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};

    // Create a unique pointer to a SharedMemory object with the specified NAME
    std::unique_ptr<cluon::SharedMemory> sharedMemory{new cluon::SharedMemory{NAME}};
    
    // Check if the shared memory object is valid and print information about it if valid
    if (sharedMemory && sharedMemory->valid()) {
    std::clog << argv[0] << ": Attached to shared memory '" << sharedMemory->name() << " (" << sharedMemory->size() << " bytes)." << std::endl;

    // Create GroundSteeringRequest and AngularVelocityReading objects
    opendlv::proxy::GroundSteeringRequest gsr;
    opendlv::proxy::AngularVelocityReading avr;

    // Create mutexes for thread safety
    std::mutex gsrMutex;
    std::mutex avrMutex;

    // Define lambda functions for handling data received from OD4Session
    auto onGroundSteeringRequest = [&gsr, &gsrMutex](cluon::data::Envelope &&env) {
        std::lock_guard<std::mutex> lck(gsrMutex);
        gsr = cluon::extractMessage<opendlv::proxy::GroundSteeringRequest>(std::move(env));
    };
    auto onAngularVelocityReading = [&avr, &avrMutex](cluon::data::Envelope &&env) {
        std::lock_guard<std::mutex> lck2(avrMutex);
        avr = cluon::extractMessage<opendlv::proxy::AngularVelocityReading>(std::move(env));
    };

    // Register the lambda functions as data triggers for the corresponding message types
    od4.dataTrigger(opendlv::proxy::GroundSteeringRequest::ID(), onGroundSteeringRequest);
    od4.dataTrigger(opendlv::proxy::AngularVelocityReading::ID(), onAngularVelocityReading);

    // Rest of the code

           // Endless loop; end the program by pressing Ctrl-C.
           while (od4.isRunning()) {
               // OpenCV data structure to hold an image.
               cv::Mat img;
               double angularVZ = 0.0;

               // Wait for a notification of a new frame.
               sharedMemory->wait();

               // Lock the shared memory. Modified on the 4th and 15th of May
               sharedMemory->lock();
               {
                   std::pair<unsigned long long int, double> tempOut;
                   // Copy the pixels from the shared memory into our own data structure.
                   cv::Mat wrapped(HEIGHT, WIDTH, CV_8UC4, sharedMemory->data());
                   img = wrapped.clone();
                   
                   //Signature is changed in order to check for VERBOSE tag as well as presence of DISPLAY source
                   //Retrieving relevant cone angle and cone distance information from the img/frame
                   coneData = detectCones(img, VERBOSE, display_provided);

                   //Retrieve z-axis measure for angular velocity
                    angularVZ = avr.angularVelocityZ();

                    //Calculate steering wheel angle according to the angular velocity
                   double steeringAngle = calculateSteeringWheelAngle(angularVZ);

                   //unsigned long long int frameTimeStamp = static_cast<unsigned long long int>(cluon::time::toMicroseconds(sharedMemory->getTimeStamp().second));
                   std::cout << "group_11;" << cluon::time::toMicroseconds(sharedMemory->getTimeStamp().second) << ";" << steeringAngle << std::endl;
               }

               sharedMemory->unlock();

               // Display image on your screen.
              
               if (VERBOSE) {
                   //cv::imshow(sharedMemory->name().c_str(), img);
                   cv::waitKey(1);
               }
              
           }
       }
       retCode = 0;
   }
   return retCode;
}






