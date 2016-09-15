/* Deck.h
*  Jenna Czeck
*  EECE 2560 Project 2
*  Header file of the deck class
*/

#ifndef PROJECT2_DECK_H_
#define PROJECT2_DECK_H_

#include <stdlib.h>
#include <time.h>

#include "d_node.h"
#include "d_except.h"
#include "Card.h"

using namespace std;

class Deck {
public:
    Deck(); //Default Constructor
    Deck(const Deck& other); //Copy Constructor
    Card Deal(); //Returns first card of deck by value;
    void Replace(Card card); //Places card at bottom of deck
    void Shuffle(); //Shuffles the deck

    Deck& operator=(const Deck& source);

    //Override print function
    friend ostream& operator<<(ostream& os, const Deck& deck);

    ~Deck(); //Destructor
private:
    node<Card>* firstCard; //Pointer to node of the first card
};


#endif