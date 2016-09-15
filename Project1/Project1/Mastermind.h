/* Mastermind.h
*  Jenna Czeck
*  EECE 2560 Project 1
*  Header file for the mastermind game class
*/

#ifndef Project1_Mastermind_h
#define Project1_Mastermind_h

#include <iostream>
#include "Code.h"
#include "Response.h"

using namespace std;

class Mastermind {
public:
    void PlayGame(); //Plays the game
private:
    Code secretCode;
    void PrintSecretCode(); //Prints out secret code
    Code HumanGuess(); //Takes in a human guess via user input
    Response GetResponse(Code guess, Code secret); //Gives response for 2 codes
    bool IsSolved(const Response &r); //Returns if code is solved
    int GetNumber(); //Takes in user input and returns when input is in range
};

#endif