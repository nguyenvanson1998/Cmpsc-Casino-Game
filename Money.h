//Money.h - header class for money management
//Written by Emma Roudabush

#pragma once

class Money
{
public:
	Money(int amountOfMoney = 0)
	{
		AmountOfMoney = amountOfMoney;
	}

	bool HasMoney() const
	{
		return (AmountOfMoney > 0);
	}

	void SetMoney(int amountOfMoney)
	{
		AmountOfMoney = amountOfMoney;
	}

	int GetCurrentAmountOfMoney()
	{
		return AmountOfMoney;
	}

	void LoseBet(int amountBetted)
	{
		AmountOfMoney -= amountBetted;
	}

	void WonBet(int amountBetted, double payout = 1.0)
	{
		AmountOfMoney = AmountOfMoney + int(amountBetted * payout);
	}

private:
	int AmountOfMoney;
};