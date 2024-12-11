#include "ladybrown.h" // IWYU pragma: keep
#include "pros/rtos.hpp"
#include <iostream> // IWYU pragma: keep 
#include <ostream> // IWYU pragma: keep

double ladyBrownTargetPosition;
double kP;
double error;
double input;
bool settled = false;

//Rotation Sensor
pros::Rotation rotationSensor(2);

//Motors
pros::Motor ladyBrown(17, pros::MotorGearset::green);


double getData(){
    return input;
}

//Setters
void setPosition(double targetPosition){
    ladyBrownTargetPosition = targetPosition;
}

//Initialization
void ladyBrownInit(){
    rotationSensor.reset_position();
    ladyBrownTargetPosition = 0;
    kP = 1;
    ladyBrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

//Async Controller
void asyncController(void * param){
    while (true){
        settled = false;
        error = ladyBrownTargetPosition - (rotationSensor.get_position()/100); 
        if (error < 3 && error > -3){
            error = 0;
            settled = true;
        }
        input = kP * error;
        ladyBrown.move_voltage(input * 120);
        pros::delay(25);
    }
}

void waitUntilSettled(){
    while (settled == false){
        pros::delay(25);
    }
}

