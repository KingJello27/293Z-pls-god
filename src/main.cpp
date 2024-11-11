#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
#include "graphics/graphics.cpp"
#include "pros/colors.hpp" // IWYU pragma: keep
#include "pros/misc.h"
#include "ladybrown.h"// IWYU pragma: keep
#include <array>


// left motor group
pros::MotorGroup left_motor_group({-13, -14, -20}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup right_motor_group({11, 12, 19}, pros::MotorGears::blue);

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              11.5, // 12 inch track width
                              lemlib::Omniwheel::OLD_325, // using old 3.25" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

//IMU
pros::Imu imu(16);

//Optical Sensor
// pros::Optical opticalSensor(5);
// pros::c::optical_rgb_s_t rgb_value;

// //Rotation Sensor
// pros::Rotation rotationSensor(3);

// // horizontal tracking wheel encoder
// pros::Rotation horizontal_encoder(8);

// //Motors
pros::Motor intake(18, pros::MotorGearset::blue);
// pros::Motor ladyBrown1(5, pros::MotorGearset::green);
// pros::Motor ladyBrown2(-4, pros::MotorGearset::green);



//pneumatics
pros::adi::DigitalOut tilter('B');
pros::adi::DigitalOut doinker('A');
// pros::adi::DigitalOut grm('C');
// pros::adi::DigitalOut colorPicker('D');

//Auton Selector
std::array<std::string,4> autonNames = {"Red Right AWP","Blue Left AWP","Red Left AWP","Blue Left AWP"};
int selectionIndex = 0;
void leftShift(){
    selectionIndex--;
    if (selectionIndex < 0)
    selectionIndex = 3;
}
void rightShift(){
    selectionIndex++;
    if (selectionIndex > 3)
    selectionIndex = 0;
}

// // horizontal tracking wheel
// lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::OLD_275, -5.75);


// odometry settings
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(8, // proportional gain (kP)
                                              0.5, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)s
);

// angular PID controller
lemlib::ControllerSettings angular_controller(1.5, // proportional gain (kP)
                                              0.5, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttle_curve(3, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1.019 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(3, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.019 // expo curve gain
);

// create the chassis
lemlib::Chassis chassis(drivetrain,
                        lateral_controller,
                        angular_controller,
                        sensors,
                        &throttle_curve, 
                        &steer_curve
);


void initialize() {
    pros::lcd::initialize(); // initialize brain screen

    pros::lcd::register_btn0_cb(leftShift);
    pros::lcd::register_btn2_cb(rightShift);

    chassis.calibrate(); // calibrate sensor
    imu.reset();
    
    ladyBrownInit();

    pros::Task ladyBrownTask(asyncController);

    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            pros::lcd::print(3, "Auton Selection: %s", autonNames[selectionIndex]);
            // delay to save resources
            pros::delay(20);
        }
    });

}


void disabled() {}


void competition_initialize() {}

// //Lady Brown
// const int start = 0;  
// const int receive = 22; 
// const int score = 145; 

// void setPosition(int targetPosition) {
//     ladyBrown1.move_absolute(targetPosition, 100);
//     ladyBrown2.move_absolute(targetPosition, 100);
//     // while (abs(rotationSensor.get_position() - targetPosition) > 5) {
//     //     pros::delay(20);
//     // }
//     pros::delay(50);
// }


// int currentPosition = 1;

// void autonLadyBrown (){

//     rotationSensor.get_position();

//         if (currentPosition == 0) {
//                 setPosition(start);
//                 currentPosition = 1;
//             } else if (currentPosition == 1) {
//                 setPosition(receive);
//                 currentPosition = 2;
//             } else if (currentPosition == 2) {
//                 setPosition(score);
//                 currentPosition = 0;
//             }
// }

//chassis.moveToPose(0, 24, 0, 5000, {.maxSpeed = 80, .minSpeed = 40});
// chassis.turnToHeading(90, 2000);
// chassis.waitUntilDone();

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
    
}
    
}


pros::Controller controller(pros::E_CONTROLLER_MASTER);



void opcontrol() {

    int counter = 0;
    bool tilterState = false;
    tilter.set_value(tilterState);

    bool doinkerState = false;
    doinker.set_value(doinkerState);

    // bool grmState = false;
    // grm.set_value(grmState);

    // //Lady Brown
    // const int start = 0;  
    // const int receive = 22; 
    // const int score = 145; 
    // rotationSensor.reset_position();
    // int currentPosition = 1;


    // loop forever
    while (true) {
       
        // get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX);

        // //Rotation Sensor -> Lady Brown Motor
        // rotationSensor.get_position();
        

        // //Shift Key
        // if (controller.get_digital(DIGITAL_L1)){

        //     // //Intake Supressor
        //     // intake.move_voltage(0);

        //     // //Tilter Supressor
        //     // tilt1.set_value(false);
        //     // tilt2.set_value(false);

        //     //Lift Control
        //     // if (controller.get_digital_new_press(DIGITAL_R1)){
                
        //     // }
            

        //     // //Goal Rush Mech Control
        //     // if (controller.get_digital_new_press(DIGITAL_L2)){
        //     // grmState = !grmState;
        //     // grm.set_value(grmState);
        //     // }
        // }

        //Tilter Control
        if (controller.get_digital_new_press(DIGITAL_L1)){
        tilterState = !tilterState;
        tilter.set_value(tilterState);
        }

        //Doinker Control
        if (controller.get_digital_new_press(DIGITAL_UP)){
        doinkerState = !doinkerState;
        doinker.set_value(doinkerState);
        }

        // //Goal Rush Mech Control
        // if (controller.get_digital_new_press(DIGITAL_L2)){
        // grmState = !grmState;
        // grm.set_value(grmState);
        // }

        //Intake Control
        if (controller.get_digital(DIGITAL_R2)){
            intake.move_voltage(-10000);
        }else if (controller.get_digital(DIGITAL_R1))
            intake.move_voltage(10000);
        else{
            intake.move_voltage(0);
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
