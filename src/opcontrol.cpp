#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp" // IWYU pragma: keep
#include "graphics/graphics.cpp"
#include "pros/colors.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "ladybrown.h"// IWYU pragma: keep
#include <array> // IWYU pragma: keep
#include "globals.hpp"
#include "autonomous.cpp"


void opcontrol() {

    int counter = 0;
    bool tilterState = false;
    tilter.set_value(tilterState);
    tilter2.set_value(tilterState);

    bool doinkerState = false;
    doinker.set_value(doinkerState);


    // loop forever
    while (true) {
       
        // get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX);


        //Tilter Control
        if (controller.get_digital_new_press(DIGITAL_L1)){
        tilterState = !tilterState;
        tilter.set_value(tilterState);
        tilter2.set_value(tilterState);
        }

        //Doinker Control
        if (controller.get_digital_new_press(DIGITAL_UP)){
        doinkerState = !doinkerState;
        doinker.set_value(doinkerState);
        }


        //Intake Control
        if (controller.get_digital(DIGITAL_R2)){
            intake.move_voltage(-10000);
            intake2.move_voltage(-10000);
        }else if (controller.get_digital(DIGITAL_R1)){
            intake.move_voltage(10000);
            intake2.move_voltage(10000);
        }else{
            intake.move_voltage(0);
            intake2.move_voltage(0);
        }

        //Lady Brown
        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            if (counter == 0) {
                setPosition(18);
            }
            else if (counter == 1) {
                setPosition(120);
            }
            else if (counter == 2) {
                setPosition(0);
            }
            counter ++;
            counter = counter % 3;
        }

//         //Color Sorter
//         rgb_value = opticalSensor.get_rgb();
//             //Blue
//             if (rgb_value.blue){
//                 colorPicker.set_value(true);
//                 pros::delay(800);
//                 colorPicker.set_value(false);
// ;            }

//             //Red
//             if (rgb_value.red){
//                 colorPicker.set_value(true);
//                 pros::delay(800);
//                 colorPicker.set_value(false);
//             }

        // delay to save resources
        pros::delay(25);
    }
}
