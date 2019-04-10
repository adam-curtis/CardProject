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
		vector<Card> temp = d1.getDeck();

		REQUIRE(temp.size() == 52);
		REQUIRE((temp[0].toString() == "2 of Clubs" && temp[1].toString() == "3 of Clubs" && temp[2].toString() == "4 of Clubs" && temp[3].toString() == "5 of Clubs" && temp[4].toString() == "6 of Clubs"));

		d1.shuffleDeck();
		temp = d1.getDeck();
		REQUIRE((temp[0].toString() != "2 of Clubs" || temp[1].toString() != "3 of Clubs" || temp[2].toString() != "4 of Clubs" || temp[3].toString() != "5 of Clubs" || temp[4].toString() != "6 of Clubs"));
	}

}
