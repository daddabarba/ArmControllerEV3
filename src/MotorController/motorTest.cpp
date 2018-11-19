#include "Class/MotorController.hpp"

#include <unistd.h>

int main()
{
	ev3TachoController::MotorController motor(0);

	motor.setHold();
	motor.makeStep(180, 200);

	return 0;
}