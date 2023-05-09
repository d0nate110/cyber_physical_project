#include <opencv2/opencv.hpp>
#include "algorithm.hpp"

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

    float angleWeight = MIDDLE_PRIORITY;
    float distanceWeight = MIDDLE_PRIORITY;
    
    /*Adjust weights based on distance and angle conditions
    if (coneDistance > 200 && coneAngle < 30) {
        distanceWeight = HIGH_PRIORITY;
        angleWeight = LOW_PRIORITY;
    } else if (coneDistance < 50 && coneAngle > 60) {
        distanceWeight = LOW_PRIORITY;
        angleWeight = HIGH_PRIORITY;
    } else if (coneDistance < 50 && coneAngle < 30) {
        distanceWeight = HIGH_PRIORITY;
        angleWeight = HIGH_PRIORITY;
    } else if (coneDistance > 150 && coneAngle < 30) {
        distanceWeight = LOW_PRIORITY;
        angleWeight = MIDDLE_PRIORITY;
    }
    */
    
    
    float normalizedDistance = coneDistance / MAX_OPENCV_DISTANCE;
    float normalizedAngle = coneAngle / MAX_CONE_ANGLE;

    float steeringAngle = (normalizedDistance * distanceWeight + normalizedAngle * angleWeight) * MAX_STEERING_WHEEL_ANGLE;

    return steeringAngle;
}