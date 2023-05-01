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


void detectYellowCones(cv::Mat& img) {
    cv::Rect roi(60, 200, 485, 160);

    cv::Mat roiImg = img(roi).clone();

    cv::rectangle(img, roi, cv::Scalar(0, 0, 255), 2);
    
    cv::Mat hsvImg;
    cv::cvtColor(roiImg, hsvImg, cv::COLOR_BGR2HSV);

    cv::Mat yellowMask;

    cv::Scalar yellowMin(YELLOW_HUE_MIN, YELLOW_SATURATION_MIN, YELLOW_VALUE_MIN);
    cv::Scalar yellowMax(YELLOW_HUE_MAX, YELLOW_SATURATION_MAX, YELLOW_VALUE_MAX);
    
    cv::inRange(hsvImg, yellowMin, yellowMax, yellowMask);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    
    cv::findContours(yellowMask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
    
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

        // Create a dot in the middle of rectangle
        cv::circle(roiImg, cv::Point(centerX, centerY), 2, cv::Scalar(0, 255, 0), -1);
    }

    cv::imshow("Yellow cones detection", roiImg);
}

void detectBlueCones(cv::Mat& img) {
    cv::Rect roi(60, 200, 485, 160);

    cv::Mat roiImg = img(roi).clone();

    cv::rectangle(img, roi, cv::Scalar(0, 0, 255), 2);

    cv::Mat hsvImg;
    cv::cvtColor(roiImg, hsvImg, cv::COLOR_BGR2HSV);

    cv::Mat blueMask;

    cv::Scalar blueMin(BLUE_HUE_MIN, BLUE_SATURATION_MIN, BLUE_VALUE_MIN);
    cv::Scalar blueMax(BLUE_HUE_MAX, BLUE_SATURATION_MAX, BLUE_VALUE_MAX);

    cv::inRange(hsvImg, blueMin, blueMax, blueMask);
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(blueMask, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

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

        // Create a dot in the middle of rectangle
        cv::circle(roiImg, cv::Point(centerX, centerY), 2, cv::Scalar(0, 255, 0), -1);
    }

    cv::imshow("Blue cones detection", roiImg);
}