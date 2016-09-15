/* Deck.cpp
*  Jenna Czeck
*  EECE 2560 Project 2
*  Implimentation of the deck class
*/

#include "Deck.h"

//Creates a deck with cards in order from 2-A, Clubs to Spades
Deck::Deck() {

    //Variable declerations
    node<Card>* currCard = new node<Card>;
    node<Card>* nextCard;
    bool initialized = false; //Has the deck been initialized yet

    //Goes through each suit and then every value
    for (int s = 0; s < 4; s++) {
        //Value is between 2 and 14 because of enum values
        for (int v = 2; v <= 14; v++) { 

            //If already initialized deck, create the next card and point to
            //it from current card
            if (initialized) {
                nextCard = new node<Card>;
                currCard->next = nextCard;
                currCard = nextCard;
            }

            //Create a card with the current value and suit of the loop
            currCard->nodeValue = Card(static_cast<value_t>(v), 
                static_cast<suit_t>(s));

            //If not initialized, make the firstCard the current card and
            //set initialized to true
            if (!initialized) {
                firstCard = currCard;
                initialized = true;
            }
        } //End value loop
    } //End suit loop
} //End default construstor

//Override of print function
ostream& operator<<(ostream& os, const Deck& deck) {
    //Creates a current card to interate through
    node<Card>* currCard = deck.firstCard;

    //While the current Card is not NULL, print out the card on its own line
    //and then move to the next card
    while (currCard != NULL) {
        os << currCard->nodeValue << endl;
        currCard = currCard->next;
    }
    return os;
}
