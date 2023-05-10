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

    /*float angleWeight = MIDDLE_PRIORITY;
    float distanceWeight = MIDDLE_PRIORITY;
    
    float normalizedDistance = coneDistance / MAX_OPENCV_DISTANCE;
    float normalizedAngle = coneAngle / MAX_CONE_ANGLE;

    //FORMULA1
    //float steeringAngle = (normalizedDistance * distanceWeight + normalizedAngle * angleWeight) * MAX_STEERING_WHEEL_ANGLE;

    //FORMULA2
    float steeringAngle = (normalizedDistance * 0.1 +  normalizedAngle * 0.1 + 0.173450638 * 0.8) * MAX_STEERING_WHEEL_ANGLE;

    //FORMULA3
    float steeringAngle = 0;
    if(coneAngle < 0){
        steeringAngle = (normalizedDistance * 0.1 +  normalizedAngle * 0.1 + -0.052035191 * 0.8) * MAX_STEERING_WHEEL_ANGLE;
    }
    else {
        steeringAngle = (normalizedDistance * 0.1 +  normalizedAngle * 0.1 + 0.052035191 * 0.8) * MAX_STEERING_WHEEL_ANGLE;
    }
    */
    

    float angleWeight = MIDDLE_PRIORITY;
    float distanceWeight = MIDDLE_PRIORITY;

    float normalizedDistance = coneDistance / MAX_OPENCV_DISTANCE;
    float normalizedAngle = coneAngle / MAX_CONE_ANGLE;

    return steeringAngle;
}