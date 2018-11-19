#ifndef MOTORCONTROLLER_H
	#define MOTORCONTROLLER_H
#endif

#include <iostream>
#include <fstream>

#include <string>
#include <sstream>
//#include <boost>

namespace ev3TachoController{

	//Interface files paths
	const std::string 
			TACHO_PATH 		= "/sys/class/tacho-motor/motor",

			SPEED_I_FILE 	= "/speed_sp",
			POSITION_I_FILE	= "/position_sp",
			STOP_I_FILE		= "/stop_action",
			COMMAND_FILE 	= "/command",

			SPEED_O_FILE	= "/speed",
			POSITION_O_FILE	= "/position",
			ADDRESS_FILE	= "/address";

	//Commands
	const std::string
			RUN				= "run-forever",
			RUN_TO_ABS		= "run-to-abs-pos",
			RUN_TO_REL		= "run-to-rel-pos",

			STOP_COAST		= "coast",
			STOP_HOLD		= "hold",
			STOP 			= "stop";

	//Max number of motors
	const int MAX_MOTORS = 8;

	int findMotor(std::string port);

	class MotorController{

		public:

			//Constructors
			MotorController(std::string port);
			MotorController(int id);

			MotorController operator= (MotorController& mc);
			MotorController operator= (MotorController mc);

			//Destructor
			~MotorController();

			//Controller functions
			void run();
			void run(int speed);

			void stop();

			void goTo();
			void goTo(int position);
			void goTo(int position, int speed);

			void makeStep();
			void makeStep(int size);
			void makeStep(int size, int speed);

			void setSpeed(int speed);
			void setPosition(int position);

			void setStop(std::string action);
			void setHold();
			void setCoast();

			int getSpeed();
			int getPosition();
			std::string getAddress();

		private:

			//Fields

			//Motor file
			//Motor_path path;

			//Motor inpus
			std::fstream 
					speed_i,
					position_i,
					stop_action,
					command_i;

			//Motor readings
			std::fstream
					address,
					speed_o,
					position_o;

			//Delete copy from constant reference
			MotorController(const MotorController& mc) 				= delete;
			MotorController operator= (const MotorController& mc) 	= delete;
	};
}