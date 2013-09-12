//Game.h - Subclass game declaration
//Written by Emma Roudabush

#pragma once

#include "Money.h"
#include <iostream>

//virtual class game used for the basis of all games
class Game
{
public:
	Game(const Money& playerMoney)
	{
		PlayerMoney = playerMoney;
		WantsToContinue = true;
	}

	virtual int Play()
	{
		return PlayerMoney.GetCurrentAmountOfMoney();
	}

protected:
	Money PlayerMoney;
	bool WantsToContinue;
};