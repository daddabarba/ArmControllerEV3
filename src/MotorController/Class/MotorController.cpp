#include "MotorController.hpp"

using namespace ev3TachoController;

ev3TachoController::MotorController::MotorController(std::string port){

	DIR *tacho_dir; 	//Motors directory
	struct dirent *ent 	//Single motor sub-directory

	if( (tacho_dir = opendir(TACHO_DIR)) != NULL){

		//Id of motor matching given port
		int id = -1;

		while(id<0 && ((ent=readdir(tacho_dir) != NULL)){

			//Get current (to check) folder path
			const char *address_folder = ent->d_name + ADDRESS_FILE;
			cout << boost::format("Checking address at %s\n")%address_folder;

			//Open address file
			std::fstream address_file(address_folder);

			//If file opened successfully
			if(address_file){

				//Get address(port) of current motor
				std::string motor_port;
				address_file >> motor_port;

				//Check if it the desired one
				if(motor_port == port)
					id = std::stoi(ent->d_name.back());
			}else{

				//Could not open current address fike
				cout << boost::format("Could not open %s\n")%address_folder
			}
		}

		if(id<0)
			//No motor matched the address
			cout << boost::format("No motor found at port %s\n")%port;
		else
			//Use id based constructor
			this(id);

	}else{
		//Could not open main tacho folder
		cout << boost::format("Could not open tacho directory at %s\n")%TACHO_DIR;
	}
}


void ev3TachoController::MotorController::run(){
	this->command_i << RUN;
}

void ev3TachoController::MotorController::run(int speed){
	this->setSpeed(speed);
	this->run();
}

void ev3TachoController::MotorController::stop(int speed){
	this->command_i << STOP;
}

void ev3TachoController::MotorController::goTo(int position){
	this->command_i << RUN-TO-ABS;
}

void ev3TachoController::MotorController::goTo(int position, int speed){
	this->setSpeed(speed);
	this->goTo(position);
}

void ev3TachoController::MotorController::setSpeed(int speed){
	this->speed_i << speed;
}

void ev3TachoController::MotorController::setPosition(int position){
	this->position_i << position;
}

void ev3TachoController::MotorController::setStop(const char *action){
	this->stop_action << action;
}

void ev3TachoController::MotorController::setHold(){
	this->setStop(STOP-HOLD);
}

void ev3TachoController::MotorController::setCoast(){
	this->setStop(STOP-COAST);
}

int ev3TachoController::MotorController::getSpeed(){
	string line;

	this->speed_o >> line;
	return std::stoi(line);
}

int ev3TachoController::MotorController::getPosition(){
	string line;

	this->position_o >> line;
	return std::stoi(line);
}

const char *ev3TachoController::MotorController::getAddress(){
	const char *line;

	this->position_o >> line;
	return line;
}