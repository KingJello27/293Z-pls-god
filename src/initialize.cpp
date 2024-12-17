#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp" // IWYU pragma: keep
#include "pros/colors.hpp" // IWYU pragma: keep
#include "pros/misc.h" // IWYU pragma: keep
#include "ladybrown.h"// IWYU pragma: keep
#include <array> // IWYU pragma: keep
#include "globals.hpp" // IWYU pragma: keep
#include "autonomous.hpp"
#include "colorSort.hpp"


void initialize() {
    pros::lcd::initialize(); // initialize brain screen

    pros::lcd::register_btn0_cb(leftShift);
    pros::lcd::register_btn2_cb(rightShift);

    chassis.calibrate(); // calibrate sensor
    imu.reset();
    
    ladyBrownInit();

    manual = false;

    colorSortInit();

    pros::Task ladyBrownTask(asyncController);
    pros::Task colorSortTask(colorSortAsyncController);

    // print position to brain screen
    // pros::Task screen_task([&]() {
    //     while (true) {
    //         // print robot location to the brain screen
    //         pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
    //         pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
    //         pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
    //         pros::lcd::print(3, "Auton Selection: %s", autonNames[selectionIndex]);
    //         // delay to save resources
    //         pros::delay(20);
    //     }
    // });

}

void disabled() {}

void competition_initialize() {}