/* Mastermind.cpp
*  Jenna Czeck
*  EECE 2560 Project 1
*  Main function of Project 1
*  Developed using Visual Studio
*/

#include <iostream>
#include "Code.h"
#include "Response.h"
#include "Mastermind.h"

using namespace std;

int main() {

    //Create a mastermind object and then play the game
    Mastermind mastermind = Mastermind();
    mastermind.PlayGame();

    //Waits for the user to exit
    cout << endl;
    system("pause");

    return 0;
}