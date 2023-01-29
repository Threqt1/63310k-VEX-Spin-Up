/*
mechanisms.cpp serves to handle inputs to the manipulators
such as the catapult and intake.
*/

#include "main.h"

void MechanismsLoop(void *_)
{
    while (true)
    {
        /* Catapult */

        /*
            Keep catapult moving down if:
            - A is pressed (until limit switch is active)
            - B is pressed (launch button)
            Else:
            - Keep it moving up to counter natural downward
              movement
        */
        if (controller.getDigital(ControllerDigital::B) || controller.getDigital(ControllerDigital::A) && !limitSwitch.isPressed())
        {
            catapult.moveVoltage(12000);
        }
        else
        {
            catapult.moveVoltage(300);
        }

        /* Intake */

        /*
            Keep intake moving forward if:
                - R2 is being pressed
            Keep intake moving backward if:
                - R1 is being pressed
            Else:
                - Stop the intake
        */
        if (controller.getDigital(ControllerDigital::R2))
        {
            intake.moveVoltage(8500);
        }
        else if (controller.getDigital(ControllerDigital::R1))
        {
            intake.moveVoltage(-8500);
        }
        else
        {
            intake.moveVoltage(0);
        }

        pros::delay(20);
    }
}