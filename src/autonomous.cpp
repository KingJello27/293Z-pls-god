#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp" // IWYU pragma: keep
#include "graphics/graphics.cpp" // IWYU pragma: keep
#include "pros/colors.hpp" // IWYU pragma: keep
#include "pros/misc.h" // IWYU pragma: keep
#include "ladybrown.h"// IWYU pragma: keep
#include <array> // IWYU pragma: keep
#include "globals.hpp" // IWYU pragma: keep


//Auton Selector
std::array<std::string,8> autonNames = {"Red Right AWP","Blue Left AWP","Red Left AWP","Blue Left AWP", "Red Right","Blue Left","Red Left","Blue Left"};
int selectionIndex = 0;
void leftShift(){
    selectionIndex--;
    if (selectionIndex < 0)
    selectionIndex = 7;
}
void rightShift(){
    selectionIndex++;
    if (selectionIndex > 7)
    selectionIndex = 0;
}


//Autonomous
void autonomous() {

    if (selectionIndex == 0){
        //Red Right AWP
        chassis.setPose(0, 0, 0);

    }else if (selectionIndex == 1){
        //Blue Left AWP
        chassis.setPose(0, 0, 0);

    }else if (selectionIndex == 2){
        //Red Left AWP
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 3){
        //Blue Right AWP
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 4){
        //Blue Right AWP
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 5){
        //Blue Right AWP
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 6){
        //Blue Right AWP
        chassis.setPose(0, 0, 0);
        
    }else if (selectionIndex == 7){
        //Blue Right AWP
        chassis.setPose(0, 0, 0);
        
    }
    
    
}
