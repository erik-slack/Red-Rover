// Erik Slack
#include "roster.h"
using namespace std;

// valgrind --tool=memcheck --leak-check=yes ./redRover

Roster::Roster(){srand(time(0));}
Roster::~Roster(){myRosterList.clear(); myTeam1.clear(); myTeam2.clear();}

/* Part 1 CREATE ROSTER
	This option will allow the user to enter a name of a file to read in. 
	You may create your own file for testing purposes, but TA files will be used when grading your program. 
	The file will contain a list of Persons to be put on the roster. 
	The format of the file will look something like this, with one token on each line:
		Dantley
		25
		12
		Matt
		15
		20
	The first integer following a Person's name is that Person's strength. 
	The second integer is that Person's speed. Using the information for each Person, create a new node and add it to the end of your roster. 
	If there is a previously existing roster, add the new Persons to that roster. 
	You may assume that the file format will be correct. 
	You may NOT assume that a correct file name will be given. 
	If an incorrect file name is given, advise the user of the error and return to the “menu.”
*/
void Roster::createRoster(){
	string file_choice;
	ifstream in_file;
	string name_in;
	int strength_in = 0;
	int speed_in = 0;
	
	clearRoster();
	
	//LOAD FILE
	do {
		cout << "What is the path to the file you wish to import?" << endl;
		cin >> file_choice;
	} while (file_choice.empty());

	cout << "File name to load (file_name.txt): \t" << file_choice << endl;
	in_file.open(file_choice.c_str());

	int line_count = getFileLines(file_choice);
	
	for (int i = line_count; i > 0; i--){
		in_file >> name_in >> strength_in >> speed_in;
		addPlayerToRoster(name_in, strength_in, speed_in);
	}
	
	do {
		
	} while (getline(in_file, file_choice));

	//cout << endl << "going in: " << line_count << endl;

	if (myRosterList.size() < 1) {
		cout << "Filename/directory invalid." << endl;
		return;
	}

	cout << endl;
}

bool Roster::addPlayerToRoster(string name_in, int strength_in, int speed_in){
	bool player_added = true;
	
	// DO I NEED A DUPLICATES CHECKER?
	string index_to_insert = "0";
	
	Player* new_player = new Player(name_in, strength_in, speed_in);
	//cout << name_in << ": strength = " << strength_in << " speed = " << speed_in;
	myRosterList.insert(new_player, index_to_insert);
	
	return player_added;
}

void Roster::clearRoster(){
	myRosterList.clear();
}

int Roster::getRosterSize(){
	return myRosterList.size();
}

/* Part 2 VIEW ROSTER
	This option will print out all of the names of the Persons on the roster. 
	The name at index 0 will be printed first, followed by the names associated with the other indexes in order. 
	The string “Roster Empty” is printed if the roster is empty.
*/
void Roster::viewRoster(){
	cout << myRosterList.print();
}

/* Part 3 SHUFFLE ROSTER
	This option will randomly shuffle the Persons in your roster. The string “Roster Empty” is printed if the roster is empty. 
*/
void Roster::shuffleRoster(){
	int last_pos = getRosterSize() - 1;
	for (int i = getRosterSize() * 55; i > 0; i--)
	{
		int randomPlayer = rand() % getRosterSize(); // Choose a random number that is between 0 and the maximum size of the list; 
		/*stringstream converter;
		converter << randomPlayer;
		string randomPlayerConverted;
		converter >> randomPlayerConverted;*/
		
		string randomPlayerConverted = itoaConverter(randomPlayer);
		
		Player* tempStoredPlayer = myRosterList.remove(randomPlayerConverted); // Store that data in a temporary variable and remove player from list
		myRosterList.insert(tempStoredPlayer, "0");
	}
}

string Roster::itoaConverter(int to_be_converted){
	stringstream converter;
	string playerConverted;
	
	converter << to_be_converted;
	converter >> playerConverted;
	
	return playerConverted;
}

