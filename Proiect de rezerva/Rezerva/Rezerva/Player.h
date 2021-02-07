#pragma once
#include<type_traits>
#include <cstdint>
#include <vector>
#include "Card.h"

class Player
{
public:
	Player() = default;
	/*Player(std::vector<Card> cards, std::vector<int> cardPointRepresentation, int points,int boards,int playerTurn);
	~Player();*/

	void setPoints(const int& point);
	int getPoints();

	void setBoards(const int& board);
	int getBoards();

	void setPlayerTurn(const int& trn);
	int getPlayerTurn();

	void setCards(const Card card);
	std::vector<Card> getCards() ;

	Card getCardAtPosition(unsigned int& position);
	void removeCardAtPosition(unsigned int& position);

	std::vector<int> getPointRepresentation();
	void setPointRepresentation();

	std::vector<Card> getWonCards();
	void setWonCard(Card card);

	void showCards();

	void removeCards();

	void countPoints();

private:
	std::vector<Card> cards;
	std::vector<int> cardPointRepresentation;
	std::vector <Card> wonCards;
	int points;
	int boards;
	int playerTurn;
};

