#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include "data_handler.hpp"
#include <opencv2/opencv.hpp>

class Algorithm {

public:
    Algorithm() = default;  // Constructor
    ~Algorithm() = default; // Destructor

    //Method definitions
    void detectCones(const cv::Mat& frame); 
    // Add any additional public methods or properties here

private:

};

#endif