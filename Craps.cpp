//Craps.cpp -- Craps class/minigame instantiation
//Written by Emma Roudabush

#include "Craps.h"
#include <iostream>

#define MAX_BET								100
#define MIN_BET								1
#define START_ROUND_CHOICE					1
#define LEAVE_CHOICE						2
#define PASS_LINE_CHOICE					1
#define DONT_PASS_CHOICE					2

#define CRAPS_VALUE_1						2			//values that are "craps"
#define CRAPS_VALUE_2						3
#define CRAPS_VALUE_3						12

#define PASS_LINE 							11
#define SEVEN_VALUE							7

using namespace std;

//function to play the game (ultimately drives the game)
int Craps::Play()
{
	system("CLS"); //clearing the board
	cout << "Welcome to Craps!" << endl;

	while (PlayerMoney.HasMoney() && WantsToContinue)
	{
		DisplayBoard();
		cout << "You have $" << PlayerMoney.GetCurrentAmountOfMoney() << " to bet with" << endl;
		
		//displays menu of choices for game decisions
		int playersChoice;
		cout << "\nChoose what to do" << endl;
		cout << "1: Start Round" << endl;
		cout << "2: End Program" << endl;
		cout << "Enter number here: ";
		cin >> playersChoice;

		switch(playersChoice)
		{
		default: 
			cout << "Invalid choice.\n" << endl;
			break;
		case START_ROUND_CHOICE:
			//starting round with betting style choice
			int betChoice;
			cout << "\nWhat bet do you wish to make" << endl;
			cout << "1: Pass Line Bet" << endl;
			cout << "2: Don't Pass Bet" << endl;
			cout << "Enter number here: ";
			cin >> betChoice;

			//making sure bet choice is valid
			while (betChoice != PASS_LINE_CHOICE && betChoice != DONT_PASS_CHOICE)
			{
				cout << "Invalid betting choice. Pick a new choice: ";
				cin >> betChoice;
			}

			//directing the betting choice selected to the proper game play method
			if (betChoice == PASS_LINE_CHOICE)
				PassLineBet();
			else
				DontPassBet();
			break;
		case LEAVE_CHOICE:
			WantsToContinue = false;
			break;
		}
	}

	if (!PlayerMoney.HasMoney())
		cout << "\nYou are out of money!" << endl;

	cout << "Thanks for playing Craps!" << endl;

	return PlayerMoney.GetCurrentAmountOfMoney();
}


//function to display an ASCII craps board
void Craps::DisplayBoard()
{
	cout << "________________________" << endl;
	cout << "|                       |" << endl;
	cout << "|   ____  CMPSC CASINO  |" << endl;
	cout << "| O | | |   	        |" << endl;
	cout << "|   | | |______________ |" << endl;
	cout << "| O | | |    |	 |    | |" << endl;
	cout << "|   | | |    |   |    | |" << endl;
	cout << "| O | |_|____|___|____| |" << endl;
	cout << "|   |_________________| |" << endl;
	cout << "| O   O   O   O	        |" << endl;
	cout << "________________________" << endl;
	cout << endl;
}

