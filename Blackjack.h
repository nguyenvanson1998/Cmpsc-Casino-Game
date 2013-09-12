//Blackjack.h - header class for blackjack minigame
//Written by Emma Roudabush

#pragma once

#include "Money.h"
#include "Game.h"
#include "DeckOfCards.h"
#include <iostream>

class Blackjack : public Game
{
public:
	//default constructor for game
	Blackjack(const Money& playerMoney) : Game(playerMoney){}
	
	//function to give the player the option to play or leave
	//(ultimately the function that starts the game)
	int Play();

	//function to deal out the inital hands to both sides
	void Deal();

	//function for the main play of the cards [Player moves]
	//made for less clutter in the play() function
	void MakeMoves(int bet);

	//function to determine what the dealer should do in response to the player's move
	//and its initial hand
	void DealersMove(int bet);
	
	//function to determine who has the winning hand (if not already busted, folded, or player blackjack)
	//also deals with the player's bet in those cases
	void DetermineWinner(int bet);

	//function that determines the numerical total of player's hand
	//cannot be const because it modifies the "PlayersTotal" element
	int GetPlayerTotal();
	
	//function that determines the numerical total of dealer's hand
	 //cannot be const because it modifies the "DealersTotal" element
	int GetDealerTotal();

	//function that returns true if player's total value is over 21, false otherwise
	//cannot be const because GetPlayerTotal() isn't const
	bool Bust();

	//function that shows dealers second card (before dealers move)
	void DealerDisplayBefore() const;

	//function that displays dealers hand after/while dealers move
	void DealerDisplayAfter() const;

	//function that displays players hand during/after player's move
	void PlayerDisplay() const;

	//function to clear hands and totals if a new game is played
	void ResetSetup();

private:
	DeckOfCards Deck; //Deck to play the card game
	
	vector <char> PlayersHand; //vector to hold the player's current hand
	int PlayersTotal;		   //the integer value of player's hand

	vector <char> DealersHand; //vector to hold the dealer's current hand
	int DealersTotal;          //the integer value of dealers's hand
};