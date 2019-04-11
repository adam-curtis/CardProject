#include <iostream>
#include <string>
#include "Card.h"
#include "PokerEvaluator.h"

PokerEvaluator::PokerEvaluator(Card c1, Card c2, Card c3, Card c4, Card c5, Card c6, Card c7)
{
	evaluateHand(c1, c2, c3, c4, c5, c6, c7);
}

void PokerEvaluator::evaluateHand(Card c1, Card c2, Card c3, Card c4, Card c5, Card c6, Card c7)
{
	
}

string PokerEvaluator::getBestHand()
{
	return bestHand;
}

