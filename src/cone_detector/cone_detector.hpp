#ifndef CONE_DETECTOR_HPP
#define CONE_DETECTOR_HPP

#include <opencv2/opencv.hpp>

class ConeDetector {

public:
    ConeDetector() = default;  // Constructor
    ~ConeDetector() = default; // Destructor

    // Method declarations
    void detectYellowCones(cv::Mat& img);
    void detectBlueCones(cv::Mat& img);
};

#endif
