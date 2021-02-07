#include "Deck.h"

void Deck::shuffle() {

	for (unsigned sign = 1; sign <= 4; sign++) {
		for (unsigned number = 1; number <= 14; number++)
		{
			if (number == 11) {

			}
			else {
				Card card;
				card.setSign(sign);
				card.setValue(number);
				this->deckOnTable.push_back(card);
			}
		}
	}
	
	//unsigned num = chrono::system_clock::now().time_since_epoch().count();
	std::random_shuffle(deckOnTable.begin(), deckOnTable.end());
}

Card Deck::getFirstCard() {
	return this->deckOnTable.front();
}

void Deck::removeFirstCard() {
	this->deckOnTable.erase(deckOnTable.begin());
}

void Deck::showDeck() {

}

int Deck::getDeckSize() {
	return static_cast<int>(deckOnTable.size());
}


