#pragma once
#include "Player.h"
#include "Deck.h"
#include "Board.h"
#include "Card.h"
#include <vector>
#include <thread>
#include <chrono>
class Game
{

public:
	void starteGame();
	void getDeckReady();
	void getPlayersReady();
	void getBoardReady();

	bool checkPlayersNumber(const int& in);

	void assignCard(Player &player, const int &howMany);
	void reassignCards();
	void assignMainDeck(const int& howMany);
	void playing();
	void showRefusedHand();
	void showOptions(int ind, char &typ, unsigned int &in);
	void addToWonBoard(std::vector<int> option, int ind, unsigned int& in);
	void addToWonHand(std::vector<int> option, int in, unsigned int &opt);

	void redoDecks(unsigned int ind,unsigned int &in);
	void checkMyCards(std::vector<int> sett, unsigned int target);
	void sumSubsets(std::vector<int> set, int n, unsigned int target);

	void winner();



private:
	std::vector<Player> players;
	std::vector<Card> refusedHand;
	std::vector<Card> residualDeck;
	Deck deckOnTable;
	Board cardsOnTable;
	int playersCount;
	unsigned int rounds;
	std::vector<std::vector<int>> solutions;	
	std::vector<int>selectedOptions;
	unsigned int emptyHands = 0;
};

