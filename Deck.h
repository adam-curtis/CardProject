#pragma once
#include<vector>
#include<string>
#include "Card.h"

using namespace std;

class Deck
{
	public:
		Deck();
		void shuffleDeck();
		void generateDeck();
		vector<Card> getDeck();
		
	private:
		vector<Card> card_deck;
};