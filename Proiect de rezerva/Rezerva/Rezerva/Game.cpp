#include "Game.h"

void Game::starteGame() {

	getDeckReady();
	getPlayersReady();
	getBoardReady();
	while (this->deckOnTable.getDeckSize() >= playersCount) {
		playing();
	}
	winner();
	
}

void Game::getDeckReady() {
	this->deckOnTable.shuffle();
}

void Game::getPlayersReady() {
	char answer;

	std::cout << "Number of players (type a number between 2 and 4): ";
	std::cin >> playersCount;
	while (!checkPlayersNumber(playersCount)) {
		std::cout << "Number of players (type a number between 2 and 4): ";
		std::cin >> playersCount;
		checkPlayersNumber(playersCount);
	}
	this->players.reserve(playersCount + 1);
	for (int in = 1; in <= playersCount; in++) {
		Player player;
		player.setPlayerTurn(in);
		if (in == 1) {
			std::cout << "Turn - player 1." << std::endl;
			assignCard(player, 4);
			std::cout << "The cards for player 1 are: " << std::endl;
			player.showCards();
			std::cout << "Would you like to keep them? (Y/N): ";
			std::cin >> answer;
			if (answer == 'n' || answer == 'N') {
				refusedHand = player.getCards();
				player.removeCards();
				assignCard(player, 6);
			}
			players.push_back(player);
			std::cout << "Player 1 turn  is over." << std::endl << std::endl;;
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
		else {
			std::cout << "Turn - player" << in << std::endl;
			std::cout << "The cards for player " << in << " are:" << std::endl;
			assignCard(player, 6);
			player.showCards();
			players.push_back(player);
			std::cout << "Player " << in << " turn  is over." << std::endl << std::endl;;
			std::this_thread::sleep_for(std::chrono::seconds(5));
		}
	}
	if(refusedHand.empty())
		assignCard(players.at(0), 2);
}

void Game::getBoardReady() {
	assignMainDeck(4);
}

bool Game::checkPlayersNumber(const int &in) {
	if (in > 4) {
		std::cerr << "Too many players selected. Please choose a number between 2 and 4";
		return false;
	}
	else if (in <= 1) {
		std::cerr << "Not enough players. Please choose a number between 2 and 4";
		return false;
	}
	return true;
	
}

void Game::assignCard(Player &player, const int &howMany) {
	
	for (int in = 0; in < howMany; in++) {
		player.setCards(this->deckOnTable.getFirstCard());
		deckOnTable.removeFirstCard();
	}
}

void Game::assignMainDeck(const int& howMany) {
	if (deckOnTable.getDeckSize() < howMany) {
		std::cerr << "Not enough cards in the deck. Game over." << std::endl;
		winner();
	}
	else {
		for (int in = 0; in < howMany; in++) {
			cardsOnTable.setCardOnBoard(deckOnTable.getFirstCard());
			deckOnTable.removeFirstCard();
		}
	}
}

void Game::reassignCards() {
	int howMany = deckOnTable.getDeckSize() / playersCount;

	for (Player ply : players) {
		if (howMany < 6) {
			for (int in = 0; in < howMany; in++) {
				ply.setCards(this->deckOnTable.getFirstCard());
				deckOnTable.removeFirstCard();
			}
		}
		else {
			assignCard(ply, howMany);
		}
		
	}
	//playing();
}

void Game::playing() {
	this->rounds++;
	char answer = NULL;
	
	std::vector<int> option;

	if (refusedHand.size() != 0) {
		std::cout << "The refused hand was: "<<std::endl;
		showRefusedHand();
	}

	for (Player ply : this->players) {
		if (emptyHands == players.size())
			reassignCards();
		unsigned int index = 0;
		if (ply.getCards().size() == 0) {
			std::cerr << "No more cards in your hand. Please wait until everyone finish their cards. ";
			emptyHands += 1;
		}
		else {
			std::cout << "Cards on the table are: " << std::endl;
			cardsOnTable.showCards();
			std::cout << std::endl << "Your cards are: " << std::endl;;
			ply.showCards();
			std::cout << std::endl;
			std::cout << "Do you want to take any card from the table? (Y/N): ";
			std::cin >> answer;
			if (answer == 'n' || answer == 'N') {
				std::cout << "What card do you want to put on the table? (insert card number): ";
				std::cin >> index;
				std::cout << std::endl;
				index--;
				residualDeck.push_back(ply.getCardAtPosition(index));
				players.at(ply.getPlayerTurn() - 1).removeCardAtPosition(index);
			}
			else {
				std::cout << "Do you want to use a card from your deck as reference or one from the board? " << std::endl;
				std::cout << "Type P to sum up cards from the board or B to sum up cards from your hand: ";
				std::cin >> answer;
				std::cout << std::endl;
				if (answer == 'P' || answer == 'p') {
					std::cout << "What card do you want to use from the ones in your hand? (insert card number): ";
					std::cin >> index;
					if (index < 1 || index>ply.getCards().size()) {
						std::cerr << "Please select a valid index. It should be between 1 and " << ply.getCards().size() << ": ";
						std::cin >> index;
					}
					else {
						unsigned int targetValue = ply.getPointRepresentation().at(index - 1);
						//const unsigned int in = cardsOnTable.getCardsOnBoard().size() + 1;
						std::vector<int> cardsOnTableRep = cardsOnTable.getPointRepresentation();
						checkMyCards(cardsOnTableRep, targetValue);
						answer = 'p';
						if (solutions.empty())
							std::cerr << "The card selected does not match any combination in your hand. " << std::endl;
						else if (solutions.size() > 1)
							showOptions(ply.getPlayerTurn(), answer, index);
						else {
							for (int i : solutions.at(0))
								option.push_back(i);
						addToWonBoard(option, ply.getPlayerTurn(), index);
							std::cout << "The only available option had been added to the won pack. " << std::endl << std::endl;
						}
						cardsOnTableRep.resize(0);
						//redoDecks(ply.getPlayerTurn(), index);
					}
				}
				else {
					std::cout << "What card do you want to use from the ones on the board? (insert card number): ";
					std::cin >> index;
					if (index < 1 || index>cardsOnTable.getCardsOnBoard().size()) {
						std::cerr << "Please select a valid index. It should be between 1 and " << ply.getCards().size() << ": ";
						std::cin >> index;
					}
					else {
						unsigned int targetValue = cardsOnTable.getPointRepresentation().at(index - 1);
						std::vector<int> cardsInHandRep = ply.getPointRepresentation();
						checkMyCards(cardsInHandRep, targetValue); 
						answer = 'b';
						if (solutions.empty()||solutions.size()==3)
							std::cerr << "The card selected does not match any combination on the table." << std::endl;
						else if (solutions.size() > 1)
							showOptions(ply.getPlayerTurn(), answer,index);
						else {
							for (int i : solutions.at(0))
								option.push_back(i);
							addToWonHand(option, ply.getPlayerTurn(), index);
							std::cout << "The only available option had been added to the won pack." << std::endl << std::endl;
						}
					}
				}
				
				for (std::vector<int> v : solutions)
					v.clear();
				solutions.clear();
				selectedOptions.clear();
				option.clear();
			}
		}
		std::cout << "Player " <<ply.getPlayerTurn() << " is over. In 4 sec will start the next turn." << std::endl << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(4));
		
	}
}

