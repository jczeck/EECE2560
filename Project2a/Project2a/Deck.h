/* Deck.h
*  Jenna Czeck
*  EECE 2560 Project 2
*  Header file of the deck class
*/

#ifndef PROJECT2_DECK_H_
#define PROJECT2_DECK_H_

#include "d_node.h"
#include "d_except.h"
#include "Card.h"

using namespace std;

class Deck {
public:
    Deck(); //Default Constructor

    //Override print function
    friend ostream& operator<<(ostream& os, const Deck& deck);
private:
    node<Card>* firstCard; //Pointer to node of the first card
};


#endif