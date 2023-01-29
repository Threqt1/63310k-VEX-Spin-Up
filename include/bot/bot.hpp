/*
bot.hpp includes all the header files, and registers
all the devices such as the controller, etc.
*/

#include "main.h"

#include "autonomous/odometry.hpp"
#include "autonomous/pid_movements.hpp"

#include "opcontrol/drivetrain.hpp"
#include "opcontrol/mechanisms.hpp"

#pragma once
/**
 * The main controller.
 */
extern Controller controller;

/**
 * The pointer to the chassis class.
 */
extern std::shared_ptr<ChassisController> chassis;

/**
 * The pointer to the chassis's drivetrain model.
 */
extern std::shared_ptr<SkidSteerModel> drivetrain;

/**
 * The inertial sensor.
 */
extern pros::Imu inertial;

/**
 * The left parallel wheel's encoder.
 */
extern pros::ADIEncoder leftEncoder;

/**
 * The back perpendicular wheel's encoder.
 */
extern pros::ADIEncoder backEncoder;

/**
 * The limit switch.
 */
extern ADIButton limitSwitch;

/**
 * The intake motor group.
 */
extern MotorGroup intake;

/**
 * The catapult motor.
 */
extern Motor catapult;
