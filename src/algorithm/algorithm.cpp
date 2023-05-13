#include <opencv2/opencv.hpp>
#include "algorithm.hpp"
#include <cmath>

double calculateSteeringWheelAngle(double coneAngle, double coneDistance, double angularVelocityZ)
{
   // declare steeringAngle double and initialize it 0.0.
   double steeringAngle{0.0};

   // take the value of z-axis from angularVelocityReading, multiply it by 0.002 and assign it to steeringAngle variable.
   steeringAngle = angularVelocityZ * 0.002;
   // if z-axis value is higher than 30, or lower than -30, then multiply the z value by 0.004, so that it outputs bigger numbers. Assign it to steeringAngle variable.
   if(angularVelocityZ >= 30 || angularVelocityZ <= -30) {
       steeringAngle = angularVelocityZ * 0.004;

   }
   // if the absolute value of steeringAngle (- or +) is within the range of 0.03, then set the steeringAngle variable to 0. 
   if (std::abs(steeringAngle) <= 0.03)
   {
       steeringAngle = 0;
   }
   // if the steeringAngle variable bigger than or equal to 0.2, then set the variable to 0.240888. Because the max number in a track is 0.290888. 
   if (steeringAngle >= 0.2) {
    steeringAngle = 0.240888;
   }  else if (steeringAngle <= -0.2) { // On the contrary, if the steeringAngle variable is less than -0.2, then set the variable to -0.290888.
    steeringAngle = -0.240888;
   }

   return steeringAngle;
}




