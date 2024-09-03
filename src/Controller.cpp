#include "Controller.h"
#include <iostream>
#include "constants.h"

Controller::Controller()
{

}

Controller::~Controller()
{

}

bool Controller::MoveTo(float py, float vy, float targetAltitude)
{
    long double PID = Kp*(targetAltitude - py) - Kd*vy;
    return PID > 0;
}


/*
1) Turn thruster on when below a certain threshold when starting at an initial height h0
2) Create a controller that uses acceleration, velocity, and position

BRAINSTORMING
- if we use current height vs target height (0) as our error,
    - derivative = velocity

- if we use curr vel vs target val as error:
    - derivative = accel

*/