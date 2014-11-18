// Erik Slack
#include "player.h"
using namespace std;

Player::Player(string name_in, int strength_in, int speed_in){
	name = name_in;
	strength = strength_in;
	speed = speed_in;
}

Player::~Player(){}

// ANALYZERS
string Player::getName(){
	return name;
}

int Player::getStrength(){
	return strength;
}

int Player::getSpeed(){
	return speed;
}
