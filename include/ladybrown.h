#pragma once
#include "main.h" // IWYU pragma: keep

//Setters
extern void setPosition(double targetPosition);

//Initialization
extern void ladyBrownInit();

//Async Controller
extern void asyncController(void * param);

extern double getData();

extern void waitUntilSettled();

//Motor
extern pros::Motor ladyBrown;