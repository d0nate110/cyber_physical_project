#ifndef CONE_DETECTOR_HPP
#define CONE_DETECTOR_HPP

#include <opencv2/opencv.hpp>

void detectYellowCones(cv::Mat& img);
void detectBlueCones(cv::Mat& img);
void detectYellowConeAngle(cv::Mat& roiImg, std::vector<std::vector<cv::Point>>& contours);

#endif
