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

//Copy Constructor
Deck::Deck(const Deck& other) {
    firstCard = new node<Card>; //Create a new node to be the first card

    //Create nodes to traverse the lists
    node<Card>* currThis = firstCard; 
    node<Card>* currOther = other.firstCard;
    node<Card>* nextCard;

    //While we have not reached the end of the Deck we are copying
    while (currOther->next != NULL) {
        currThis->nodeValue = currOther->nodeValue; //Copy node value
        nextCard = new node<Card>; //Create a new card node
        currThis->next = nextCard; //Add that card to the end of the deck
        currThis = nextCard; //Switch to the next card
        currOther = currOther->next; //Go to next card of deck you are copying
    }

    currThis->nodeValue = currOther->nodeValue; //Copy last card value

} //End Copy Constructor

//Returns the first card in the deck and removes it from the deck
Card Deck::Deal() {
    Card dealt = Card(firstCard->nodeValue); //Create the card to be dealt

    //Deletes the first card and changes where the first card points
    node<Card>* curr;
    if (firstCard != NULL) {
        curr = firstCard;
        firstCard = firstCard->next;
        delete curr;
    }
    return dealt; //Returns the top card
} //End Deal

//Adds the card passed to the bottom of the deck
void Deck::Replace(Card card) {
    node<Card>* curr = firstCard; //Create a variable to traverse the list

    //If the first card is not NULL go to the end of the list
    if (curr != NULL) {
        while (curr->next != NULL) {
            curr = curr->next;
        }

        //Once at the end of the list, create a new node with passed card
        node<Card>* newNode = new node<Card>;
        newNode->nodeValue = card;
        curr->next = newNode;
    }
    //If there is no first card (ie NULL) put passed card as the first card
    else {
        curr = new node<Card>;
        curr->nodeValue = card;
    }
} //End Replace

//Shuffles the deck putting the cards in a random order
void Deck::Shuffle() {
    //Declare variables to count the number of cards
    int cardCount = 0;
    node<Card>* curr = firstCard;

    //Goes through the deck and counts how many cards are in the deck
    while (curr != NULL) {
        cardCount++;
        curr = curr->next;
    }

    //Seeds the random number generator with the time
    srand(time(NULL));
    
    //Declares variables to switch cards
    node<Card> *switch1, *switch2;
    Card temp;

    //Switches 2 random cards 100 times
    for (int i = 0; i < 100; i++) {
        //Sets the switch cards to the first card
        switch1 = firstCard;
        switch2 = firstCard;
        int rand1 = rand() % cardCount;
        int rand2 = rand() % cardCount;
        //Traverse to the place of the first card
        for (int j = 0; j < (rand1); j++) {
            switch1 = switch1->next;
            if (switch1 == NULL) {
                throw rangeError("Shuffling went out of deck");
            }
        }
        //Traverse to the place of the second card
        for (int k = 0; k < (rand2); k++) {
            switch2 = switch2->next;
            if (switch2 == NULL) {
                throw rangeError("Shuffling went out of deck");
            }
        }
        //Switch the nodes' value
        temp = switch1->nodeValue;
        switch1->nodeValue = switch2->nodeValue;
        switch2->nodeValue = temp;
    }
} //End Shuffle

//Overrides the assignment operator
Deck& Deck::operator=(const Deck& source) {
    //Delete all the cards in the current deck
    //Goes through the linked list and deletes each node
    node<Card>* curr;
    while (firstCard != NULL) {
        curr = firstCard;
        firstCard = firstCard->next;
        delete curr;
    }

    firstCard = new node<Card>; //Create a new node to be the first card

    //Create nodes to traverse the lists
    node<Card>* currThis = firstCard;
    node<Card>* currSource = source.firstCard;
    node<Card>* nextCard;

    //While we have not reached the end of the Deck we are copying
    while (currSource->next != NULL) {
        currThis->nodeValue = currSource->nodeValue; //Copy node value
        nextCard = new node<Card>; //Create a new card node
        currThis->next = nextCard; //Add that card to the end of the deck
        currThis = nextCard; //Switch to the next card
        currSource = currSource->next; //Go to next card of deck you are copying
    }

    currThis->nodeValue = currSource->nodeValue; //Copy last card value

    return *this;
}

Deck::~Deck() {
    //Goes through the linked list and deletes each node
    node<Card>* curr;
    while (firstCard != NULL) {
        curr = firstCard;
        firstCard = firstCard->next;
        delete curr;
    }
}

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
