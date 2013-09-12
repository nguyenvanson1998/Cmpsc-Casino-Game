//Dice.cpp - Dice class instantiation
//Written by Emma Roudabush

#include "Dice.h"

using namespace std;

//default constructor 
Dice::Dice() {}

//function to roll the dice and give the random values to the private variables
void Dice::RollDice()
{
	srand(time(NULL)); //to makes sure rand won't be seeded the same every time
				       //meaning the random generator won't follow the same sequence

	DiceFaceOne = rand() % DICE_POSSIBILITIES + LOWEST_NUMBER;
	DiceFaceTwo = rand() % DICE_POSSIBILITIES + LOWEST_NUMBER;
}

//funcion that gives the integer value of the two dice faces combined
unsigned int Dice::ValueOfPair()
{
	return DiceFaceOne + DiceFaceTwo;
}