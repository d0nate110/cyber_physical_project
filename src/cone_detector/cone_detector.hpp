#ifndef CONE_DETECTOR_HPP
#define CONE_DETECTOR_HPP

#include <opencv2/opencv.hpp>

void detectCones(cv::Mat& img);
void detectYellowConeAngle(cv::Mat& roiImg, std::vector<std::vector<cv::Point>>& contours);

#endif
