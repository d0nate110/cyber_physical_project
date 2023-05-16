#include <opencv2/opencv.hpp>
#include "algorithm.hpp"
#include <cmath>

double calculateSteeringWheelAngle(double coneAngle, double coneDistance, double angularVelocityZ)
{
    double steeringAngle{0.0};


    steeringAngle = angularVelocityZ * 0.002;

    if(angularVelocityZ >= 20 || angularVelocityZ <= -20) {
        steeringAngle = angularVelocityZ * 0.003;


    }

    if (std::abs(steeringAngle) <= 0.03)
    {
        steeringAngle = 0;
    }


    return steeringAngle;
}




