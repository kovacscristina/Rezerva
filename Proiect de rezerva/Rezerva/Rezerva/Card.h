#pragma once
#include <cstdint>
#include <iostream>

class Card
{
public:
	enum class Sign:int{
		//trefla
		Clubs = 1,
		//romb
		Diamonds = 2,
		//inima rosie
		Hearts = 3, 
		//inima neagra
		Spades = 4 
		
	};
	
	enum class Number:int{
		Joker=0,
		Ace = 1,
		Two = 2,
		Three = 3,
		Four = 4,
		Five = 5,
		Six = 6,
		Seven = 7,
		Eight = 8,
		Nine = 9,
		Ten = 10,
		Jack = 12,
		Queen = 13,
		King = 14
	};

public:
	Card();
	~Card();

	void setSign(const Sign& sng);
	void setSign(const int& sng);
	Sign getSign();
	void setValue(const Number& valu);
	void setValue(const int& valu);
	Number getValue();

private:
	Number cardValue;
	Sign cardSign;
};
