#include "MotorController.hpp"

#include <dirent.h>
#include <iostream>

using namespace ev3TachoController;

ev3TachoController::MotorController::~MotorController(){

	this->command_i.close();
	this->speed_i.close();
	this->position_i.close();
	this->stop_action.close();
	this->speed_o.close();
	this->position_o.close();
	this->address.close();
}

int ev3TachoController::findMotor(std::string port){

	for(int m_id=0; m_id<MAX_MOTORS; m_id++){

		//Open address file
		std::fstream address_file(TACHO_PATH + std::to_string(m_id) + ADDRESS_FILE);

		//Get addres
		std::string address;
		address_file >> address;

		//Compare address with given port
		if(address == port)
			return m_id;
	}

	return -1;
}


void ev3TachoController::MotorController::run(){
	this->command_i << RUN;
}

void ev3TachoController::MotorController::run(int speed){
	this->setSpeed(speed);
	this->run();
}

void ev3TachoController::MotorController::stop(){
	this->command_i << STOP;
}

void ev3TachoController::MotorController::goTo(){
	this->command_i << RUN_TO_ABS;
}

void ev3TachoController::MotorController::goTo(int position){
	this->setPosition(position);
	this->goTo();
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

void ev3TachoController::MotorController::setStop(std::string action){
	this->stop_action << action;
}

void ev3TachoController::MotorController::setHold(){
	this->setStop(STOP_HOLD);
}

void ev3TachoController::MotorController::setCoast(){
	this->setStop(STOP_COAST);
}

int ev3TachoController::MotorController::getSpeed(){
	std::string line;

	this->speed_o >> line;
	return std::stoi(line);
}

int ev3TachoController::MotorController::getPosition(){
	std::string line;

	this->position_o >> line;
	return std::stoi(line);
}

std::string ev3TachoController::MotorController::getAddress(){
	std::string line;

	this->position_o >> line;
	return line;
}