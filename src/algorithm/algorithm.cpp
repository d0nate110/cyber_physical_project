#include <opencv2/opencv.hpp>
#include "algorithm.hpp"
#include <cmath>

constexpr double MAX_STEERING_WHEEL_ANGLE{0.28};
constexpr double MIN_STEERING_WHEEL_ANGLE{-0.28};

constexpr double MAX_CONE_ANGLE{90};
constexpr double MIN_CONE_ANGLE{-90};

constexpr double MAX_OPENCV_DISTANCE{268.365};
constexpr double MIN_OPENCV_DISTANCE{0};

constexpr double HIGH_PRIORITY{0.75};
constexpr double MIDDLE_PRIORITY{0.5};
constexpr double LOW_PRIORITY{0.25};

// Average of turn before another one as the difference 0.22 | 0.05 --> 0
constexpr double AVERAGE_DIFFERENCE{0.00283774};
constexpr double AVERAGE_BIG_TURNING_VALUE{0.22};

double calculateSteeringWheelAngle(double coneAngle, double coneDistance)
{
    double steeringAngle{0.0};
    double angleWeight{LOW_PRIORITY};
    double distanceWeight{HIGH_PRIORITY};

    const double normalizedDistance{1 - (coneDistance / MAX_OPENCV_DISTANCE)};
    double normalizedAngle{0};

    double clampedConeAngle{std::clamp(coneAngle, MIN_CONE_ANGLE, MAX_CONE_ANGLE)};

    if (clampedConeAngle < 0)
    {
        normalizedAngle = 1 - (-clampedConeAngle / MAX_CONE_ANGLE);
        steeringAngle = (normalizedDistance * distanceWeight + normalizedAngle * angleWeight) * MIN_STEERING_WHEEL_ANGLE;
    }
    else
    {
        normalizedAngle = 1 - (clampedConeAngle / MAX_CONE_ANGLE);
        normalizedAngle = std::min(normalizedAngle, 1.0);
        steeringAngle = (normalizedDistance * distanceWeight + normalizedAngle * angleWeight) * MAX_STEERING_WHEEL_ANGLE;
    }

    if (std::abs(steeringAngle) < 0.05)
    {
        steeringAngle = 0;
    }
    else if (steeringAngle > 1.5){
        steeringAngle = AVERAGE_BIG_TURNING_VALUE;
    }

    else if (steeringAngle < -1.5){
        steeringAngle = -AVERAGE_BIG_TURNING_VALUE;
    }

    return steeringAngle;
}