/* Part 4 CREATE TEAMS
	This option will divide the Persons in the roster into two teams.
	When adding to the teams, you must insert at the end of the team's list 
	(i.e. with a new index that is greater that all the existing indexes); the members of the team are linked together in this order. 
	Every other Person will be assigned to the same team. The first Person in the roster will be added to Team A, 
	the second Person to Team B, the third Person to Team A, etc. 
	When a Person is added to a team, he is removed from the roster. 
	If the roster has an odd number of Persons, omit the last Person (the last Person will remain on the roster). 
	If the roster has less than 4 persons, advise the user of the error and return to the menu. 
	Team A and Team B are cleared of all Persons from a previous game before new Persons are added.
*/
void Roster::createTeams(){
	int roster_size = getRosterSize();
	if (roster_size < 4){
		cout << "There must be at least 4 players on the roster to create teams." << endl;
	} else {
		clearTeam1();
		clearTeam2();
		
		
		bool odd_team_situation = false;
		int last_or_not_picked;
		
		if (roster_size % 2 == 1){
			odd_team_situation = true;	
		}
		
		if (odd_team_situation == true){
			last_or_not_picked = roster_size - 1;
		} else {
			last_or_not_picked = roster_size;
		}
		
		for (int i = 0; i < last_or_not_picked; i++){
			string teamSize;

			Player* tempStoredPlayer = myRosterList.remove("0"); // Store that data in a temporary variable and remove player from list
			
			if ((i % 2) == 0){
				teamSize = itoaConverter(getTeam1Size());
				myTeam1.insert(tempStoredPlayer, teamSize);
				//cout << "team1 size = " << teamSize << endl;
			} else {
				teamSize = itoaConverter(getTeam2Size());
				myTeam2.insert(tempStoredPlayer, teamSize);
				//cout << "team2 size = " << teamSize << endl;
			}
		}
	}
	
}

int Roster::getTeam1Size(){
	return myTeam1.size();
}

int Roster::getTeam2Size(){
	return myTeam2.size();
}

void Roster::clearTeam1(){
	myTeam1.clear();
}

void Roster::clearTeam2(){
	myTeam2.clear();
}


/* Part 5 VIEW TEAMS
	This option will print the names, strengths, and speeds of all the Persons currently on Team A, 
	and then print out all of the names, strengths, and speeds of Persons currently on Team B. 
	For example,
		Team A:
			Luz 15 5
			Alexis 20 10
		Team B:
			Max 10 20
			Ana 15 15
*/
void Roster::viewTeams(){
	cout << "Team A has " << getTeam1Size() << " players." << endl;
	cout << "Team B has " << getTeam2Size() << " players." << endl;
	cout << "Team A:\n" << myTeam1.printMore();
	cout << "Team B:\n" << myTeam2.printMore();
}

