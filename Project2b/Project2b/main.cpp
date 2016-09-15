/* main.cpp
*  Jenna Czeck
*  EECE 2560 Project 2
*  Main function of Project 2
*  Developed using Visual Studio
*/

#include <iostream>

#include "d_except.h"
#include "Card.h"
#include "Deck.h"

//Gets the next action of the user
char GetAction() {
    char action; //Declare variable

                 //Output message of choices of actions
    cout << "Press 's' to stop or 'd' to deal another card" << endl;
    cin >> action; //Takes in user response

                   //If response is not one of the choices
    if (action != 'd' && action != 'D' && action != 's' && action != 'S') {
        //Output error message
        cout << "Sorry, that command is not recognized. Try again" << endl;
        action = GetAction(); //Try again
    }
    return action; //Return the action
}

//Plays the flip game
void PlayFlip() {
    //Declare variables
    Deck playDeck = Deck();
    char action = 'd';
    int points = 0;
    Card flipped;

    //Shuffle the deck 3 times
    playDeck.Shuffle();
    playDeck.Shuffle();
    playDeck.Shuffle();

    //Output game play notices
    cout << "Let's play Flip!" << endl;
    cout << "Let's see what the first card is" << endl;

    //While the user has not selected the action to stop
    while (action != 's' && action != 'S') {
        //Deal the top card and display it
        flipped = playDeck.Deal();
        cout << "Your card: " << flipped << endl;

        //Calculate the points value based on the card
        switch (flipped.GetValue()) {
        case ACE:
            points += 10;
            break;
        case KING: case QUEEN: case JACK:
            points += 5;
            break;
        case SEVEN:
            points = points / 2;
            break;
        case TWO: case THREE: case FOUR: case FIVE: case SIX:
            points = 0;
            break;
        }
        //Add an extra points if it is a heart
        if (flipped.GetSuit() == HEARTS) {
            points += 1;
        }
        //Replace the card
        playDeck.Replace(flipped);

        //Display the points value
        cout << "Points: " << points << endl;
        //Ask for the user's next action
        cout << "What would you like to do?" << endl;
        action = GetAction(); //Call to get action to get action value
    }

    //Output end of game command
    cout << "End Game" << endl << "Your point total: " << points << endl;
}

int main() {

    //Put the function in a try block to catch errors
    try {

        PlayFlip();

    }

    //Catch a range error
    catch (const rangeError& re) {
        cout << re.what() << endl;
        exit(1);
    }

    //Catch any other error
    catch (const baseException& be) {
        cout << be.what() << endl;
        exit(1);
    }

    //Waits for the user to exit
    cout << "Press any key and enter to exit" << endl;
    string exit;
    cin >> exit;

    return 0;
}