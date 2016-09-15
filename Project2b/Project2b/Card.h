/* Card.h
*  Jenna Czeck
*  EECE 2560 Project 2
*  Header file of the card class
*/

#ifndef PROJECT2_CARD_H_
#define PROJECT2_CARD_H_

#include <iostream>
#include <string>

#include "d_except.h"

using namespace std;

//Enum declaration for the possible suits and values of cards
enum suit_t { CLUBS, DIAMONDS, HEARTS, SPADES };
enum value_t { TWO = 2, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN,
               JACK, QUEEN, KING, ACE };

class Card {
public:
    //Constructor with input values that have default value
    Card(value_t initValue = TWO, suit_t initSuit = CLUBS );
    Card(const Card& other); //Copy Constructor
    void SetValue(value_t newValue); //Set the value
    value_t GetValue() { return value; }; //Accessor for value
    void SetSuit(suit_t newSuit); //Set the suit
    suit_t GetSuit() { return suit; }; //Accessor for value

    Card& operator=(const Card& cardSource); //Override of assignment operator

    //Override of print fuction
    friend ostream& operator<<(ostream& os, const Card& card);
private:
    value_t value;
    suit_t suit;
    
};


#endif