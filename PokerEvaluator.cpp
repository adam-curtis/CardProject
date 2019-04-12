#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Card.h"
#include "PokerEvaluator.h"

PokerEvaluator::PokerEvaluator(Card c1, Card c2, Card c3, Card c4, Card c5, Card c6, Card c7)
{
	pokerHand.push_back(c1);
	pokerHand.push_back(c2);
	pokerHand.push_back(c3);
	pokerHand.push_back(c4);
	pokerHand.push_back(c5);
	pokerHand.push_back(c6);
	pokerHand.push_back(c7);
}

string PokerEvaluator::getBestHand()
{
	vector<int> suits(4);
	map<int, vector<Card>> cardNums;
	vector<Card> straight;
	bool typeOfFlush = false;
	bool typeOfStraight = false;
	for (int i = 0; i < 14; i++)
	{
		vector<Card> v;
		cardNums.insert(pair<int,vector<Card>>(i, v));
	}

	for (int i = 0; i < pokerHand.size(); i++)
	{
		int cardValue = pokerHand[i].getNumericValue();
		string tempSuit = pokerHand[i].getSuit();

		if (cardValue == 14)
		{
			cardNums[0].push_back(pokerHand[i]);
			cardNums[13].push_back(pokerHand[i]);
		}
		else
		{
			cardNums[cardValue - 1].push_back(pokerHand[i]);
		}
		
		if (tempSuit == "Spades")
			suits[0]++;
		else if (tempSuit == "Hearts")
			suits[1]++;
		else if (tempSuit == "Clubs")
			suits[2]++;
		else if(tempSuit == "Diamonds")
			suits[3]++;
	}

	int counter = 0;
	for (int i = 0; i < cardNums.size(); i++)
	{
		if (cardNums[i].size() != 0)
		{
			for (int j = 0; j < cardNums[i].size(); j++)
			{
				straight.push_back(cardNums[i][j]);
			}
			counter++;
		}
		else
		{
			if (counter >= 5)
			{
				break;
			}
			straight.clear();
			counter = 0;
		}
	}

	if (counter >= 5)
	{
		typeOfStraight = true;
		vector<int> suit_counter(4);
		for (int i = 0; i < straight.size(); i++)
		{
			if (straight[i].getSuit() == "Spades")
				suit_counter[0]++;
			else if (straight[i].getSuit() == "Hearts")
				suit_counter[1]++;
			else if (straight[i].getSuit() == "Clubs")
				suit_counter[2]++;
			else if (straight[i].getSuit() == "Diamonds")
				suit_counter[3]++;
		}

		for (int i = 0; i < suit_counter.size(); i++)
		{
			if (suit_counter[i] >= 5)
			{
				for (int j = 0; j < straight.size(); j++)
				{
					if (straight[j].getNumericValue() == 14)
					{
						continue;
					}
					else if (straight[j].getNumericValue() < 10)
					{
						return "Straight Flush";
					}
				}
				return "Royal Flush";
			}
		}
	}
	//--Four of a kind
	bool threeOfAKind = false;
	bool onePair = false;
	bool twoPair = false;
	for (int i = 0; i < cardNums.size(); i++)
	{
		if (cardNums[i].size() == 4)
		{
			return "Four of a Kind";
		}
		else if (cardNums[i].size() == 3 && !threeOfAKind)
		{
			threeOfAKind = true;
		}
		else if (cardNums[i].size() >= 2)
		{
			if (onePair)
			{
				twoPair = true;
			}
			else
			{
				onePair = true;
			}
		}

	}
	//--Full House
	if (threeOfAKind && onePair)
	{
		return "Full House";
	}

	for (int i = 0; i < suits.size(); i++)
	{
		if (suits[i] >= 5)
		{
			typeOfFlush = true;
		}
	}

	if (typeOfFlush)
	{
		return "Flush";
	}
	else if (typeOfStraight)
	{
		return "Straight";
	}
	//--Three of a kind
	if (threeOfAKind)
	{
		return "Three of a Kind";
	}
	else if (twoPair)
	{
		return "Two Pair";
	}
	else if (onePair)
	{
		return "One Pair";
	}

	for (int i = cardNums.size() - 1; i >= 0; i--)
	{
		if (cardNums[i].size() == 1)
		{
			if (i == 13)
				return "A High";
			else if (i == 12)
				return "K High";
			else if (i == 11)
				return "Q High";
			else if (i == 10)
				return "J High";
			else
				return (i + 1) + " High";
		}
	}
}


