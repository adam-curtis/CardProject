#pragma once
#include<vector>
#include<string>
#include "Card.h"

using namespace std;

//Deck class
class Deck
{
	public:
		Deck();
		void shuffleDeck();
		void generateDeck();
		void dealCards(int numCards);
		vector<Card> getDeck();
		vector<Card> hand;
	private:
		vector<Card> cardDeck;
		
};