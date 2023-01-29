/*
pid_movements.cpp declares functions that utilize PID via an
odometry feedback loop in order to move much more accurately.
*/

#include "main.h"

/**
 * pollOdometryState is a utility function to
 * poll the current odometry state through the
 * appropriate Mutex operations
 */
OdometryState pollOdometryState(MutexOdometryState *state)
{
    state->mutex.take();

    OdometryState currentState = state->state;

    state->mutex.give();

    return currentState;
}

void moveForwardFor(QLength length, MutexOdometryState *state)
{
}

void turnTo(QAngle angle, MutexOdometryState *state)
{
}