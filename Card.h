#pragma once
#include <string>

using namespace std;

class Card
{
private:
	int cardNumber;
public:
	Card(int n, string s);

	string toString();

	int getNumericValue();
	void setNumericValue(int n);
	string getSuit();
	void setSuit(string s);
	bool operator==(Card const& rhs);
};