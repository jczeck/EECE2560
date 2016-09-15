/* Card.cpp
*  Jenna Czeck
*  EECE 2560 Project 2
*  Implimentation of the card class
*/

#include "Card.h"

//Default constructor of card with value 2-Clubs
Card::Card() :
    value(TWO), suit(CLUBS) {
}

//Constructor of Card with initial values
Card::Card(value_t initValue, suit_t initSuit) :
    value(initValue), suit(initSuit) {

    //Throw exception if inputs are out of range
    if (initValue > 14 || initValue < 2) {
        throw rangeError("Initial value of card is out of range");
    }
    if (initSuit > 3 || initSuit < 0) {
        throw rangeError("Initial suit of card is out of range");
    }
}

//Set the value and throw exception if out of range
void Card::SetValue(value_t newValue) {
    if (newValue > 14 || newValue < 2) {
        throw rangeError("Value of card is out of range");
    }
    value = newValue;
}

//Set the suit and throw exception if out of range
void Card::SetSuit(suit_t newSuit) {
    if (newSuit > 3 || newSuit < 0) {
        throw rangeError("Suit of card is out of range");
    }
    suit = newSuit;
}

ostream& operator<<(ostream& os, const Card& card) {
    string valueDisp; // The string to output to represent value

    //What to output based off of the card value
    switch (card.value) {
    case(ACE) :
        valueDisp = "A";
        break;
    case(JACK) :
        valueDisp = "J";
        break;
    case(QUEEN) :
        valueDisp = "Q";
        break;
    case(KING) :
        valueDisp = "K";
        break;
    default:
        valueDisp = to_string(card.value);
    }

    string suitName; //String to hold representation of suit to output

    //Set what to output based on suit
    switch (card.suit) {
    case CLUBS:
        suitName = "Clubs";
        break;
    case DIAMONDS:
        suitName = "Diamonds";
        break;
    case HEARTS:
        suitName = "Hearts";
        break;
    case SPADES:
        suitName = "Spades";
        break;
    }

    //Output the valueDisp-suitName
    os << valueDisp << "-" << suitName;
    return os;
}