//function to proceed with play if player chooses to do a Pass line Bet
void Craps::PassLineBet()
{
	//collecting bet
	int bet;
	cout << "\n\nEnter bet (Min bet is 1, Max bet is 100): "; 
	cin >> bet;
	//making sure bet is valid
	while (bet > PlayerMoney.GetCurrentAmountOfMoney() || bet > MAX_BET || bet < MIN_BET)
	{
		cout << "Invalid bet." << endl;
		cout << "Enter bet (Min bet is 1, Max bet is 100): "; 
		cin >> bet;
	}

	//rolling dice and seeing what the outcome it
	PairOfDice.RollDice();

	int result = PairOfDice.ValueOfPair();
	cout << "\nYou rolled a combined " << result << endl;
	if (result == PASS_LINE || result == SEVEN_VALUE) //player rolled a combined 7 or 11 (bet doubled)
	{
		cout << "You win double your bet!"  << endl;
		PlayerMoney.WonBet(bet); //will add another bet to the current money, since first bet was not originally taken out
								 //of the player's money total
	}
	else if (result == CRAPS_VALUE_1 || result == CRAPS_VALUE_2 || result == CRAPS_VALUE_3) //player rolled a "craps" value (loses bet)
	{
		cout << "You rolled a craps! You lose your bet." << endl;
		PlayerMoney.LoseBet(bet);
	}	
	else
	{
		CurrentPoint = result;
		cout << "Your point is now " << CurrentPoint << endl;
		
		//starting process to roll again until hits a 7 or point
		cout << "\nPress enter to roll again!" << endl;
		cin.ignore();
		cin.get();
		PairOfDice.RollDice();
		result = PairOfDice.ValueOfPair();

		while (result != CurrentPoint && result != SEVEN_VALUE)
		{
			cout << "\nYou rolled a combined " << result << endl;
			cout << "It is not your point or 7." << endl;
			cout << "\nPress enter to roll again!" << endl;
			cin.get();
			PairOfDice.RollDice();
			result = PairOfDice.ValueOfPair();
		}

		cout << "\nYou rolled a combined " << result << endl;
		if (result == CurrentPoint) //player rolls their point before rolling a "7"
		{
			cout << "You hit your point again!" << endl;
			cout << "You win double your bet!" << endl;
			PlayerMoney.WonBet(bet); //will add another bet to the current money, since first bet was not originally taken out
									 //of the player's money total
		}
		else //player rolls a "7" before rolling their point
		{
			cout << "Oh no! You hit a 7 first!" << endl;
			cout << "You lose your bet." << endl;
			PlayerMoney.LoseBet(bet);
		}
	}
}

//function to proceed with play if player chooses to do a Don't Pass Bet
//Don't pass bet is the opposite of a pass line bet
void Craps::DontPassBet()
{
	//collecting bet
	int bet;
	cout << "\n\nEnter bet (Min bet is 1, Max bet is 100): "; 
	cin >> bet;
	//making sure bet is valid
	while (bet > PlayerMoney.GetCurrentAmountOfMoney() || bet > MAX_BET || bet < MIN_BET)
	{
		cout << "Invalid bet." << endl;
		cout << "Enter bet (Min bet is 1, Max bet is 100): "; 
		cin >> bet;
	}

	//rolling dice and seeing what the outcome it
	PairOfDice.RollDice();

	int result = PairOfDice.ValueOfPair();
	cout << "\nYou rolled a combined " << result << endl;
	if (result == CRAPS_VALUE_1 || result == CRAPS_VALUE_2 || result == CRAPS_VALUE_3) //player rolled a "craps" value (bet doubled)
	{
		cout << "You rolled a craps! You win double your bet!"  << endl;
		PlayerMoney.WonBet(bet); //will add another bet to the current money, since first bet was not originally taken out
								 //of the player's money total
	}
	else if (result == PASS_LINE || result == SEVEN_VALUE) //player rolled a combined 7 or 11 (loses bet)
	{
		cout << "You rolled a 7 or 12! You lose your bet." << endl;
		PlayerMoney.LoseBet(bet);
	}	
	else
	{
		CurrentPoint = result;
		cout << "Your point is now " << CurrentPoint << endl;
		
		//starting process to roll again until hits a 7 or point
		cout << "\nPress enter to roll again!" << endl;
		cin.ignore();
		cin.get();
		PairOfDice.RollDice();
		result = PairOfDice.ValueOfPair();

		while (result != CurrentPoint && result != SEVEN_VALUE)
		{
			cout << "\nYou rolled a combined " << result << endl;
			cout << "It is not your pointer or 7." << endl;
			cout << "\nPress enter to roll again!" << endl;
			cin.ignore();
			cin.get();
			PairOfDice.RollDice();
			result = PairOfDice.ValueOfPair();
		}

		cout << "\nYou rolled a combined " << result << endl;
		if (result == CurrentPoint) //player rolls their point before rolling a "7"
		{
			cout << "Oh no! You hit your point again!" << endl;
			cout << "You lose your bet." << endl;
			PlayerMoney.LoseBet(bet);

		}
		else //player rolls a "7" before rolling their point
		{
			cout << "You hit a 7 first!" << endl;
			cout << "You win double your bet!" << endl;
			PlayerMoney.WonBet(bet); //will add another bet to the current money, since first bet was not originally taken out
									 //of the player's money total
		}
	}
}