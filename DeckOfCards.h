//DeckOfCards.h -- class declaration for a deck of cards (for blackjack)
//Written by Emma Roudabush

#pragma once

#include <string>
#include <vector>

using namespace std;

class DeckOfCards
{
public:
	DeckOfCards();
	//function to create new deck, putting all 52 cards in the vector
	void MakeNewDeck();
	char DealCard();

private:
	vector <char> Deck; 
};