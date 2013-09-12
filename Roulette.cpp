//Roulette.cpp-- Roulette class instantiation
//Written by Emma Roudabush

#include "Roulette.h"
#include <math.h>
#include <time.h>
#include <algorithm>

#define ZERO				0
#define RED					"Red"
#define BLACK				"Black"
#define GREEN				"Green"
#define START_1				1
#define START_2				11
#define START_3				19
#define START_4				29
#define END_1				10
#define END_2				18
#define END_3				28
#define END_4				36

#define BET_CHOICE			1
#define LEAVE_CHOICE		2
#define SINGLE_CHOICE		1
#define RANGE_CHOICE_1		2
#define RANGE_CHOICE_2		3
#define RED_CHOICE			4
#define BLACK_CHOICE		5
#define EVEN_CHOICE			6
#define ODD_CHOICE			7

#define NUMBER_OF_POCKETS	36
#define MAX_BET				100
#define MAX_BET_SINGLE		10
#define MIN_BET				1
#define SINGLE_BET			1

using namespace std;

//static map giving the color value of each number on roulette wheel
//int being it's integer value and char being it's color (either r, g, or b)
map<int, string> Roulette::Pockets;

//static map giving the color value of each number on roulette wheel
//int being it's integer value and char being it's color (either r, g, or b)
void Roulette::PreLoadPockets()
{
	Pockets[ZERO] = GREEN;

	for (int i = START_1; i <= END_1; i++)
	{
		if (i % 2 == 0) //in this section, if even -- BLACK
			Pockets[i] = BLACK;
		else
			Pockets[i] = RED; //if odd -- RED
	}

	for (int i = START_2; i <= END_2; i++)
	{
		if (i % 2 == 0) //in this section, if even -- RED
			Pockets[i] = RED;
		else
			Pockets[i] = BLACK; //if odd -- BLACK
	}

	for (int i = START_3; i <= END_3; i++)
	{
		if (i % 2 == 0) //in this section, if even -- BLACK
			Pockets[i] = BLACK;
		else
			Pockets[i] = RED; //if odd -- RED
	}

	for (int i = START_4; i <= END_4; i++)
	{
		if (i % 2 == 0) //in this section, if even -- RED
			Pockets[i] = RED;
		else
			Pockets[i] = BLACK;  //if odd -- BLACK
	}

}

//function to reset all the variables for another game
void Roulette::ResetGame()
{
	//deleting the players bets
	while (!BettedNumbers.empty())
	{
		BettedNumbers.pop_back();
	}

	Bet = 0;
	RedBet = false;
	BlackBet = false;
	EvenBet = false;
	OddBet = false;
	RangeBet = false;
}

//function to determine where the "ball" lands on the roulette wheel
//returns the number landed on
int Roulette::SpinWheel()
{
	srand(time(NULL)); //to makes sure rand won't be seeded the same every time
				       //meaning the random generator won't follow the same sequence

	return rand() % NUMBER_OF_POCKETS;
}

//function that ultimately drives the game play
//directs player to appropriate functions for continued play
int Roulette::Play()
{
	system("CLS"); //clearing the board
	cout << "Welcome to Roulette!" << endl;

	while (PlayerMoney.HasMoney() && WantsToContinue)
	{
		DisplayBoard();
		cout << "You have $" << PlayerMoney.GetCurrentAmountOfMoney() << " to bet with" << endl;
		
		//displays menu of choices for game decisions
		int playersChoice;
		cout << "\nChoose what to do" << endl;
		cout << "1: Start Betting" << endl;
		cout << "2: End Program" << endl;
		cout << "Enter number here: ";
		cin >> playersChoice;

		int winningPocket;
		switch(playersChoice)
		{
		default: 
			cout << "Invalid choice.\n" << endl;
			break;
		case BET_CHOICE:
			ResetGame(); //reseting any changes made by other games
			MakeBets();
			winningPocket = SpinWheel();
			cout << "\n\nThe house spun a " << Pockets[winningPocket] << " " << winningPocket << "!" << endl;
			EvaluateOutcome(winningPocket);
			break;
		case LEAVE_CHOICE:
			WantsToContinue = false;
			break;
		}
	}

	if (!PlayerMoney.HasMoney())
		cout << "\nYou are out of money!" << endl;

	cout << "Thanks for playing Roulette!" << endl;

	return PlayerMoney.GetCurrentAmountOfMoney();
}

