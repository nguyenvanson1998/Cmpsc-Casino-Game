//DeckOfCards.cpp -- class initialization
//Written by Emma Roudabush

#include "DeckOfCards.h"

#include <vector>
#include <math.h>
#include <time.h>

#define NUMBER_OF_CARDS_IN_SUIT		4
#define NUMBER_OF_CARDS_IN_DECK		Deck.size()

using namespace std;

//Default constructor
DeckOfCards::DeckOfCards()
{
	MakeNewDeck();
}

//function to create new deck, putting all 52 cards in the vector
void DeckOfCards::MakeNewDeck()
{
	//Putting Aces in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('A');
		
	//Putting Kings in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('K');

	//Putting Queens in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('Q');

	//Putting Jacks in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('J');

	//Putting 10s in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('0');
		
	//Putting 9s in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('9');
		
	//Putting 8s in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('8');

	//Putting 7s in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('7');
				
	//Putting 6s in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('6');
				
	//Putting 5s in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('5');
				
	//Putting 4s in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('4');

	//Putting 3s in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('3');

	//Putting 2s in Deck 
	for (int i = 1; i <= NUMBER_OF_CARDS_IN_SUIT; i++)
		Deck.push_back('2');
}

char DeckOfCards::DealCard()
{
	srand(time(NULL)); //to makes sure rand won't be seeded the same every time
				       //meaning the random generator won't follow the same sequence

	int indexOfCard = rand()%NUMBER_OF_CARDS_IN_DECK;
	char card = Deck[indexOfCard];
	Deck.erase(Deck.begin() + indexOfCard);

	return card;
}
