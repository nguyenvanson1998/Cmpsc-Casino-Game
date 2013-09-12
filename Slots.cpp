//Slots.cpp - instantiation of slots minigame
//Written by Emma Roudabush

#include "Slots.h"
#include <iostream>
#include <math.h>
#include <time.h>

#define MAX_BET							100
#define MIN_BET							1
#define BET_CHOICE						1
#define LEAVE_CHOICE					2
#define AMOUNT_OF_SLOT_POSSIBILITIES	5
#define MIN_SLOT_POSSIBILITY			1
#define FIRST_NUMBER				SlotFaces[0]
#define SECOND_NUMBER				SlotFaces[1]
#define THIRD_NUMBER				SlotFaces[2]
#define ALL_MATCH						3
#define PARTIAL_MATCH					2
#define NO_MATCH						0

using namespace std;

int Slots::Play()
{
	system("CLS"); //clearing the board
	cout << "Welcome to Slots!" << endl;

	while (PlayerMoney.HasMoney() && WantsToContinue)
	{
		cout << "You have $" << PlayerMoney.GetCurrentAmountOfMoney() << " to bet with" << endl;
		
		//displays menu of choices for game decisions
		int playersChoice, bet;
		cout << "\nChoose what to do" << endl;
		cout << "1: Bet" << endl;
		cout << "2: End Program" << endl;
		cout << "Enter number here: ";
		cin >> playersChoice;

		switch(playersChoice)
		{
		default: 
			cout << "Invalid choice.\n" << endl;
			break;
		case BET_CHOICE:
			//collecting bet
			cout << "\n\nEnter bet (Min bet is 1, Max bet is 100): "; 
			cin >> bet;
			//making sure bet is valid
			while (bet > PlayerMoney.GetCurrentAmountOfMoney() || bet > MAX_BET || bet < MIN_BET)
			{
				cout << "Invalid bet." << endl;
				cout << "Enter bet (Min bet is 1, Max bet is 100): "; 
				cin >> bet;
			}
			//Spinning and displaying slot machine with values
			Spin();
			DisplaySlotFace();
			//Analysing proper payout
			if (NumberOfMatchingFaces() == 0) //there are no matching sides
			{
				cout << "Nothing matches!" << endl;
				cout << "You lose your bet of $" << bet << endl;
				PlayerMoney.LoseBet(bet);
			}
			else if (NumberOfMatchingFaces() == 2) //two faces match
			{
				cout << "Two faces match!" << endl;
				cout << "You get your bet back" << endl;
			}
			else //all three match
			{
				cout << "All three match!!" << endl;
				cout << "You get double your bet back!" << endl;
				PlayerMoney.WonBet(bet); //will add another bet to the current money, since first bet was not originally taken out
			}							 //of the player's money total
			break;
		case LEAVE_CHOICE:
			WantsToContinue = false;
			break;
		}
	}

	if (!PlayerMoney.HasMoney())
		cout << "\nYou are out of money!" << endl;

	cout << "Thanks for playing Slots!" << endl;

	return PlayerMoney.GetCurrentAmountOfMoney();
}

//function to "spin" the slot machine, putting a random number between 1 and 5 in the slot machine
void Slots::Spin()
{
	srand(time(NULL)); //to makes sure rand won't be seeded the same every time
					   //meaning the random generator won't follow the same sequence

	for (int i = 0; i < SLOTS_NUMBER; i++)
	{
		//putting random number in each of the slot faces, between 1 and 5
		SlotFaces[i] = rand() % AMOUNT_OF_SLOT_POSSIBILITIES + MIN_SLOT_POSSIBILITY; 
	}
}

//function to display an ASCII art slot machine with the player's outcome
void Slots::DisplaySlotFace()
{
	cout << "\n\n"; 
	cout << "-----------------" << endl;
	cout << "|" << "  " << "---" << " " << "---" << " " << "---" << "  "  << "|" << endl;
	cout << "| | " << FIRST_NUMBER << " | " << SECOND_NUMBER << " | " << THIRD_NUMBER << " | |" << endl;
	cout << "|" << "  " << "---" << " " << "---" << " " << "---" << "  "  << "|" << endl;
	cout << "|" << "\t\t" << "| (_)" << endl;
	cout << "|" << "\t\t" << "| ||" << endl;
	cout << "|" << "\t\t" << "| ||" << endl;
	cout << "|" << "\t\t" << "| ||" << endl;
	cout << "-----------------" << endl;
	cout << "\n\n"; 
}

//function to determine the number of matching numbers on the slot faces
int Slots::NumberOfMatchingFaces()
{
	if (FIRST_NUMBER == SECOND_NUMBER && FIRST_NUMBER == THIRD_NUMBER)
		return ALL_MATCH;
	else if (FIRST_NUMBER == SECOND_NUMBER || FIRST_NUMBER == THIRD_NUMBER || THIRD_NUMBER == SECOND_NUMBER)
		return PARTIAL_MATCH;
	else 
		return NO_MATCH;
}