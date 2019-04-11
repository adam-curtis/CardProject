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
			if (find(cardDeck.begin(), cardDeck.end(), c) == cardDeck.end())
			{
				cardDeck.push_back(c);
			}
		}
	}
}
vector<Card> Deck::getDeck()
{
	return cardDeck;
}

void Deck::dealCards(int numCards)
{
	try
	{
		if ((size_t)numCards > cardDeck.size())
			throw "Number of requested cards are not in deck.";
		if (numCards < 0)
			throw "Please enter a positive number.";

		int currentDeckSize = cardDeck.size() - 1;
		for (int i = currentDeckSize; i > currentDeckSize - numCards; i--)
		{
			hand.push_back(cardDeck[i]);
			cardDeck.pop_back();
		}
	}
	catch(string e)
	{
		cout << "Exception: " + e << endl;
	}
}

void Deck::shuffleDeck()
{
	srand((unsigned)time(NULL));
	random_shuffle(cardDeck.begin(), cardDeck.end());
}