void Game::showRefusedHand() {
	for (Card var : this->refusedHand)
	{
		std::cout << "Card: " << static_cast<int>(var.getValue()) << " of " << static_cast<int>(var.getSign())<<std::endl;
	}
}

void Game::sumSubsets(std::vector<int> set, int n, unsigned int target){
	std::vector<int> arr;
	std::vector<int> solution;

	if (target != 0) {
		int* x = (int*)malloc(set.size() * sizeof(int));
		int j = set.size() - 1;
		while (n > 0)
		{
			x[j] = n % 2;
			n = n / 2;
			j--;
		}
		int sum = 0;

		for (int i = 0; i < set.size(); i++)
			if (x[i] == 1)
				sum = sum + set[i];
		if (sum == target)
		{
			for (int i = 0; i < set.size(); i++)
				if (x[i] == 1 && set[i] != 0)
					arr.push_back(set[i]);
		}
		if (!arr.empty()&&arr.size()<=2)
			this->solutions.push_back(arr);
		free(x);
	}
	else {

		solution.clear();
		arr.clear();
		set.clear();
	}
	
}

void Game::checkMyCards(std::vector<int> set, unsigned int targetSum){
	int x = pow(2, set.size());
	for (int i = 1; i < x; i++)
		sumSubsets(set, i, targetSum);
	sumSubsets(set, x, 0);
	set.clear();

}

