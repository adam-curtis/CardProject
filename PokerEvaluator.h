#pragma once
#include "Card.h"

using namespace std;

class PokerEvaluator
{
	
public:
	PokerEvaluator(Card c1, Card c2, Card c3, Card c4, Card c5, Card c6, Card c7);
	void evaluateHand(Card c1, Card c2, Card c3, Card c4, Card c5, Card c6, Card c7);
	string getBestHand();

private:
	string bestHand;
};