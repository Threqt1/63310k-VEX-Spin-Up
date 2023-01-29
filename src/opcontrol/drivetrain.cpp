/*
drivetrain.cpp implements the task that handles controller inputs
and translates them to drivetrain movements.
*/

#include "main.h"

void DrivetrainLoop(void *_)
{
    while (true)
    {
        // Move the drivetrain based on the current controller
        // values
        drivetrain->arcade(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightX));

        pros::delay(20);
    }
}