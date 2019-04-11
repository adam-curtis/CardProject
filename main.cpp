#include <iostream>
#include "Card.h"
#include "Deck.h"
#include <unordered_set>
using namespace std;

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main()
{
	cout << "Hello World!!!" << endl;

	Catch::Session().run();

	return 0;
}

TEST_CASE("Test Cards")
{
	SECTION("Test create bad cards")
	{
		Card c1(-10, "Hearts");
		Card c2(10, "Fish");
		Card c3(-10, "Fish");

		REQUIRE(c1.getNumericValue() == 2);
		REQUIRE(c1.getSuit() == "Hearts");
		REQUIRE(c2.getNumericValue() == 10);
		REQUIRE(c2.getSuit() == "Clubs");
		REQUIRE(c3.getNumericValue() == 2);
		REQUIRE(c3.getSuit() == "Clubs");
	}

	SECTION("Test create 52 cards")
	{
		string suits[] = { "Clubs", "Diamonds", "Hearts", "Spades" };
		for (int i = 0; i < 4; i++)
		{
			for (int num = 2; num <= 14; num++)
			{
				Card c(num, suits[i]);
				REQUIRE(c.getNumericValue() == num);
				REQUIRE(c.getSuit() == suits[i]);
			}
		}
	}

	SECTION("Test toString()")
	{
		Card c1(2, "Hearts");
		Card c2(10, "Diamonds");
		Card c3(11, "Clubs");
		Card c4(14, "Spades");

		REQUIRE(c1.toString() == "2 of Hearts");
		REQUIRE(c2.toString() == "10 of Diamonds");
		REQUIRE(c3.toString() == "J of Clubs");
		REQUIRE(c4.toString() == "A of Spades");
	}
}

TEST_CASE("Test Deck")
{
	SECTION("Test Unique & Shuffle" )
	{
		Deck d1;
		vector<Card> tempDeck = d1.getDeck();
		d1.shuffleDeck();
		vector<Card> tempDeck2 = d1.getDeck();
		bool isShuffled = false;
		for (size_t i = 0; i < tempDeck.size(); i++)
		{
			if (!(tempDeck[i] == tempDeck2[i]))
				isShuffled = true;
		}
		REQUIRE(tempDeck.size() == 52);
		REQUIRE(isShuffled == true);
	}

	SECTION("Deal Cards")
	{
		Deck d1;
		d1.dealCards(5);
		vector<Card> tempDeck = d1.getDeck();
		REQUIRE(tempDeck.size() == 47);
		REQUIRE(d1.hand.size() == 5);

		bool isUniqueHand = true;
		for (size_t i = 1; i < d1.hand.size(); i++)
		{
			for (size_t j = 0; j < tempDeck.size(); j++)
			{
				if (d1.hand[i] == tempDeck[j])
					isUniqueHand = false;
			}
		}
		REQUIRE(isUniqueHand == true);

		d1.dealCards(2);
		tempDeck = d1.getDeck();
		REQUIRE(tempDeck.size() == 45);
		REQUIRE(d1.hand.size() == 7);
		REQUIRE_THROWS(d1.dealCards(100));
	}

}

TEST_CASE("Poker Evaluator")
{

}
