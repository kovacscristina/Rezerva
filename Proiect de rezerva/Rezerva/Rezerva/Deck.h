#pragma once
#include <vector>
#include "Card.h"
#include <time.h>
#include <stdlib.h>
#include "Player.h"
#include <algorithm>
#include <random>
#include <chrono>


class Deck
{
public:

	void shuffle();
	Card getFirstCard();
	void removeFirstCard();
	void showDeck();
	int getDeckSize();


private:
	std::vector<Card> deckOnTable;

};