//function that allows players to make multiple bets
void Roulette::MakeBets()
{
		//displays menu of choices for game decisions
		int playersChoice;
		cout << "\n\nWhat bet do you wish to make?" << endl;
		cout << "1: Bet on certain numbers" << endl;
		cout << "2: Range Bet, 1-18" << endl;
		cout << "3: Range Bet, 19-36" << endl;
		cout << "4: Bet on Red" << endl;
		cout << "5: Bet on Black" << endl;
		cout << "6: Bet on Evens" << endl;
		cout << "7: Bet on Odds" << endl;
		cout << "Enter number here: ";
		cin >> playersChoice;

		switch(playersChoice) //player can only pick ONE of these betting styles
		{
		default: 
			cout << "Invalid choice.\n" << endl;
			MakeBets(); //to have the player pick another choice
			break;
		case SINGLE_CHOICE:
			SingleNumberBets();
			break;
		case RANGE_CHOICE_1:
			cout << "\n\nEnter bet for the Range bet (Max bet is 100): "; 
			GetBet();
			for (int i = START_1; i <= END_2; i++)
				BettedNumbers.push_back(i);
			NumberOfBets = SINGLE_BET;
			RangeBet = true;
			break;
		case RANGE_CHOICE_2:
			cout << "\n\nEnter bet for the Range bet (Max bet is 100): "; 
			GetBet();
			for (int i = START_3; i <= END_4; i++)
				BettedNumbers.push_back(i);
			RangeBet = true;
			NumberOfBets = SINGLE_BET;
			break;
		case RED_CHOICE:
			cout << "\n\nEnter bet for the Red bet (Max bet is 100): "; 
			GetBet();
			RedBet = true;
			NumberOfBets = SINGLE_BET;
			break;
		case BLACK_CHOICE:
			cout << "\n\nEnter bet for the Black bet (Max bet is 100): "; 
			GetBet();
			BlackBet = true;
			NumberOfBets = SINGLE_BET;
			break;
		case EVEN_CHOICE:
			cout << "\n\nEnter bet for the Even bet (Max bet is 100): "; 
			GetBet();
			EvenBet = true;
			NumberOfBets = SINGLE_BET;
			break;
		case ODD_CHOICE:
			cout << "\n\nEnter bet for the Odd bet (Max bet is 100): ";
			GetBet();
			OddBet = true;
			NumberOfBets = SINGLE_BET;
			break;
		}
}

//function to, if the player choices to pick numbers, let's them pick their choices
void Roulette::SingleNumberBets()
{
	//asking player how many numbers they want to bet on and validating if in bounds
	cout << "\n\nEnter amount of numbers to bet on (Max can bet on is 37): "; 
	cin >> NumberOfBets;
	while (NumberOfBets <= ZERO || NumberOfBets > NUMBER_OF_POCKETS + 1)
	{
		cout << "Invalid amount of numbers." << endl;
		cout << "Enter amount of numbers to bet on (Min bet is 1, Max bet is 37): "; 
		cin >> NumberOfBets;
	}

	//asking player much they want to bet on EACH number and validating
	cout << "\nNow, enter bet for EACH number (Max bet is 10): "; 
	cin >> Bet;
	//making sure bet is valid
	while ((Bet*NumberOfBets) > PlayerMoney.GetCurrentAmountOfMoney() || Bet > MAX_BET_SINGLE || Bet < MIN_BET)
	{
		cout << "Invalid bet." << endl;
		cout << "Enter bet (Min bet is 1, Max bet is 10): "; 
		cin >> Bet;
	}

	//now, getting the player to input the numbers they want to bet on and validating that they didn't already pick them
	int currentBet;
	for (int i = 1; i <= NumberOfBets; i++)
	{
		cout << "Enter the number you wish to bet on: ";
		cin >> currentBet;
		while (currentBet < 0 || currentBet > NUMBER_OF_POCKETS) //validation (on the wheel)
		{
			cout << "That number isn't on wheel! Enter a new one: ";
			cin >> currentBet;
		}
		while (find(BettedNumbers.begin(),BettedNumbers.end(), currentBet) != BettedNumbers.end()) //validation (not already betted)
		{
			cout << "Already betted on that number. Enter a new one: ";
			cin >> currentBet;
		}
		BettedNumbers.push_back(currentBet);
	}
}

