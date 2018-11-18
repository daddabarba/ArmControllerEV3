#include "Class/MotorController.hpp"

int main()
{
	MotorController motor(0);

	motor.goTo(180, 200);

	return 0;
}