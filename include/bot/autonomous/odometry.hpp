/*
odometry.hpp externalizes the odometry function and
declares necessary structs used to interact with
the algorithm.
*/

#include "main.h"

#pragma once

/**
 * A struct representing the current odometry data
 * at the current tick.
 */
struct OdometryState
{
    QAngle angle{};
    QLength y{};
    QLength x{};
};

/**
 * A struct wrapping the odometry state with a mutex
 * in order to enable modification across tasks.
 */
struct MutexOdometryState
{
    pros::Mutex mutex;
    OdometryState state;
};

/**
 * The function to handle odometry, updating a given
 * state using the movements of the tracking wheels/IMU.
 */
void OdometryLoop(void *);