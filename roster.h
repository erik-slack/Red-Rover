// Erik Slack
#pragma once
#include <iostream>
#include <string>
#include <list>
#include <cctype>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <stdlib.h>

#include "List.h"
#include "player.h"

using namespace std;

class Roster
{
	private:
		List<Player*> myRosterList;
		List<Player*> myTeam1;
		List<Player*> myTeam2;
		
		int getFileLines(string file_choice);
		
	public:
		Roster();
		~Roster();

		/* Grading Requirements
		 * MENU
		 * 1 - Menu follows the required format. After every operation except Quit, the user is returned to the menu.
		 * ROSTER
		 * 1 - Reads in an input file and successfully creates the roster. Rejects any incorrect file names provided by the user.
		 * 2 - Prints the names of all the Person objects in the roster in the specified order.
		 * 3 - Shuffles the order of Person objects in the roster.
		 * TEAMS
		 * 1 - Creates two teams from the Person objects in the roster, as described above. The last Persons entered is omitted if the number of Persons is odd.
		 * 2 - The Persons added to the teams are removed from the roster.
		 * 3 - The two teams are displayed for the user.
		 * USER PLAY
		 * 1 - Teams are displayed for user input. User input is checked for validity and re-prompting occurs when necessary.
		 * 2 - Correctly calculates when a link is to be broken.
		 * 3 - Correctly remove sand inserts from the two teams.
		 * OTHER
		 * 1 - Appropriate design document attached.
		 * 2 - Your program passes valgrind with no memory leaks.
		 * 3 - You have neat and consistent code with comments where appropriate.
		 * AUTO PLAY (EXTRA CREDIT)
		 * 1 - Teams are printed after each attempt to break a connection. 
		 * 2 - Successfully creates a randomly generated game. 
		 * 3 - Program does not crash.
		 */

		/* Part 1 CREATE ROSTER */
		void createRoster();
		void clearRoster();
		int getRosterSize();
		bool addPlayerToRoster(string name_in, int strength_in, int speed_in);
		
		/* Part 2 VIEW ROSTER */
		void viewRoster();
		
		/* Part 3 SHUFFLE ROSTER */
		void shuffleRoster();
		string itoaConverter(int to_be_converted);
		
		/* Part 4 CREATE TEAMS */
		void createTeams();
		int getTeam1Size();
		int getTeam2Size();
		void clearTeam1();
		void clearTeam2();
		
		/* Part 5 VIEW TEAMS */
		void viewTeams();
		
		/* Part 6 USER PLAY */
		string userPlay();
		string choosePlayer(string gametype, string team);
		string getLinkedDefender(string player_on_defense, string team_on_defense);
		void swapPlayer(string player_to_swap, string round_winning_team, string swap_next_to_this_player, string and_this_player);
		
		/* Part 7 AUTO PLAY (EXTRA CREDIT) */
		string autoPlay();
};