void Game::showOptions(int ind, char &typ, unsigned int &in) {
	unsigned int index=1;
	unsigned int option;
	
	for (std::vector<int> v : solutions) {
		std::cout << "Option no " << index << ": ";
		for (int x : v)
			std::cout << x<<' ';
		std::cout << std::endl;
		index++;
	}
	std::cout << "What option do you prefer? Insert option number:  ";
	std::cin >> option;
	std::cout << std::endl;
	if (option<0 || option>index) {
		std::cerr << "Invalid option. Please select an option between 1 and " << index;
	}
	for (int i : solutions.at(option - 1))
		selectedOptions.push_back(i);
	if (typ == 'p')
		addToWonBoard(selectedOptions, ind, in);
	else
		addToWonHand(selectedOptions, ind, in);
}

void Game::addToWonBoard(std::vector<int> option, int in, unsigned int& opt) {
	Card card;
	unsigned int removed=0;
	unsigned int cardsToAddBoard = 0;
	unsigned int index = 0;
	std::vector<Card> vect = cardsOnTable.getCardsOnBoard();
	for (int ind = 0; ind < option.size(); ind++)
	{
		for (Card c : vect) {
			index = index - removed;
			if (static_cast<int>(c.getValue()) == option.at(ind)) {
				players.at(in - 1).setWonCard(c);
				if (removed != 0) {
					index += removed;
					cardsOnTable.removeCardOnBoard(index);
				}
				else {
					cardsOnTable.removeCardOnBoard(index);
				}
				cardsToAddBoard++;
				removed += 1;
				index++;
			}else
				index++;

		}
	}	
	if (cardsToAddBoard == 4) {
		std::cout << "You just made a board!" << std::endl<< "Extra point has been added!" << std::endl;
		unsigned int value = players.at(in - 1).getBoards();
		value++;
		players.at(in - 1).setBoards(value);
	}
	opt -= 1;
	players.at(in - 1).setWonCard(players.at(in-1).getCardAtPosition(opt));
	players.at(in - 1).removeCardAtPosition(opt);
	vect.clear();
	assignMainDeck(cardsToAddBoard);
}

void Game::addToWonHand(std::vector<int> option, int in, unsigned int& opt) {
	Card card;
	unsigned int removed = 0;
	unsigned int cardsToAddHand = 0;
	unsigned int index = 0;
	std::vector<Card> vect = players.at(in-1).getCards();
	for (int ind = 0; ind < option.size(); ind++){
		for (Card c : vect) {
			index = index - removed;
			if (static_cast<int>(c.getValue()) == option.at(ind)) {
				players.at(in - 1).setWonCard(c);
				if (removed != 0) {
					index += removed;
					players.at(in - 1).removeCardAtPosition(index);
				}
				else {
					players.at(in - 1).removeCardAtPosition(index);
				}
				removed += 1;
				index++;
			}
			else
				index++;
		}
	}

	opt -= 1;
	players.at(in - 1).setWonCard(cardsOnTable.getCard(opt));
	cardsOnTable.removeCardOnBoard(opt);
	assignMainDeck(1);
	vect.clear();
	//assignCard(players.at(in - 1), cardsToAddHand);
}

void Game::redoDecks(unsigned int ind,unsigned int &in) {
	in--;
	players.at(ind - 1).setWonCard(players.at(ind - 1).getCardAtPosition(in));
	players.at(ind - 1).removeCardAtPosition(in);
	//assignCard(players.at(ind - 1), 1);
}

void Game::winner() {
	int winner = 0;
	int max = 0;
	for (Player ply : players) {
		if (ply.getPoints() > max) {
			max = ply.getPoints();
			winner = ply.getPlayerTurn();
		}
	}
	std::cout << "The winner is player no " << winner << ". This player accumulated " << max << " points." << std::endl;
}
