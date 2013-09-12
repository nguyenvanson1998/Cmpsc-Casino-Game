//Craps.h - header class for craps minigame (dice)
//Written by Emma Roudabush

#pragma once

#include "Game.h"
#include "Dice.h"
#include <iostream>

using namespace std;

class Craps : public Game
{
public:
	//default constructor which calls its superclass
	Craps(const Money& playerMoney): Game(playerMoney) {}

	//function to play the game
	int Play();

	//function to display an ASCII craps board
	void DisplayBoard();

	//function to proceed with play if player chooses to do a Pass line Bet
	void PassLineBet();

	//function to proceed with play if player chooses to do a Pass line Bet
	void DontPassBet();

private:
	int CurrentPoint; //for betting
	Dice PairOfDice; //for the gameplay
};