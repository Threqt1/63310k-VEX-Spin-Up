/*
pid_movements.hpp exports movement functions that utilize PID
in order to be used in the autonomous routine.
*/

#include "main.h"

#pragma once

/**
 * Move forward in the Y direction for a specified
 * amount of units
 */
void moveForwardFor(QLength, MutexOdometryState *);

/**
 * Turn the bot to a specified angle
 */
void turnTo(QAngle, MutexOdometryState *);