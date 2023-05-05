#include <opencv2/opencv.hpp>
#include "cone_detector.hpp"

#define BLUE_HUE_MIN 102
#define BLUE_SATURATION_MIN 65
#define BLUE_VALUE_MIN 40
#define BLUE_HUE_MAX 135
#define BLUE_SATURATION_MAX 255
#define BLUE_VALUE_MAX 134

#define YELLOW_HUE_MIN 9
#define YELLOW_SATURATION_MIN 0
#define YELLOW_VALUE_MIN 147
#define YELLOW_HUE_MAX 76
#define YELLOW_SATURATION_MAX 255
#define YELLOW_VALUE_MAX 255

bool isBlueCone = false;
bool clockwise_direction = true;
bool isYellowCone = false;

double detectConeDistance(cv::Point conePoint, cv::Point carPoint) {
    double distance = cv::norm(carPoint - conePoint);
    std::cout << "Distance: " << distance << std::endl;
    return distance;
}

double detectConeAngle(cv::Mat& roiImg, std::vector<std::vector<cv::Point>>& contours, cv::Point conePoint, cv::Point carPoint) {
    
    cv::Point midScreenPoint(roiImg.cols/2, roiImg.rows/2);

    double angle = 0.0;

    //Find the largest contour (the contour with the largest area)
    double maxArea = 0.0;
    std::vector<cv::Point> largestContour;

    for (const auto& contour : contours)
    {
        double area = cv::contourArea(contour);
        if (area > maxArea)
        {
            maxArea = area;
            largestContour = contour;
        }
    }

    if (!largestContour.empty())
    {
        cv::circle(roiImg, carPoint,  2, cv::Scalar(0, 255, 0), -1);
        cv::circle(roiImg, midScreenPoint,  2, cv::Scalar(0, 255, 0), -1);
        
        cv::Moments m = cv::moments(largestContour);
        conePoint = cv::Point(m.m10/m.m00, m.m01/m.m00);
        cv::circle(roiImg, conePoint, 2, cv::Scalar(0, 255, 0), -1);

        // Draw a line from the carPoint to the conePoint
        cv::line(roiImg, carPoint, conePoint, cv::Scalar(255, 255, 0), 2);
        cv::line(roiImg, carPoint, midScreenPoint, cv::Scalar(0, 0, 255), 2);

        double dx = conePoint.x - carPoint.x;
        double dy = conePoint.y - carPoint.y;
        double coneAngle = atan2(dy, dx) * 180.0 / CV_PI;

        double dx2 = midScreenPoint.x - carPoint.x;
        double dy2 = midScreenPoint.y - carPoint.y;
        double horizontalAngle = atan2(dy2, dx2) * 180.0 / CV_PI;

        angle = coneAngle - horizontalAngle;
    }

    std::cout << "Angle: " << angle << std::endl;

    return angle;
}

std::vector<double> detectCones(cv::Mat& img) {
    
    std::vector<cv::Point> coneData;
    
    cv::Rect roi(60, 250, 485, 140);

    cv::Mat roiImg = img(roi).clone();

    //cv::rectangle(img, roi, cv::Scalar(0, 0, 255), 2);
    
    cv::Mat hsvImg;
    cv::cvtColor(roiImg, hsvImg, cv::COLOR_BGR2HSV);

    cv::Scalar blueMin(BLUE_HUE_MIN, BLUE_SATURATION_MIN, BLUE_VALUE_MIN);
    cv::Scalar blueMax(BLUE_HUE_MAX, BLUE_SATURATION_MAX, BLUE_VALUE_MAX);
    cv::Scalar yellowMin(YELLOW_HUE_MIN, YELLOW_SATURATION_MIN, YELLOW_VALUE_MIN);
    cv::Scalar yellowMax(YELLOW_HUE_MAX, YELLOW_SATURATION_MAX, YELLOW_VALUE_MAX);
    
    cv::Mat blueMask, yellowMask;
    
    cv::inRange(hsvImg, yellowMin, yellowMax, yellowMask);
    cv::inRange(hsvImg, blueMin, blueMax, blueMask);

    cv::Mat coneMask = blueMask | yellowMask;

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    
    cv::findContours(coneMask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    
    cv::Point conePoint;
    cv::Point carPoint(roiImg.cols/2, static_cast<int>(roiImg.rows/1.2));
    
    
    for (size_t i = 0; i < contours.size(); i++)
    {
        // Compute the bounding box for the contour, which will put the cone contours in a reactangle.
        cv::Rect bRect = cv::boundingRect(contours[i]);

        // Filter out small boxes that might be noise
        if (bRect.width < 17 || bRect.height < 17)
            continue;

        // Draw the bounding box on the image and around cones
        cv::rectangle(roiImg, bRect, cv::Scalar(0, 255, 0), 2);

        // Calculating the center point of the rectangle
        int centerX = bRect.x + bRect.width/2;
        int centerY = bRect.y + bRect.height/2;

        cv::Point conePoint(centerX, centerY);

        // Create a dot in the middle of rectangle
        cv::circle(roiImg, conePoint, 2, cv::Scalar(0, 0, 255), -1);
    }

    double coneAngle = detectConeAngle(roiImg, contours, conePoint, carPoint);
    double coneDistance = detectConeDistance(conePoint, carPoint);

    cv::imshow("Cone detection", roiImg);
}
