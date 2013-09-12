//Blackjack.cpp -- Blackjack class instantiation
//Written by Emma Roudabush

#include "Blackjack.h"
#include <iostream>

#define MAX_BET								100
#define MIN_BET								1
#define BET_CHOICE							1
#define LEAVE_CHOICE						2
#define BLACKJACK							21
#define DEALERS_SECOND_CARD					1
#define HIT_CHOICE							1
#define FOLD_CHOICE							3
#define STAND_CHOICE						2
#define MAX_HIT_VALUE						16

//card value definitions
#define ACE_INITIAL							11
#define ACE_CHANGE							10
#define FACE_CARD_VALUE						10
#define CHANGE_TO_INTEGER					'0'

using namespace std;

//function to give the player the option to play or leave
//(ultimately the function that starts the game)
int Blackjack::Play()
{
	system("CLS"); //clearing the board
	cout << "Welcome to Blackjack!" << endl;

	while (PlayerMoney.HasMoney() && WantsToContinue)
	{
		cout << "You have $" << PlayerMoney.GetCurrentAmountOfMoney() << " to bet with" << endl;
		
		//displays menu of choices for game decisions
		int playersChoice, bet;
		cout << "\nChoose what to do" << endl;
		cout << "1: Deal" << endl;
		cout << "2: End Program" << endl;
		cout << "Enter number here: ";
		cin >> playersChoice;

		switch(playersChoice)
		{
		default: 
			cout << "Invalid choice.\n" << endl;
			break;
		case BET_CHOICE:
			cout << "\n\nEnter bet (Max bet is 100): "; 
			cin >> bet;
			//making sure bet is valid
			while (bet > PlayerMoney.GetCurrentAmountOfMoney() || bet > MAX_BET || bet < MIN_BET)
			{
				cout << "Invalid bet." << endl;
				cout << "Enter bet (Min bet is 1, Max bet is 100): "; 
				cin >> bet;
			}
			MakeMoves(bet);
			break;
		case LEAVE_CHOICE:
			WantsToContinue = false;
			break;
		}
	}

	if (!PlayerMoney.HasMoney())
		cout << "\nYou are out of money!" << endl;

	cout << "Thanks for playing Blackjack!" << endl;

	return PlayerMoney.GetCurrentAmountOfMoney();
}

//function to deal out the inital hands to both sides
void Blackjack::Deal()
{
	PlayersHand.push_back(Deck.DealCard());
	PlayersHand.push_back(Deck.DealCard());

	DealersHand.push_back(Deck.DealCard());
	DealersHand.push_back(Deck.DealCard());
}

//function for the main play of the cards
//made for less clutter in the play() function
void Blackjack::MakeMoves(int bet)
{
	ResetSetup();
	int playersChoice;
	bool wantsToContinue = true;
	
	//Deal cards to players
	Deal();

	//Show initial configuration
	DealerDisplayBefore();
	cout << "\n\n\n";
	PlayerDisplay();

	if (GetPlayerTotal() == BLACKJACK) //first checking to see if player has gotten blackjack
	{
		cout << "Blackjack 21!! You win!" << endl;
		cout << "You get double your bet!" << endl;
		PlayerMoney.WonBet(bet); //will add another bet to the current money, since first bet was not originally taken out
								 //of the player's money total
	}
	else
	{
		while (!Bust() && wantsToContinue)
		{
			cout << "Your card total is... " << GetPlayerTotal() << endl;
			cout << "\nChoose what to do" << endl;
			cout << "1: Hit" << endl;
			cout << "2: Stand" << endl;
			cout << "3: Fold" << endl;
			cout << "Enter number here: ";
			cin >> playersChoice;

			switch(playersChoice)
			{
			default: 
				cout << "Invalid choice.\n";
				break;
			case HIT_CHOICE:
				PlayersHand.push_back(Deck.DealCard());
				//Show new configuration
				cout << "\n\n\n\n\n" << endl;
				DealerDisplayBefore();
				cout << "\n\n\n";
				PlayerDisplay();
				break;
			case FOLD_CHOICE:
				wantsToContinue = false;
				break;
			case STAND_CHOICE:
				wantsToContinue = false;
				break;
			}
		}
		
		if (Bust()) //if player goes over card value 21
		{
			cout << "Bust!" << endl;
			cout << "You lose your bet. :(" << endl;
			PlayerMoney.LoseBet(bet);
		}
		else if (playersChoice != FOLD_CHOICE)
		{
			DealersMove(bet);
			DetermineWinner(bet);
		}
		else //for those who folded (lose their bet)
		{
			cout << "You folded! You lose your bet." << endl;
			PlayerMoney.LoseBet(bet);
		}
	}
}

//function to determine what the dealer should do in response to the player's move
//and its initial hand
void Blackjack::DealersMove(int bet)
{
		cout << "\n\n\n\n\n" << endl;
		DealerDisplayAfter();
		cout << "\n\n\n";
		PlayerDisplay();

		if (GetDealerTotal() == BLACKJACK) //first checking to see if player has gotten blackjack
		{
			cout << "\nThe Dealer has blackjack!" << endl;
			cout << "You lose your bet. :(" << endl;
			PlayerMoney.LoseBet(bet); 
		}
		else
		{
			//hitting (or not)
			while(GetDealerTotal() <= MAX_HIT_VALUE && GetDealerTotal() < PlayersTotal)
			{
				//the dealer will hit if his hand's total value is less than a set value
				DealersHand.push_back(Deck.DealCard());
				
				cout << "The dealer hits!\n\n" << endl;
				DealerDisplayAfter();
				cout << "\n\n\n";
				PlayerDisplay();
			}
		}
}

