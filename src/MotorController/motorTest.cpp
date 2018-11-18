#include "Class/MotorController.hpp"

int main()
{
	ev3TachoController::MotorController motor(0);

	motor.goTo(180, 200);

	return 0;
}