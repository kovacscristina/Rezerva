#include "Card.h"

Card::Card(){

}

Card::~Card() {

}

Card::Number Card::getValue(){ 

	return cardValue;
}

void Card::setValue(const int& valu) {

	cardValue = static_cast<Number>(valu);
}

void Card::setValue(const Number& value){

	cardValue = value;
}

Card::Sign Card::getSign(){

	return cardSign;
}

void Card::setSign(const int& sng){

	cardSign = static_cast<Sign>(sng);
}

void Card::setSign(const Sign& sng){

	cardSign = sng;
}
