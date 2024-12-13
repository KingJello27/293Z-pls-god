#include "main.h" // IWYU pragma: keep
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "lemlib/chassis/trackingWheel.hpp"
#include "graphics/graphics.cpp"
#include "pros/colors.hpp" // IWYU pragma: keep
#include "pros/misc.h" // IWYU pragma: keep
#include "ladybrown.h"// IWYU pragma: keep

//controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);

// left motor group
pros::MotorGroup leftMotors({-6, -14, -18}, pros::MotorGears::blue);
// right motor group
pros::MotorGroup rightMotors({12, 15, 9}, pros::MotorGears::blue);

// vertical tracking wheel encoder
pros::Rotation vertical_encoder(16);
// horizontal tracking wheel encoder
pros::Rotation horizontal_encoder(19);
// horizontal tracking wheel
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::OLD_275, -3);
// horizontal tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::OLD_275, -0.5);

//Motors
pros::Motor hookIntake(13, pros::MotorGearset::blue);
pros::Motor rollerIntake(10, pros::MotorGearset::blue);

//pneumatics
pros::adi::DigitalOut tilter('A');
pros::adi::DigitalOut doinker('B');
// pros::adi::DigitalOut colorPicker('D');

//IMU
pros::Imu imu(1);

// drivetrain settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.5, // 12 inch track width
                              lemlib::Omniwheel::NEW_325, // using old 3.25" omnis
                              450, // drivetrain rpm is 360
                              0 // horizontal drift is 2 (for now)
);

// lateral PID controller
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              1, // integral gain (kI)
                                              50, // derivative gain (kD)
                                              0, // anti windup
                                              0, // small error range, in inches
                                              0, // small error range timeout, in milliseconds
                                              0, // large error range, in inches
                                              0, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

// sensors for odometry
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal_tracking_wheel, // horizontal tracking wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // inertial sensor
);

// @KingJello27 What are these stuff for?

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