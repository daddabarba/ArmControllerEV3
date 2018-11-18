#ifndef MOTORCONTROLLER_H
	#define MOTORCONTROLLER_H
#endif

#include <iostream>
#include <fstream>

#include <string>
#include <boost>

namespace ev3TachoController{

	//Interface files paths
	const char *
			TACHO_PATH 		= "/sys/class/tacho-motor/motor%d/",

			SPEED_I_FILE 	= "speed_sd",
			POSITION_I_FILE	= "position_sd",
			STOP_I_FILE		= "stop_action",
			COMMAND_FILE 	= "command",

			SPEED_O_FILE	= "speed",
			POSITION_O_FILE	= "position",
			ADDRESS_FILE	= "address",

			SPEED_I_PATH 	= TACHO_PATH + SPEED_I_FILE,
			POSITION_I_PATH	= TACHO_PATH + POSITION_I_FILE,
			STOP_I_PATH		= TACHO_PATH + STOP_I_FILE,
			COMMAND_PATH 	= TACHO_PATH + COMMAND_FILE,

			SPEED_O_PATH	= TACHO_PATH + SPEED_O_FILE,
			POSITION_O_PATH	= TACHO_PATH + POSITION_O_FILE,
			ADDRESS_PATH	= TACHO_PATH + ADDRESS_FILE;

	//Commands
	const char *
			RUN				= "run-forever",
			RUN-TO-ABS		= "run-to-abs-pos",
			RUN-TO-REL		= "run-to-rel-pos",

			STOP-COAST		= "coast",
			STOP-HOLD		= "hold",
			STOP 			= "stop";

	class MotorController{

		public:

			//Constructors
			MotorController(std::string port);
			MotorController(int id) : 
							command_i	(boost::format(COMMAND_PATH)%id, std::fstream::out),
							speed_i 	(boost::format(SPEED_I_PATH)%id, std::fstream::out),
							position_i 	(boost::format(POSITION_I_PATH)%id, std::fstream::out),
							stop_action (boost::format(STOP_I_PATH)%id, std::fstream::out),
							address 	(boost::format(ADDRESS_PATH)%id, std::fstream::in),
							speed_o 	(boost::format(SPEED_O_PATH)%id, std::fstream::in),
							position_o 	(boost::format(POSITION_O_PATH)%id, std::fstream::in)
							{}

			MotorController operator= (MotorController& mc);
			MotorController operator= (MotorController mc);

			//Destructor
			~MotorController();

			//Controller functions
			void run();
			void run(int speed);

			void stop();

			void goTo(int position);
			void goTo(int position, int speed);

			void setSpeed(int speed);
			void setPosition(int position);

			void setStop(const char *action);
			void setHold();
			void setCoast();

			int getSpeed();
			int getPosition();
			const char *getAddress();

		private:

			//Fields

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