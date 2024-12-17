#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp" // IWYU pragma: keep
#include "pros/colors.hpp" // IWYU pragma: keep
#include "pros/misc.h" // IWYU pragma: keep
#include "ladybrown.h"// IWYU pragma: keep
#include <array> // IWYU pragma: keep
#include "globals.hpp" // IWYU pragma: keep
#include "colorSort.hpp"


//Auton Selector
std::array<std::string,9> autonNames = {"Red Left AWP","Red Right AWP","Blue Left AWP","Blue Right AWP", "Red Left Elim","Red Right Elim","Blue Left Elim","Blue Right Elim", "Skills"};
int selectionIndex = 0;
void leftShift(){
    selectionIndex--;
    if (selectionIndex < 0)
    selectionIndex = 8;
}
void rightShift(){
    selectionIndex++;
    if (selectionIndex > 8)
    selectionIndex = 0;
}

void tilt(){
    tilter.set_value(true);
}

void untilt(){
    tilter.set_value(false);
}

/*Basic Movement Functions:

chassis.setPose(0, 0, 0); - set pose
resetLocalPosition() - reset pose
chassis.waitUntilDone(); - waits for drive to complete
chassis.turnToPoint(45, -45, 1000, {.forwards = false, .direction = AngularDirection::AUTO, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false); - turn function
chassis.swingToPoint(45, -45, DriveSide::RIGHT, 1000, {.forwards = true, .direction = AngularDirection::AUTO, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false); - swing function
chassis.moveToPose(20, 15, 90, 4000, {.forwards = false, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false); - drive function
chassis.moveToPoint(20, 15, 4000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false); - secondary drive function

*/


//Autonomous
void autonomous() {

    if (selectionIndex == 0){
        colorIndex = 1;

        //PID Tuning
        chassis.setPose(0, 0, 0);
        chassis.moveToPose(0, 24, 0, 4000, {.forwards = true, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 0}, false);

        // //Red Left AWP
        // chassis.setPose(-58.7, 8, 90);

        // //score on alliance stake
        // chassis.swingToPoint(-52, 0, DriveSide::LEFT, 1000, {.forwards = true, .direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false);
        // chassis.waitUntilDone();
        // chassis.moveToPose(-66, 0, 0, 4000, {.forwards = false, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false);
        // intake.move_velocity(12000);
        // pros::delay(750);

        // //grab mobile goal
        // chassis.moveToPose(-58.7, 0, 0, 4000, {.forwards = true, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false);
        // chassis.waitUntilDone();
        // chassis.moveToPose(-31, 19, -40, 4000, {.forwards = false, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 1});
        // tilt();

        // //score first ring
        // intake.move_velocity(12000);
        // chassis.turnToPoint(-24.5, 32.5, 1000, {.forwards = true, .direction = AngularDirection::AUTO, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false);
        // chassis.waitUntilDone();
        // chassis.moveToPoint(-24.5, 32.5, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 2});
        // chassis.moveToPose(-8, 41, 0, 4000, {.forwards = true, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0});
        // chassis.waitUntilDone();

        // //score second ring
        // chassis.swingToPoint(-24.5, 32.5, DriveSide::RIGHT, 1000, {.forwards = false, .direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false);
        // chassis.waitUntilDone();

        // //score second ring
        // chassis.moveToPoint(-23.5, 47, 4000, {.forwards = true, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 1});
        // chassis.moveToPose(-7, 50, 0, 4000, {.forwards = true, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0});
        // chassis.waitUntilDone();

        // //touch the pole
        // chassis.moveToPoint(-23.5, 47, 4000, {.forwards = false, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 3});
        // chassis.turnToPoint(-24, 4, 1000, {.forwards = true, .direction = AngularDirection::CCW_COUNTERCLOCKWISE, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false);
        // chassis.waitUntilDone();
        // chassis.moveToPose(-24, 4, 90, 4000, {.forwards = true, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 3});




    
    }else if (selectionIndex == 1){
        colorIndex = 1;

        //Red Right AWP
        chassis.setPose(0, 0, 0);

    }else if (selectionIndex == 2){
        colorIndex = 0;

        //Blue Left AWP
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 3){
        colorIndex = 0;

        //Blue Right AWP
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 4){
        colorIndex = 1;

        //Red Left Elim
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 5){

        colorIndex = 1;

        //Red Right Elim
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 6){
        colorIndex = 0;

        //Blue Left Elim
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 7){
        colorIndex = 0;

        //Blue Right Elim
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 8){

        //Skills
        chassis.setPose(0, 0, 0);
        
    }
    
    
}
