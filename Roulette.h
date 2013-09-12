//Roulette.h - header class for roulette minigame
//Written by Emma Roudabush

#pragma once

#include "Game.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Roulette : public Game
{
public:
	//default constructor for game
	Roulette(const Money& playerMoney): Game(playerMoney)
	{
		if (Pockets.empty())
			PreLoadPockets();
	}

	//function that ultimately drives the game play
	//directs player to appropriate functions for continued play
	int Play();

	//function to determine where the "ball" lands on the roulette wheel
	//returns the number landed on
	int SpinWheel();

	//function to reset all the variables for another game
	void ResetGame();

	//function that allows players to make multiple bets
	void MakeBets();

	//function that determine what the player wins or loses bet wise
	void EvaluateOutcome(int winningPocket);

	//function to, if the player choices to pick numbers, let's them pick their choices
	void SingleNumberBets();

	//function for other bet choices to get the bet from player and stores it in the Bet variable
	void GetBet();

	//static function to preload the Pocket's map
	static void PreLoadPockets();

	//static map giving the color value of each number on roulette wheel
	//int being it's integer value and char being it's color (either r, g, or b)
	static map<int, string> Pockets; 

	//function to display ASCII art roulette table
	void DisplayBoard();

private:
	//boolean variables to see if player choose a broad spectrum of betting style in roulette
	bool RedBet;
	bool BlackBet;
	bool EvenBet;
	bool OddBet;
	bool RangeBet;

	//integer variable for player's bet
	int Bet;
	int NumberOfBets;

	//vector to hold the numbers betted on
	vector<int> BettedNumbers;
};