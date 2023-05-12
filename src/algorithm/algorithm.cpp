#include <opencv2/opencv.hpp>
#include "algorithm.hpp"
#include <cmath>

#define MAX_STEERING_WHEEL_ANGLE 0.3
#define MIN_STEERING_WHEEL_ANGLE -0.3

#define MAX_CONE_ANGLE 90
#define MIN_CONE_ANGLE -90

#define MAX_OPENCV_DISTANCE 268.365	
#define MIN_OPENCV_DISTANCE 0

#define HIGH_PRIORITY 0.75
#define MIDDLE_PRIORITY 0.5
#define LOW_PRIORITY 0.25

//Average of turn before another one as the difference
#define AVERAGE_DIFFERENCE 0.00283774

double calculateSteeringWheelAngle(double coneAngle, double coneDistance) {

    float steeringAngle = 0.0;
    float angleWeight = LOW_PRIORITY;
    float distanceWeight = HIGH_PRIORITY;
    
    float normalizedDistance = 1 - (coneDistance / MAX_OPENCV_DISTANCE);
    float normalizedAngle = 0;

    if(coneAngle > 90.0) {
        coneAngle = 90.0;
    }
    else if(coneAngle < -90.0) {
        coneAngle = -90.0;
    }

    if (coneAngle < 0)
    {
        normalizedAngle = 1 - (-coneAngle / MAX_CONE_ANGLE);
        steeringAngle = (normalizedDistance * distanceWeight + normalizedAngle * angleWeight) * MIN_STEERING_WHEEL_ANGLE;
    }

    else{
        normalizedAngle = 1 - (coneAngle / MAX_CONE_ANGLE);
        if (normalizedAngle > 1)
        {
            normalizedAngle = 1;
        }
        steeringAngle = (normalizedDistance * distanceWeight + normalizedAngle * angleWeight) * MAX_STEERING_WHEEL_ANGLE;
    }

    if (steeringAngle > -0.03 && steeringAngle < 0.03)
    {
        steeringAngle = 0;
    }

    return steeringAngle;
}