/* Part 6 USER PLAY
	The functionality of this option is as follows:
	1. The names of the Persons on Team A are displayed to the user and the user is prompted to pick a name from Team A. 
	2. The names of the Persons on Team B are displayed to the user and the user is prompted to pick a name from Team B. 
	This is the name of the Person whose link to his successor the Person from Team A will try to break, 
	unless the person is the last Person on Team B, in which case the Person from Team A will try to break the link between the last two Persons.
		For example,
			Team A: Grant, Ray, Iris, Eric
				Pick: Ray
			Team B: Dantley, Kevin, Matt, Jacob
				Pick: Matt
	In this example, Ray will attempt to break the link between Matt and Jacob. 
	The link is broken if the sum of Ray's strength and speed exceeds the sum of Matt’s and Jacob's strength.
	If the link is broken then Ray returns to his original index on his team. 
	The stronger Person associated with the link that was broken becomes a part of Ray's team and is inserted after Ray. 
	If the link is not broken then Ray becomes part of Team B and is inserted between Matt and Jacob.
		3. Team B then assumes Team A’s role, and so forth. 
		4. Play continues until there is one person left on a team. At this point, print 				out the name of the winning team and return to the menu.		
	If the user enters invalid input, re-prompt the user until correct input is provided.
*/
string Roster::userPlay(){
	string winning_team;
	int turn_count = 0;
	string team_on_offense;
	string team_on_defense;
	string player_on_offense;
	string player_on_defense;
	string linked_defender;
	int offense_strength = 0;
	int offense_speed = 0;
	int defender_strength = 0;
	int linked_defender_strength = 0;
	string player_on_offense_index;
	string player_on_defense_index;
	
	while (winning_team == ""){
		string round_winning_team;
		//cout << "part A" << endl;
		
		// Determine Offensive and Defense Team
		if (turn_count % 2 == 0){
			team_on_offense = "A";
			team_on_defense = "B";
		} else {
			team_on_offense = "B";
			team_on_defense = "A";
		}
		//cout << "part B" << endl;
		

		// Pick Players to Compete
		player_on_offense = choosePlayer("user", team_on_offense);
		player_on_defense = choosePlayer("user", team_on_defense);
		//cout << "part C" << endl;
		
		// Determine Linked Defender
		if (team_on_defense == "A"){
			linked_defender = getLinkedDefender(player_on_defense, team_on_defense);
		} else {
			linked_defender = getLinkedDefender(player_on_defense, team_on_defense);
		}
		//cout << "part D" << endl;
		
		// Get Offensive Player's Stats
		if (team_on_offense == "A"){
			player_on_offense_index = itoaConverter(myTeam1.find(player_on_offense));
			offense_strength = (myTeam1.at(player_on_offense_index, 0, 0))->getStrength();
			offense_speed = (myTeam1.at(player_on_offense_index, 0, 0))->getSpeed();
		} else {
			player_on_offense_index = itoaConverter(myTeam2.find(player_on_offense));
			offense_strength = myTeam2.at(player_on_offense_index, 0, 0)->getStrength();
			offense_speed = myTeam2.at(player_on_offense, 0, 0)->getSpeed();
		}
		//cout << "part E" << endl;
		
		// Get Defensive Players' Stats
		if (team_on_defense == "A"){
			player_on_defense_index = itoaConverter(myTeam1.find(player_on_defense));
			defender_strength = myTeam1.at(player_on_defense_index, 0, 0)->getStrength();
			linked_defender_strength = myTeam1.at(linked_defender, 0, 0)->getStrength();
		} else {
			player_on_defense_index = itoaConverter(myTeam2.find(player_on_defense));
			defender_strength = myTeam2.at(player_on_defense_index, 0, 0)->getStrength();
			linked_defender_strength = myTeam2.at(linked_defender, 0, 0)->getStrength();
		}
		//cout << "part F" << endl;
		
		// Choose Winner and Determine Who Gets Swapped to Where
		if (offense_strength + offense_speed > defender_strength + linked_defender_strength){
			round_winning_team = team_on_offense;
			cout << "Team " << round_winning_team << " offense wins round!" << endl;
			
			if (defender_strength > linked_defender_strength){
				swapPlayer(player_on_defense_index, round_winning_team, player_on_offense_index, "none");
			} else {
				swapPlayer(player_on_defense_index, round_winning_team, player_on_offense_index, "none");
			}
		} else {
			round_winning_team = team_on_defense;
			cout << "Team " << round_winning_team << " defense wins round!" << endl;
			
			swapPlayer(player_on_offense_index, round_winning_team, player_on_defense_index, linked_defender);
		}
		//cout << "part G" << endl;
		
		if (myTeam1.size() < 2 || myTeam2.size() < 2){
			winning_team = round_winning_team;
			cout << "Team " << winning_team << " wins the game!" << endl;
		} else {
			turn_count++;
		}
	}
	
	return winning_team;
}

