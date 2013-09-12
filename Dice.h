//Dice.h - dice class declaration for use by Craps
//Written by Emma Roudabush

#pragma once

#include <vector>
#include <math.h>
#include <time.h>

#define DICE_POSSIBILITIES	6
#define LOWEST_NUMBER		1

using namespace std;

class Dice
{
public:
	//default constructor 
	Dice();

	//function to roll the dice and give the random values to the private variables
	void RollDice();

	//funcion that gives the integer value of the two dice faces combined
	unsigned int ValueOfPair();
private:
	unsigned int DiceFaceOne;
	unsigned int DiceFaceTwo;
};
