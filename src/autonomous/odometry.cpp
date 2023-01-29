/*
odometry.cpp houses the Odometry functionality for the robot
It uses the Inertial Sensor + A parallel tracking wheel + A perpendicular tracking wheel.
*/

#include "main.h"

// Threshold at which to consider to IMU angles equal
double IMU_ANGLE_THRESHOLD = .0001;

// Convert the tracking wheel diameter and the TPR of the
// quadrature encoder, and convert that into ticks per inch
QLength trackingWheelDiameter = 2.75_in;
double ticksPerInch = static_cast<double>(360.0 / (trackingWheelDiameter.convert(inch) * 1_pi));

// Horizontal distance between the left tracking wheel
// the and tracking center
double sL = (0.25_in).convert(inch);

// Vertical distance between the back tracking wheel
// and the tracking center
double sB = (0.25_in).convert(inch);

void OdometryLoop(void *istate)
{
    // Cast the state to a Mutex Odometry State
    MutexOdometryState *state = (struct MutexOdometryState *)istate;

    // The cumulative distance travelled by the left tracking wheel
    // (Y displacement)
    double rY;

    // The cumulative distance travelled by the back tracking wheel
    // (X displacement)
    double rX;

    // The left encoder value at the last tick
    double L0;

    // The back encoder value at the last tick
    double B0;

    // The angle at the last tick
    double theta0;

    // Measure encoder values every 10 milliseconds and update
    // state values
    while (true)
    {
        // The current value of the left encoder
        double L1 = leftEncoder.get_value();

        // The current value of the back encoder
        double B1 = backEncoder.get_value();

        // The current angle (from the inertial sensor),
        // convert it to radians
        double theta1 = inertial.get_heading() * degreeToRadian;

        // The change in the left encoder's value since last reset,
        // convert the encoder tick values to distance (inches)
        double deltaL = (L1 - L0) / ticksPerInch;

        // The change in the back encoder's value since last reset,
        // convert the encoder tick values to distance (inches)
        double deltaB = (B1 - B0) / ticksPerInch;

        // The change in angle (radians)
        double deltaTheta = theta1 - theta0;

        // Calculate the distance travelled using a local coordinate
        // system (used so the math becomes easier)

        // The local Y displacement
        double localY;

        // The local X displacement
        double localX;

        // If the angle was 0, no change in orientation,
        // so the distance travelled = the distance the
        // tracking wheels travelled
        // Use a threshold to confirm equality because double
        // equality can get wonky
        if (std::abs(deltaTheta) < IMU_ANGLE_THRESHOLD)
        {
            localY = deltaL;
            localX = deltaB;
        }
        else
        {
            // Compute the rotation to apply to the coordinate system
            // to make it local
            double rotation = 2 * std::sin(deltaTheta / 2.0);

            // Apply the rotation to the tracking wheel distances to
            // find the local X and Y displacements
            localY = rotation * (deltaL / deltaTheta - sL);
            localX = rotation * (deltaB / deltaTheta + sB);
        }

        // The local coordinate system is rotated by theta/2 from the
        // actual (global) orientation

        // Compute the local orientation
        double localTheta = theta0 + (deltaTheta / 2);

        // Convert the local displacement into polar coordinates, and rotate
        // the local displacement to the global displacement

        // Get the polar radius
        double polarR = std::sqrt(localX * localX + localY * localY);

        // Get the polar angle, and rotate it by the local orientation
        // to get the global angle
        double polarA = std::atan2(localY, localX) - localTheta;

        // Calculate the global X and Y displacements
        double deltaY = std::sin(polarA) * polarR;
        double deltaX = std::cos(polarA) * polarR;

        // If any of the computed values are undefined, change them to
        // 0.

        if (isnan(deltaY))
        {
            deltaY = 0;
        }

        if (isnan(deltaX))
        {
            deltaX = 0;
        }

        if (isnan(deltaTheta))
        {
            deltaTheta = 0;
        }

        // Update the cumulative values
        rY += deltaY;
        rX += deltaX;

        // Update the odometry state by
        // taking the mutex
        state->mutex.take();

        // Convert the angle to Okapi degrees
        state->state.angle = (theta1 * radianToDegree) * degree;

        // Convert the y displacement to Okapi inches
        state->state.y = rY * inch;

        // Convert the x displacement to Okapi inches
        state->state.x = rX * inch;

        // Release the mutex
        state->mutex.give();

        // Update the last tick values
        L0 = L1;
        B0 = B1;
        theta0 = theta1;

        pros::delay(10);
    }
}