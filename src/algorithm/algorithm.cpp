#include <opencv2/opencv.hpp>
#include "algorithm.hpp"
#include <cmath>

double calculateSteeringWheelAngle(double angularVelocityZ)
{
   // declare steeringAngle double and initialize it 0.0.
   double steeringAngle{0.0};
   // multiply angularVelocity value by 0.003, and assign it to steeringAngle variable.
   steeringAngle = angularVelocityZ * 0.003;
   
   // if the steeringAngle variable bigger than or equal to 0.2, then set the variable to 0.21.  
   if (steeringAngle >= 0.2) {
    steeringAngle = 0.21;
   }  else if (steeringAngle <= -0.2) { // On the contrary, if the steeringAngle variable is less than -0.2, then set the variable to -0.21.
    steeringAngle = -0.21;

   }


   return steeringAngle;
}




