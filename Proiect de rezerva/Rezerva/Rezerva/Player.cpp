#include "Player.h"

void Player::setPoints(const int& point){

	points = point;
}

int Player::getPoints(){

	return points;
}

void Player::setBoards(const int& board) {

	boards = board;
}

int Player::getBoards(){

	return boards;
}

void Player::setPlayerTurn(const int& ply) {
	
	playerTurn = ply;
}

int Player::getPlayerTurn() {

	return playerTurn;
}

void Player::setCards(const Card card){
	cards.emplace_back(card);
}

std::vector<Card> Player::getCards(){

	return cards;
}

Card Player::getCardAtPosition(unsigned int& position){

	if (cards.size() > position) {
		return cards.at(position);
	}
	else {
		std::cerr << "Invalid selection";
	}
}

void Player::removeCardAtPosition(unsigned int& position) {

	this->cards.erase(cards.begin() + position, cards.begin() + position + 1);
}

std::vector<int> Player::getPointRepresentation() {
	setPointRepresentation();
	return this->cardPointRepresentation;
}

void Player::setPointRepresentation() {

	for (int in = 0; in < this->cards.size(); in++) {
		cardPointRepresentation.push_back(static_cast<int>(cards.at(in).getValue()));
	}

}

std::vector<Card> Player::getWonCards() {
	return wonCards;
}

void Player::setWonCard(Card card) {
	wonCards.push_back(card);
}

void Player::showCards()
{
	int index = 1;
	for (Card var :this->cards)
	{
		std::cout << "Card no " << index << " is:" << static_cast<int>(var.getValue()) << " of "<< static_cast<int>(var.getSign())<<std::endl;
		index++;
	}

}

void Player::countPoints(){

	for (Card var : this->cards)
	{
		if (var.getSign() == Card::Sign::Diamonds) {
			if (var.getValue() == Card::Number::Ten)
				this->points = points + 2;
			else
				this->points = points + 1;
		}
		if (var.getSign() == Card::Sign::Clubs&& var.getValue() == Card::Number::Two)
			this->points = points + 2;
		if (var.getValue() == Card::Number::Ace ||
			var.getValue() == Card::Number::Jack ||
			var.getValue() == Card::Number::Queen ||
			var.getValue() == Card::Number::King)
			this->points = points + 1;
	}
	this->points = points + boards;
}

void Player::removeCards() {

	this->cards.clear();
}


