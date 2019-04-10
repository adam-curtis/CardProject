#include "Deck.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <string>

using namespace std;

Deck::Deck()
{
	generateDeck();
};

void Deck::generateDeck()
{
	string suits[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
	for (int i = 0; i < 4; i++)
	{
		
		for (int j = 2; j <= 14; j++)
		{
			Card c(j, suits[i]);
			if (find(card_deck.begin(), card_deck.end(), c) == card_deck.end())
			{
				card_deck.push_back(c);
			}
		}
	}
}
vector<Card> Deck::getDeck()
{
	return card_deck;
}

void Deck::shuffleDeck()
{
	srand(time(NULL));
	random_shuffle(card_deck.begin(), card_deck.end());
}
