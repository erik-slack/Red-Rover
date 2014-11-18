// Erik Slack
#pragma once
#include <iostream>
#include <string>
using namespace std;

class Player
{
	private:
		string name;
		int strength;
		int speed;
		
	public:
		Player(string name_in, int strength_in, int speed_in);
		~Player();

		// ANALYZERS
		string getName();
		int getStrength();
		int getSpeed();
};
