// Erik Slack
#include <iostream>
#include "roster.h"
#include "player.h"
using namespace std;

// This main_menu gives choices to the user of many other functions they can choose to make use of.  Consider it like Grand Central Station.
void main_menu()	
{
	Roster myRoster;
	bool repeat_checker = true;
	while (repeat_checker == true)
	{
		string name_choice = "";
		cout << "Erik's Red Rover Application" << endl;
		cout << "1 - Load New Roster \n2 - View Roster \n3 - Shuffle Roster \n4 - Create Teams \n5 - View Teams \n6 - User Play \n7 - Auto Play \n8 - Quit" << endl << endl;
		cout << "What would you like to do? \t";
		int menu_choice = 0;
		cin >> menu_choice;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore();
			cout << "Try again please.  Choose a number this time.";
		}

		
		if (menu_choice == 1) // Clears Current Roster and Loads File
		{
			cout << "You chose menu choice " << menu_choice << endl;
			myRoster.clearRoster();
			myRoster.createRoster();
		}
		
		else if (menu_choice == 2)  // View Roster
		{
			cout << "You chose menu choice " << menu_choice << endl;
			
			if (myRoster.getRosterSize() == 0) {
				cout << "Roster Empty" << endl;
			} else {
				myRoster.viewRoster();
			}
		}
		
		else if (menu_choice == 3) // Shuffle Roster
		{
			cout << "You chose menu choice " << menu_choice << endl;
			
			if (myRoster.getRosterSize() == 0) {
				cout << "Roster Empty" << endl;
			} else {
				myRoster.shuffleRoster();
			}
		}
		
		
		else if (menu_choice == 4) // Create Teams
		{
			cout << "You chose menu choice " << menu_choice << endl;
			
			if (myRoster.getRosterSize() == 0) {
				cout << "Roster Empty" << endl;
			} else {
				myRoster.createTeams();
			}
		}
		
		
		else if (menu_choice == 5)  // View Teams
		{
			cout << "You chose menu choice " << menu_choice << endl;
			
			if (myRoster.getTeam1Size() < 2) {
				cout << "Not enough players on the teams." << endl;
			} else {
				myRoster.viewTeams();
			}
		}
		
		else if (menu_choice == 6) // User Play
		{
			cout << "You chose menu choice " << menu_choice << endl;
			
			if (myRoster.getTeam1Size() < 2) {
				cout << "Not enough players on the teams." << endl;
			} else {
				myRoster.userPlay();
			}
		}
		
		else if (menu_choice == 7) // Auto Play
		{
			cout << "You chose menu choice " << menu_choice << endl;
			
			if (myRoster.getTeam1Size() < 2) {
				cout << "Not enough players on the teams." << endl;
			} else {
				myRoster.autoPlay();
			}
		}

		else if (menu_choice == 8) // Quit
		{
			cout << "You chose menu choice " << menu_choice << endl;
			cout << "The application has been terminated.  Goodbye." << endl;
			repeat_checker = false;
		}
		
		else // INPUT VALIDATION
		{
			cout << endl;
			cout << "That is not a valid response to the question. \n" << endl;
		}
		
		cout << "\n" << endl;
	}
}

int main()
{
	/*Pedigree pedigree1;
	string name_choice;

	cout << "What is the full name of the person you are adding?" << endl;
			
	while (name_choice == "")
	{
		getline(cin, name_choice);
	}

	pedigree1.addPerson(name_choice);*/

	main_menu();
	
	return 0;
}