//function for other bet choices to get the bet from player and stores it in the Bet variable
void Roulette::GetBet()
{
	cin >> Bet;
	//making sure bet is valid
	while (Bet > PlayerMoney.GetCurrentAmountOfMoney() || Bet > MAX_BET || Bet < MIN_BET)
	{
		cout << "Invalid bet." << endl;
		cout << "Enter bet (Min bet is 1, Max bet is 100): "; 
		cin >> Bet;
	}
}

//function that determine what the player wins or loses bet wise
void Roulette::EvaluateOutcome(int winningPocket)
{
	if (RedBet) //Wins if pocket is red
	{
		if (Pockets[winningPocket] == RED)
		{
			cout << "You win! You win your bet back plus half!" << endl;
			PlayerMoney.WonBet(Bet,.5); //since bet was never taken out, just add the half
		}
		else
		{
			cout << "You lose. You lose your bet." << endl;
			PlayerMoney.LoseBet(Bet);
		}
	}
	else if (BlackBet) //Wins if pocket is black
	{
		if (Pockets[winningPocket] == BLACK)
		{
			cout << "You win! You win your bet back plus half!" << endl;
			PlayerMoney.WonBet(Bet,.5); //since bet was never taken out, just add the half
		}
		else
		{
			cout << "You lose. You lose your bet." << endl;
			PlayerMoney.LoseBet(Bet);
		}
	}
	else if (EvenBet) //Wins if pocket is even
	{
		if (winningPocket % 2 == 0)
		{
			cout << "You win! You win your bet back plus half!" << endl;
			PlayerMoney.WonBet(Bet,.5); //since bet was never taken out, just add the half
		}
		else
		{
			cout << "You lose. You lose your bet." << endl;
			PlayerMoney.LoseBet(Bet);
		}
	}
	else if (OddBet) //Wins if pocket is odd
	{
		if (winningPocket % 2 != 0)
		{
			cout << "You win! You win your bet back plus half!" << endl;
			PlayerMoney.WonBet(Bet,.5); //since bet was never taken out, just add the half
		}
		else
		{
			cout << "You lose. You lose your bet." << endl;
			PlayerMoney.LoseBet(Bet);
		}
	}
	else //for range and single bets
	{
		if (find(BettedNumbers.begin(), BettedNumbers.end(), winningPocket) != BettedNumbers.end()) //if player has the number landed on
		{
			cout << "One of your numbers was landed on!" << endl;
			if (RangeBet)
			{
				cout << "You win your bet back plus half!" << endl;
				PlayerMoney.WonBet(Bet,.5); //since bet was never taken out, just add the half
			}
			else
			{
				cout << "You win double your bet!" << endl;
				PlayerMoney.WonBet(Bet);
				if (NumberOfBets - 1 != 0)
				{
					cout << "However, you also lose money from your other numbers." << endl;
					PlayerMoney.LoseBet(Bet * (NumberOfBets - 1));
				}
			}
		}
		else
		{
			cout << "Your number was not landed on!" << endl;
			cout << "You lose you bet(s)" << endl;
			PlayerMoney.LoseBet(Bet * NumberOfBets);
		}
	}
}

//function to display ASCII art roulette wheel
void Roulette::DisplayBoard()
{
	cout << endl;
	cout << "        $$$$$$$$$$" << endl;
	cout << "      $$$$$$$$$$$$$$" << endl;
	cout << "    $$$$$$      $$$$$$" << endl;
	cout << "  $$$$$$     .    $$$$$$" << endl;
	cout << " $$$$$$      .     $$$$$$" << endl;
	cout << "$$$$$       ...      $$$$$" << endl;
	cout << "$$$$$     ...+...    $$$$$" << endl;
	cout << "$$$$$       ...      $$$$$" << endl;
	cout << " $$$$$$      .     $$$$$$" << endl;
	cout << "  $$$$$$     .    $$$$$$" << endl;
	cout << "    $$$$$$      $$$$$$" << endl;
	cout << "      $$$$$$$$$$$$$$" << endl;
	cout << "        $$$$$$$$$$" << endl;
	cout << endl;
}