#pragma once
#include "Card.h"

#include<vector>
class Board
{
public:
	Board();
	~Board();

	void setCardOnBoard(Card card);
	std::vector<Card> getCardsOnBoard();
	Card getCard(unsigned int &ind);
	void removeCardOnBoard(unsigned int& position);

	std::vector<int> getPointRepresentation();
	void setPointRepresentation();
	void showCards();

private:
	std::vector<Card> cardsOnBoard;
	std::vector<int> cardsOnBoardPointRepresentation;
	unsigned int numberOfCardsOnBoard;
};

