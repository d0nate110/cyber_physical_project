#ifndef CONE_DETECTOR_HPP
#define CONE_DETECTOR_HPP

#include <opencv2/opencv.hpp>

std::vector<double> detectCones(cv::Mat& img);
double detectConeAngle(cv::Mat& roiImg, cv::Point conePoint, cv::Point carPoint);
double detectConeDistance(cv::Point conePoint, cv::Point carPoint);

#endif
