#include "Board.h"
Board::Board() {
	
}

Board::~Board() {

}

void Board::setCardOnBoard(Card card) {
	cardsOnBoard.push_back(card);
}

std::vector<Card> Board::getCardsOnBoard() {
	return cardsOnBoard;
}

Card Board::getCard(unsigned int &ind) {
	return cardsOnBoard.at(ind-1);
}

void Board::showCards() {
	int index = 1;
	for (Card var : cardsOnBoard) {
		std::cout << "Card no " << index << " is:" << static_cast<int>(var.getValue()) << " of " << static_cast<int>(var.getSign()) << std::endl;
		index++;
	}

}

void Board::removeCardOnBoard(unsigned int& position) {
	if (cardsOnBoard.size()==0) {
		std::cerr << "Malfunction in the game, no cards to take from the table";
	}
	else {
		this->cardsOnBoard.erase(cardsOnBoard.begin() + position, cardsOnBoard.begin() + position + 1);
		
	}
}

std::vector<int> Board::getPointRepresentation() {
	cardsOnBoardPointRepresentation.clear();
	for (int in = 0; in < this->cardsOnBoard.size(); in++) {
		cardsOnBoardPointRepresentation.push_back(static_cast<int>(cardsOnBoard.at(in).getValue()));
	}
	return cardsOnBoardPointRepresentation;
}

void Board::setPointRepresentation() {

	for (int in = 0; in < this->cardsOnBoard.size(); in++) {
		cardsOnBoardPointRepresentation.push_back(static_cast<int>(cardsOnBoard.at(in).getValue()));
	}

}
