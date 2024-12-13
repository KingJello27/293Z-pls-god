#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp" // IWYU pragma: keep
#include "pros/colors.hpp" // IWYU pragma: keep
#include "pros/misc.h" // IWYU pragma: keep
#include "ladybrown.h"// IWYU pragma: keep
#include <array> // IWYU pragma: keep
#include "globals.hpp" // IWYU pragma: keep


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

        chassis.setPose(0,0,0);
        chassis.moveToPose(0, 24, 0, 4000, {.forwards = true, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 100, .minSpeed = 60, .earlyExitRange = 0}, false);

        // //Red Left AWP
        // chassis.setPose(-58.7, 7, 0);

        // //score on alliance stake
        // intake.move_velocity(12000);
        // chassis.swingToPoint(-64, 0, DriveSide::LEFT, 1000, {.forwards = false, .direction = AngularDirection::CW_CLOCKWISE, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false);
        // chassis.waitUntilDone();
        // intake.move_velocity(-12000);
        // pros::delay(750);

        // //grab mobile goal
        // chassis.moveToPose(-58.7, 0, -90, 4000, {.forwards = true, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 0}, false);
        // chassis.waitUntilDone();
        // chassis.moveToPose(-31.5, 18, 50, 4000, {.forwards = false, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 1});
        // tilt();

        // //score first ring
        // chassis.moveToPose(-23.5, 47, 50, 4000, {.forwards = true, .horizontalDrift = 0, .lead = 0.6, .maxSpeed = 127, .minSpeed = 0, .earlyExitRange = 1});

    }else if (selectionIndex == 1){
        //Red Right AWP
        chassis.setPose(0, 0, 0);

    }else if (selectionIndex == 2){
        //Blue Left AWP
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 3){
        //Blue Right AWP
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 4){
        //Red Left Elim
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 5){
        //Red Right Elim
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 6){
        //Blue Left Elim
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 7){
        //Blue Right Elim
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 8){
        //Skills
        chassis.setPose(0, 0, 0);
        
    }
    
    
}
