//Slots.h - header class for slots minigame
//Written by Emma Roudabush

#pragma once

#include <array>
#include "Game.h"
#include <iostream>

#define SLOTS_NUMBER	3

class Slots : public Game
{
public:
	Slots (const Money& playerMoney): Game(playerMoney){}
	int Play();
	void DisplaySlotFace();
	void Spin();
	int NumberOfMatchingFaces();
private:
	int SlotFaces [SLOTS_NUMBER]; 
};