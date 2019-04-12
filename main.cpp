#include <iostream>
#include "Card.h"
#include "Deck.h"
#include "PokerEvaluator.h"
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

		//checks for bad cards
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
				//checks the creation of all 52 unique cards
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

		//checks the toString() method
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
		//in deck, if there are duplicates, the card will not be added again, if this returns 52, all cards are unique
		REQUIRE(tempDeck.size() == 52);
		//checks to see if all the cards have been shuffled
		REQUIRE(isShuffled == true);
	}

	SECTION("Deal Cards")
	{
		Deck d1;
		d1.dealCards(5);
		vector<Card> tempDeck = d1.getDeck();
		//checks to see if certain number of cards are moved from a deck into a hand
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
		//checks to see if the correct cards were removed from the deck and added to the hand, no duplicates should be found between the hand/deck
		REQUIRE(isUniqueHand == true);

		d1.dealCards(2);
		tempDeck = d1.getDeck();
		//checks to see if cards can be dealt more than once
		REQUIRE(tempDeck.size() == 45);
		REQUIRE(d1.hand.size() == 7);
		//throws exception if user enters invalid deck size
		REQUIRE_THROWS(d1.dealCards(100));
	}

}

TEST_CASE("Poker Evaluator")
{
	SECTION("Royal Flush, Straight Flush, Flush, Straight")
	{
		Card c1(10, "Spades");
		Card c2(11, "Spades");
		Card c3(12, "Spades");
		Card c4(13, "Spades");
		Card c5(14, "Spades");
		Card c6(5, "Hearts");
		Card c7(2, "Diamonds");

		//Royal Flush
		PokerEvaluator p1(c1, c2, c3, c4, c5, c6, c7);
		REQUIRE(p1.getBestHand() == "Royal Flush");

		//Straight flush
		Card c8(9, "Spades");
		PokerEvaluator p2(c1, c2, c3, c4, c8, c6, c7);
		REQUIRE(p2.getBestHand() == "Straight Flush");

		//not a flush, just a straight
		Card c9(12, "Hearts");
		PokerEvaluator p3(c1, c2, c9, c4, c5, c6, c7);
		REQUIRE(p3.getBestHand() == "Straight");

		//Not straight or royal flush
		Card c10(2, "Spades");
		PokerEvaluator p4(c1, c2, c10, c4, c5, c6, c7);
		REQUIRE(p4.getBestHand() == "Flush");

		//Flush and straight, not straight flush
		Card c11(10, "Hearts");
		Card c12(4, "Spades");
		PokerEvaluator p5(c11, c2, c3, c4, c5, c6, c12);
		REQUIRE(p5.getBestHand() == "Flush");
	}

	SECTION("Test Low Ace Straight")
	{
		Card c1(2, "Spades");
		Card c2(3, "Spades");
		Card c3(4, "Spades");
		Card c4(5, "Spades");
		Card c5(14, "Spades");
		Card c6(5, "Hearts");
		Card c7(2, "Diamonds");
		PokerEvaluator p1(c1, c2, c3, c4, c5, c6, c7);
		REQUIRE(p1.getBestHand() == "Straight Flush");
	}

	SECTION("Test 4 of a kind")
	{
		Card c1(2, "Diamonds");
		Card c2(5, "Hearts");
		Card c3(5, "Spades");
		Card c4(5, "Hearts");
		Card c5(14, "Spades");
		Card c6(5, "Hearts");
		Card c7(2, "Diamonds");
		PokerEvaluator p1(c1, c2, c3, c4, c5, c6, c7);
		REQUIRE(p1.getBestHand() == "Four of a Kind");
	}

	SECTION("Test Full House")
	{
		Card c1(2, "Diamonds");
		Card c2(5, "Hearts");
		Card c3(4, "Spades");
		Card c4(5, "Hearts");
		Card c5(14, "Spades");
		Card c6(5, "Hearts");
		Card c7(2, "Diamonds");
		PokerEvaluator p1(c1, c2, c3, c4, c5, c6, c7);
		REQUIRE(p1.getBestHand() == "Full House");
	}

	SECTION("Test 3 of a kind")
	{
		Card c1(8, "Diamonds");
		Card c2(5, "Hearts");
		Card c3(7, "Spades");
		Card c4(5, "Hearts");
		Card c5(14, "Spades");
		Card c6(5, "Hearts");
		Card c7(2, "Diamonds");
		PokerEvaluator p1(c1, c2, c3, c4, c5, c6, c7);
		REQUIRE(p1.getBestHand() == "Three of a Kind");
	}

	SECTION("Test Two Pair")
	{
		Card c1(8, "Diamonds");
		Card c2(5, "Hearts");
		Card c3(7, "Spades");
		Card c4(5, "Hearts");
		Card c5(14, "Spades");
		Card c6(2, "Hearts");
		Card c7(2, "Diamonds");
		PokerEvaluator p1(c1, c2, c3, c4, c5, c6, c7);
		REQUIRE(p1.getBestHand() == "Two Pair");
	}

	SECTION("Test One Pair")
	{
		Card c1(8, "Diamonds");
		Card c2(5, "Hearts");
		Card c3(7, "Spades");
		Card c4(5, "Hearts");
		Card c5(14, "Spades");
		Card c6(9, "Hearts");
		Card c7(2, "Diamonds");
		PokerEvaluator p1(c1, c2, c3, c4, c5, c6, c7);
		REQUIRE(p1.getBestHand() == "One Pair");
	}

	SECTION("Test 3 of a kind")
	{
		Card c1(8, "Diamonds");
		Card c2(5, "Hearts");
		Card c3(7, "Spades");
		Card c4(9, "Hearts");
		Card c5(14, "Spades");
		Card c6(10, "Hearts");
		Card c7(2, "Diamonds");
		PokerEvaluator p1(c1, c2, c3, c4, c5, c6, c7);
		REQUIRE(p1.getBestHand() == "A High");
	}

}
