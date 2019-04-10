#include "Card.h"
#include <iostream>

using namespace std;

Card::Card(int n, string s)
{
	cardNumber = 0;
	setNumericValue(n);
	setSuit(s);
}
//--
string Card::toString()
{
	string retVal;
	int cardNumber = getNumericValue();
	if (cardNumber <= 10)
	{
		retVal = to_string(cardNumber);
	}
	else if(cardNumber == 11)
	{
		retVal = "J";
	}
	else if (cardNumber == 12)
	{
		retVal = "Q";
	}
	else if (cardNumber == 13)
	{
		retVal = "K";
	}
	else if (cardNumber == 14)
	{
		retVal = "A";
	}

	retVal = retVal + " of " + getSuit();

	return retVal;
}
//--
int Card::getNumericValue()
{
	return (cardNumber % 13) + 2;
}
//--
void Card::setNumericValue(int n)
{
	int suitStart = cardNumber / 13;
	if (n >= 2 && n <= 14)
	{
		cardNumber = suitStart + n - 2;
	}
	else
	{
		cardNumber = suitStart;
	}
}
string Card::getSuit()
{
	string suits[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
	return suits[cardNumber / 13];
}
//--
void Card::setSuit(string s)
{
	if (s == "Clubs") 
	{
		cardNumber = getNumericValue() - 2;
	}
	else if (s == "Diamonds")
	{
		cardNumber = 13 + getNumericValue() - 2;
	}
	else if (s == "Hearts")
	{
		cardNumber = 26 + getNumericValue() - 2;
	}
	else if (s == "Spades")
	{
		cardNumber = 39 + getNumericValue() - 2;
	}
	else
	{
		cardNumber = getNumericValue() - 2;
	}
}

bool Card::operator==(Card const& rhs)
{
	if (cardNumber == rhs.cardNumber)
		return true;
	return false;
}
