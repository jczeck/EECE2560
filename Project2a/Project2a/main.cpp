/* main.cpp
*  Jenna Czeck
*  EECE 2560 Project 2
*  Main function of Project 2
*  Developed using Visual Studio
*/

//Need to create our own linked list

#include <iostream>

#include "d_except.h"
#include "Card.h"
#include "Deck.h"

int main() {

    //Put the function in a try block to catch errors
    try {
        //Create a default deck and display that deck
        Deck myDeck = Deck();

        cout << myDeck;
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