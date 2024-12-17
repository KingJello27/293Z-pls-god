#pragma once
#include "main.h" // IWYU pragma: keep

//Sensor
extern pros::Optical colorSensor;

//Piston
extern pros::adi::DigitalOut colorPiston;

//Initialize
extern void colorSortInit();

//Detection Functions
extern void blueSideDetection(), redSideDetection();

//Async Function
extern void colorSortAsyncController();

//Color Index
extern int colorIndex;