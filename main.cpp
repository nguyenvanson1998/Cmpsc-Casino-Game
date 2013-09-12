//main.cpp - Casino play program
//Written by Emma Roudabush

#include <iostream>
#include "Money.h"
#include "Blackjack.h"
#include "Craps.h"
#include "Roulette.h"
#include "Slots.h"

#define SLOTS_CHOICE			1
#define ROULETTE_CHOICE			2
#define CRAPS_CHOICE			3
#define BLACKJACK_CHOICE		4
#define END_PROGRAM_CHOICE		5
#define NO_MONEY				0

using namespace std;

void main()
{
	int startingMoney;
	bool wantsToContinue = true;

	cout << "Welcome to CompSci Casino!" << endl;
	
	cout << "How much money do you have? ";
	cin >> startingMoney;
	while (startingMoney <= NO_MONEY) //making sure starting player's money is valid
	{
		cout << "Invalid starting money!" << endl; 
		cout << "\nHow much money do you have? ";
		cin >> startingMoney;
	}

	Money playerMoney(startingMoney);

	while (playerMoney.HasMoney() && wantsToContinue)
	{
		int playersChoice;
		cout << "\nPick which game to play!" << endl;
		cout << "1: Slots" << endl;
		cout << "2: Roulette" << endl;
		cout << "3: Craps" << endl;
		cout << "4: Blackjack" << endl;
		cout << "5: End Program" << endl;
		cout << "Enter number here: ";
		cin >> playersChoice;

		switch (playersChoice)
		{
			//have to put default case first so there will be no
			//"Transfer of control bypasses initialization of" error
			default:
				cout << "Invalid choice.";
				break;
			case SLOTS_CHOICE:
				{
				Slots newSlotsGame(playerMoney);
				playerMoney.SetMoney(newSlotsGame.Play());
				}
				break;
			case ROULETTE_CHOICE:
				{
				Roulette newRouletteGame(playerMoney);
				playerMoney.SetMoney(newRouletteGame.Play());
				}
				break;
			case CRAPS_CHOICE:
				{
				Craps newCrapsGame(playerMoney);
				playerMoney.SetMoney(newCrapsGame.Play());
				}
				break;
			case BLACKJACK_CHOICE:
				{
				Blackjack newBlackjackGame(playerMoney);
				playerMoney.SetMoney(newBlackjackGame.Play());
				}
				break;
			case END_PROGRAM_CHOICE:
				wantsToContinue = false;
				break;

		}

		if (playerMoney.HasMoney() && wantsToContinue)
		{
			system("CLS"); //clearing the board
			cout << "You have $" << playerMoney.GetCurrentAmountOfMoney() << " to use";
		}
		else
		{
			cout << "\nThank you for coming to the CompSci Casino!" << endl;
			cout << "You ended with $" << playerMoney.GetCurrentAmountOfMoney() << "." << endl;
			int difference = playerMoney.GetCurrentAmountOfMoney() - startingMoney;
			if (difference > 0)
				cout << "You won $" << difference << "! :)" << endl;
			else if (difference < 0)
				cout << "You lost $" << abs(difference) << ". :(" << endl;
			else
				cout << "You broke even!" << endl;
		}
	}

	system("pause");
}