string Roster::choosePlayer(string gametype, string team){
	string chosen_player;
	bool valid_player = false;
	int player_index_found = -1;
	//Player* player_found = NULL;
	
	if (gametype == "user"){
		// USER PLAY
		if (team == "A"){
			cout << "Choose a player..." << endl;
			cout << "Team A: " << myTeam1.printInLine();
		} else {
			cout << "Choose a player..." << endl;
			cout << "Team B: " << myTeam2.printInLine();
		}
		
		cin >> chosen_player;
		
		if (team == "A"){
			player_index_found = myTeam1.find(chosen_player);
			while (player_index_found == -1){
				cout << "Player not found on team A, enter another name." << endl;
				cin >> chosen_player;
				player_index_found = myTeam1.find(chosen_player);
			}
			//player_found = myTeam1.at(itoaConverter(player_index_found));
		} else {
			player_index_found = myTeam2.find(chosen_player);
			while (player_index_found == -1){
				cout << "Player not found on team B, enter another name." << endl;
				cin >> chosen_player;
				player_index_found = myTeam2.find(chosen_player);
			}
			//player_found = myTeam2.at(itoaConverter(player_index_found));
		}
	} else {
		// AUTO PLAY
		int random_player_index = 0;
		string random_player_name;
		
		if (team == "A"){
		cout << "Team A: " << myTeam1.printInLine();
		} else {
		cout << "Team B: " << myTeam2.printInLine();
		}
		
		if (team == "A"){
			random_player_index = rand() % myTeam1.size();
			random_player_name = myTeam1.at(itoaConverter(random_player_index), 0, 0)->getName();
		} else {
			random_player_index = rand() % myTeam2.size();
			random_player_name = myTeam2.at(itoaConverter(random_player_index), 0, 0)->getName();
		}
		
		chosen_player = random_player_name;
	}
	
	return chosen_player;
}

string Roster::getLinkedDefender(string player_on_defense, string team_on_defense){
	string linked_defender;
	
	if (team_on_defense == "A"){
		if (player_on_defense == itoaConverter(myTeam1.size() - 1)){
			linked_defender = itoaConverter(myTeam1.find(player_on_defense) - 1);
		} else {
			linked_defender = itoaConverter(myTeam1.find(player_on_defense) + 1);
		}
	} else {
		if (player_on_defense == itoaConverter(myTeam2.size() - 1)){
			//cout << "player_on_defense = " << player_on_defense << endl;
			linked_defender = itoaConverter(myTeam2.find(player_on_defense) - 1);
		} else {
			//cout << "player_on_defense = " << player_on_defense << endl;
			linked_defender = itoaConverter(myTeam2.find(player_on_defense) + 1);
		}
	}
	
	return linked_defender;
}

void Roster::swapPlayer(string player_to_swap, string round_winning_team, string swap_next_to_this_player, string and_this_player){
	string win_type;
	Player* player_being_switched = NULL;
	
	//cout << "swap_next_to_this_player = " << swap_next_to_this_player << " and_this_player = " << and_this_player;
	
	if (and_this_player == "none"){
		win_type = "offensive";
	} else {
		win_type = "defensive";
	}
	
	if (win_type == "offensive"){
		if (round_winning_team == "A"){
			player_being_switched = myTeam2.remove(player_to_swap);
			swap_next_to_this_player = itoaConverter(atoi(swap_next_to_this_player.c_str()) + 1);
			myTeam1.insert(player_being_switched, swap_next_to_this_player);
		} else {
			player_being_switched = myTeam1.remove(player_to_swap);
			swap_next_to_this_player = itoaConverter(atoi(swap_next_to_this_player.c_str()) + 1);
			myTeam2.insert(player_being_switched, swap_next_to_this_player);
		}
	} else {
		if (round_winning_team == "A"){
			player_being_switched = myTeam2.remove(player_to_swap);
			if (atoi(swap_next_to_this_player.c_str()) < atoi(and_this_player.c_str())){
				myTeam1.insert(player_being_switched, swap_next_to_this_player);
			} else {
				swap_next_to_this_player = atoi(swap_next_to_this_player.c_str()) - 0;
				myTeam1.insert(player_being_switched, swap_next_to_this_player);
			}
		} else {
			player_being_switched = myTeam1.remove(player_to_swap);
			if (atoi(swap_next_to_this_player.c_str()) < atoi(and_this_player.c_str())){
				myTeam2.insert(player_being_switched, swap_next_to_this_player);
			} else {
				swap_next_to_this_player = itoaConverter(atoi(swap_next_to_this_player.c_str()) - 0);
				myTeam2.insert(player_being_switched, swap_next_to_this_player);
			}
		}
	}
	cout << endl << endl;
}

