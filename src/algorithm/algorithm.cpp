#include <opencv2/opencv.hpp>
#include "algorithm.hpp"

#define MAX_STEERING_WHEEL_ANGLE 0.3
#define MIN_STEERING_WHEEL_ANGLE -0.3

#define MAX_CONE_ANGLE 90
#define MIN_CONE_ANGLE -90

#define MAX_OPENCV_DISTANCE 268.365	
#define MIN_OPENCV_DISTANCE 0

#define AVERAGE_DIFFERENCE 0.00283774

double calculateSteeringWheelAngle(double coneAngle, double coneDistance) {
    
    float normalizedDistance = coneDistance / MAX_OPENCV_DISTANCE;
    float normalizedAngle = coneAngle / MAX_CONE_ANGLE;

    float steeringAngle = (normalizedDistance / 2 + normalizedAngle / 2) * MAX_STEERING_WHEEL_ANGLE;

    return steeringAngle;
}