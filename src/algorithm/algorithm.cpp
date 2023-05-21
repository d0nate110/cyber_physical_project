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

   if(steeringAngle <= 0.19 && steeringAngle >= 0.14) {
      steeringAngle = 0.135;
   } else if (steeringAngle <= -0.19 && steeringAngle >= -0.14) {
      steeringAngle = -0.135;
   }

   if(steeringAngle <= 0.13 && steeringAngle >= 0.10) {
      steeringAngle = 0.10;
   } else if (steeringAngle <= -0.13 && steeringAngle >= -0.10) {
      steeringAngle = -0.10;
   }

   if(steeringAngle <= 0.09 && steeringAngle >= 0.07) {
      steeringAngle = 0.07;
   } else if (steeringAngle <= -0.10 && steeringAngle >= -0.07) {
      steeringAngle = -0.07;
   }

   if(steeringAngle <= 0.06 && steeringAngle >= 0.05) {
      steeringAngle = 0.05;
   } else if (steeringAngle <= -0.07 && steeringAngle >= -0.05) {
      steeringAngle = -0.05;
   }
   return steeringAngle;
}