/* Part 7 AUTO PLAY (EXTRA CREDIT)
	This option will simulate a game of Red Rover. 
	Your program randomly selects a player to try to break a randomly selected link of the other team. 
	Between each turn, print the names of Persons currently on Team A and Team B. 
	At the end of play, print out the name of the winning team, and return to the menu.
*/
string Roster::autoPlay(){
	string winning_team;
	int turn_count = 0;
	string team_on_offense;
	string team_on_defense;
	string player_on_offense;
	string player_on_defense;
	string linked_defender;
	int offense_strength = 0;
	int offense_speed = 0;
	int defender_strength = 0;
	int linked_defender_strength = 0;
	string player_on_offense_index;
	string player_on_defense_index;
	
	while (winning_team == ""){
		string round_winning_team;
		//cout << "part A" << endl;
		
		// Determine Offensive and Defense Team
		if (turn_count % 2 == 0){
			team_on_offense = "A";
			team_on_defense = "B";
		} else {
			team_on_offense = "B";
			team_on_defense = "A";
		}
		//cout << "part B" << endl;
		

		// Pick Players to Compete
		player_on_offense = choosePlayer("auto", team_on_offense);
		player_on_defense = choosePlayer("auto", team_on_defense);
		//cout << "part C" << endl;
		
		// Determine Linked Defender
		if (team_on_defense == "A"){
			linked_defender = getLinkedDefender(player_on_defense, team_on_defense);
		} else {
			linked_defender = getLinkedDefender(player_on_defense, team_on_defense);
		}
		//cout << "part D" << endl;
		
		// Get Offensive Player's Stats
		if (team_on_offense == "A"){
			player_on_offense_index = itoaConverter(myTeam1.find(player_on_offense));
			offense_strength = (myTeam1.at(player_on_offense_index, 0, 0))->getStrength();
			offense_speed = (myTeam1.at(player_on_offense_index, 0, 0))->getSpeed();
		} else {
			player_on_offense_index = itoaConverter(myTeam2.find(player_on_offense));
			offense_strength = myTeam2.at(player_on_offense_index, 0, 0)->getStrength();
			offense_speed = myTeam2.at(player_on_offense, 0, 0)->getSpeed();
		}
		//cout << "part E" << endl;
		
		// Get Defensive Players' Stats
		if (team_on_defense == "A"){
			player_on_defense_index = itoaConverter(myTeam1.find(player_on_defense));
			defender_strength = myTeam1.at(player_on_defense_index, 0, 0)->getStrength();
			linked_defender_strength = myTeam1.at(linked_defender, 0, 0)->getStrength();
		} else {
			player_on_defense_index = itoaConverter(myTeam2.find(player_on_defense));
			defender_strength = myTeam2.at(player_on_defense_index, 0, 0)->getStrength();
			linked_defender_strength = myTeam2.at(linked_defender, 0, 0)->getStrength();
		}
		//cout << "part F" << endl;
		
		// Choose Winner and Determine Who Gets Swapped to Where
		if (offense_strength + offense_speed > defender_strength + linked_defender_strength){
			round_winning_team = team_on_offense;
			//cout << "Team " << round_winning_team << " offense wins round!" << endl;
			
			if (defender_strength > linked_defender_strength){
				swapPlayer(player_on_defense_index, round_winning_team, player_on_offense_index, "none");
			} else {
				swapPlayer(player_on_defense_index, round_winning_team, player_on_offense_index, "none");
			}
		} else {
			round_winning_team = team_on_defense;
			//cout << "Team " << round_winning_team << " defense wins round!" << endl;
			
			swapPlayer(player_on_offense_index, round_winning_team, player_on_defense_index, linked_defender);
		}
		//cout << "part G" << endl;
		
		if (myTeam1.size() < 2 || myTeam2.size() < 2){
			winning_team = round_winning_team;
			cout << "Team " << winning_team << " wins the game!" << endl;
		} else {
			turn_count++;
		}
	}
	
	return winning_team;
}

// PRIVATE FUNCTIONS
int Roster::getFileLines(string file_choice){
	ifstream in_file;
	in_file.open(file_choice.c_str());
	int line_count = 0;

	do {
		line_count++;
	} while (!getline(in_file, file_choice).fail());

	line_count--;

	return line_count;
}
