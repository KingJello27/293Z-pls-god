#pragma once
#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/adi.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp" // IWYU pragma: keep
#include "pros/colors.hpp" // IWYU pragma: keep
#include "pros/misc.h" // IWYU pragma: keep
#include "ladybrown.h"// IWYU pragma: keep
#include "pros/motor_group.hpp"

//Chassis
extern lemlib::Chassis chassis;

//Controller
extern pros::Controller controller;

//Motors
extern pros::Motor hookIntake,rollerIntake;
extern pros::Motor motors[8];
extern pros::MotorGroup leftMotors, rightMotors;

//IMU
extern pros::IMU imu;

//Pneumatics
extern pros::adi::DigitalOut doinker, tilter;
