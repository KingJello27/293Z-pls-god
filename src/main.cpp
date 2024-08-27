#include "main.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
#include "graphics/graphics.cpp"


// left motor group
pros::MotorGroup left_motor_group({-1, -6, -20}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup right_motor_group({12, 15, 16}, pros::MotorGears::blue);

// drivetrain settings
lemlib::Drivetrain drivetrain(&left_motor_group, // left motor group
                              &right_motor_group, // right motor group
                              12, // 12 inch track width
                              lemlib::Omniwheel::OLD_325, // using old 3.25" omnis
                              450, // drivetrain rpm is 360
                              2 // horizontal drift is 2 (for now)
);

//imu
pros::Imu imu(10);

//Motors
pros::Motor intake(7, pros::MotorGearset::green);
pros::Motor lift(8, pros::MotorGearset::green);

//pneumatics
pros::adi::DigitalOut tilt1('A');
pros::adi::DigitalOut tilt2('B');
pros::adi::DigitalOut grm('C');

// odometry settings
lemlib::OdomSensors sensors(nullptr, // vertical tracking wheel 1, set to null
                            nullptr, // vertical tracking wheel 2, set to nullptr as we are using IMEs
                            nullptr, // horizontal tracking wheel 1
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
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
    chassis.calibrate(); // calibrate sensors
    // print position to brain screen
    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // delay to save resources
            pros::delay(20);
        }
    });

}


void disabled() {}


void competition_initialize() {}


void autonomous() {}


pros::Controller controller(pros::E_CONTROLLER_MASTER);

void opcontrol() {

    bool tilterState = false;
    tilt1.set_value(tilterState);
    tilt2.set_value(tilterState);

    bool grmState = false;
    grm.set_value(grmState);

    // loop forever
    while (true) {
       
        // get left y and right x positions
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

        // move the robot
        chassis.arcade(leftY, rightX);

        //Shift Key
        if (controller.get_digital(DIGITAL_L1)){

            //Lift Control
            if (controller.get_digital(DIGITAL_R2)){
                lift.move_voltage(12000);
            }else if (controller.get_digital(DIGITAL_R1)){
                intake.move_voltage(-12000);
            }else{
                lift.move_voltage(0);
            }

            //Goal Rush Mech Control
            if (controller.get_digital_new_press(DIGITAL_L2)){
            grmState = !grmState;
            grm.set_value(grmState);
            }

        }

        //Tilter Control
        if (controller.get_digital_new_press(DIGITAL_L2)){
        tilterState = !tilterState;
        tilt1.set_value(tilterState);
        tilt2.set_value(tilterState);
        }

        // //Goal Rush Mech Control
        // if (controller.get_digital_new_press(DIGITAL_L2)){
        // grmState = !grmState;
        // grm.set_value(grmState);
        // }

        //Intake Control
        if (controller.get_digital(DIGITAL_R2)){
            intake.move_voltage(12000);
        }else if (controller.get_digital(DIGITAL_R1))
            intake.move_voltage(-12000);
        else{
            intake.move_voltage(0);
        }

        // //Lift Control
        // if (controller.get_digital(DIGITAL_R2)){
        //     lift.move_voltage(12000);
        // }else if (controller.get_digital(DIGITAL_R1))
        //     intake.move_voltage(-12000);
        // else{
        //     lift.move_voltage(0);
        // }
        
        // delay to save resources
        pros::delay(25);
    }
}