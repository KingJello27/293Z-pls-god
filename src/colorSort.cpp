#include "colorSort.hpp"

//Config
pros::Optical colorSensor(1);
pros::adi::DigitalOut colorPiston('C');

int colorIndex;

//Initialize
void colorSortInit(){
    colorPiston.set_value(false);
}

//Blue Side Detetcion (detecting red) when color index == 0
void blueSideDetection(){
    if ((colorSensor.get_hue() >= 0 && colorSensor.get_hue() <= 30) || (colorSensor.get_hue() >= 330 && colorSensor.get_hue() <= 360)){
        pros::delay(250);
        colorPiston.set_value(true);
        pros::delay(500);
    }
}

//Red Side Detetcion (detecting blue) when color index == 1
void redSideDetection(){
    if ((colorSensor.get_hue() >= 200 && colorSensor.get_hue() <= 250)){
        pros::delay(250);
        colorPiston.set_value(true);
        pros::delay(500);
    }
}

//Async Function
void colorSortAsyncController(void * param){
    while (true){

        if (colorIndex == 0){
            blueSideDetection();
        }else if (colorIndex == 1){
            redSideDetection();
        }
        
    }
}