//function to determine who has the winning hand (if not already busted, folded, or player blackjack)
//also deals with the player's bet in those cases
void Blackjack::DetermineWinner(int bet)
{
	//now comparing the two values
	if (DealersTotal > BLACKJACK)
	{
		cout << "\nThe dealer busts! You win!" << endl;
		cout << "You get twice your bet" << endl;
		PlayerMoney.WonBet(bet); //will add another bet to the current money, since first bet was not originally taken out
									//of the player's money total
	}
	else if (DealersTotal > PlayersTotal)
	{
		cout << "\nThe dealer has the greater value. The dealer wins." << endl;
		cout << "You lose your bet" << endl;
		PlayerMoney.LoseBet(bet);
	}
	else if (DealersTotal == PlayersTotal)
	{
		cout << "\nYou have the same values. Dealer wins" << endl;
		cout << "You lose your bet" << endl;
		PlayerMoney.LoseBet(bet);
	}
	else //player has greater value
	{
		cout << "\nYou have the greater value! You win!" << endl;
		cout << "You get twice your bet" << endl;
		PlayerMoney.WonBet(bet); //will add another bet to the current money, since first bet was not originally taken out
								//of the player's money total
	}
}

//function that determines the numerical total of player's hand
int Blackjack::GetPlayerTotal()  //cannot be const because it modifies the "PlayersTotal" element
{
	int sum = 0;
	int numOfAcesAtMax = 0;
	for (unsigned int i = 0; i < PlayersHand.size(); i++)
	{
		switch(PlayersHand[i])
		{
		case 'A':
			sum += ACE_INITIAL; //initally assume that an Ace's value is 11
			numOfAcesAtMax++;
			break;
		case 'K':
		case 'Q':
		case 'J':
		case '0': 
			sum += FACE_CARD_VALUE;
			break;
		case '9':
		case '8':
		case '7':
		case '6':
		case '5':
		case '4':
		case '3':
		case '2':
			sum += (PlayersHand[i] - CHANGE_TO_INTEGER);
			break;
		}
		if (sum > BLACKJACK && numOfAcesAtMax > 0)
		{
			sum -= ACE_CHANGE;
			numOfAcesAtMax--;
		}
	}
	PlayersTotal = sum; // for future comparison
	return sum;
}

//function that determines the numerical total of dealer's hand
int Blackjack::GetDealerTotal() //cannot be const because it modifies the "DealersTotal" element
{
	int sum = 0;
	int numOfAcesAtMax = 0;
	for (unsigned int i = 0; i < DealersHand.size(); i++)
	{
		switch(DealersHand[i])
		{
		case 'A':
			sum += ACE_INITIAL; //initally assume that an Ace's value is 11
			numOfAcesAtMax++;
			break;
		case 'K':
		case 'Q':
		case 'J':
		case '0': 
			sum += FACE_CARD_VALUE;
			break;
		case '9':
		case '8':
		case '7':
		case '6':
		case '5':
		case '4':
		case '3':
		case '2':
			sum += (DealersHand[i] - CHANGE_TO_INTEGER);
			break;
		}
		if (sum > BLACKJACK && numOfAcesAtMax > 0)
		{
			sum -= ACE_CHANGE;
			numOfAcesAtMax--;
		}
	}
	DealersTotal = sum; // for future comparison
	return sum;
}

//function that returns true if player's total value is over 21, false otherwise
bool Blackjack::Bust() //cannot be const because GetPlayerTotal() isn't const
{
	return (GetPlayerTotal() > BLACKJACK);
}

//function that shows dealers second card (before dealers move)
void Blackjack::DealerDisplayBefore() const
{
	cout << "Dealers Hand: [] [" << DealersHand[DEALERS_SECOND_CARD] << "]" << endl; 
}

//function that displays dealers hand after/while dealers move
void Blackjack::DealerDisplayAfter() const
{
	cout << "Dealers Hand:";
	for (unsigned int i = 0; i < DealersHand.size(); i++)
		cout << " [" << DealersHand[i] << "]";
	cout << endl;
}

//function that displays players hand during/after player's move
void Blackjack::PlayerDisplay() const
{
	cout << "Your Hand:";
	for (unsigned int i = 0; i < PlayersHand.size(); i++)
		cout << " [" << PlayersHand[i] << "]";
	cout << endl;
}

//function to clear hands and totals if a new game is played
void Blackjack::ResetSetup()
{
	//deleting the players hand
	while (!PlayersHand.empty())
	{
		PlayersHand.pop_back();
	}

	//deleting the Dealers hand
	while (!DealersHand.empty())
	{
		DealersHand.pop_back();
	}

	PlayersTotal = 0;
	DealersTotal = 0;
}