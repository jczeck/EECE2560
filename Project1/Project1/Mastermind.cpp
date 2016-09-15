/* Mastermind.cpp
*  Jenna Czeck
*  EECE 2560 Project 1
*  Implimentation of the Mastermind game class
*/

#include "Mastermind.h"

//Prints out the secret code
void Mastermind::PrintSecretCode() {
    vector<int> code = secretCode.GetCode(); //Gets the code and stores it
    
    //Prints out the secret code
    cout << "Secret Code: (" << code.at(0) << ", " << code.at(1) << ", ";
    cout << code.at(2) << ", " << code.at(3) << ")" << endl;
}

//Returns a code object as read from the keyboard
Code Mastermind::HumanGuess() {
    int a, b, c, d; //Declare variables to be read

    //For each number asks user and then calls to GetNumber to handle input
    cout << "What is your guess?" << endl << "First number: ";
    a = GetNumber();
    cout << "Second Number: ";
    b = GetNumber();
    cout << "Third Number: ";
    c = GetNumber();
    cout << "Fourth Number: ";
    d = GetNumber();

    //Displays the full code formated
    cout << "Your Code: (" << a << ", " << b << ", " << c << ", " << d << ")";
    return Code(a, b, c, d); //Returns code object
}

// Reads a number from the keyboard and if in specified range, returns it
int Mastermind::GetNumber() {
    int num;
    cin >> num; //Read number from keyboard, assumes it will be number

    //If num is not in range [0,5] displays message and then recursively calls
    //GetNumber again
    if (num < 0 || num > 5) {
        cout << "Number must be between 0 and 5, Please enter again: ";
        num = GetNumber();
    }

    return num; //Returns user inputed number
}

//Takes in two code objects and returns a response object
Response Mastermind::GetResponse(Code guess, Code secret) {
    Response response = Response(); //Initialize response

    //Sets number correct of response by calling to code function
    response.SetCorrect(secret.CheckCorrect(guess)); 

    //Sets number incorrect of response by calling to code function
    response.SetIncorrect(secret.CheckIncorrect(guess));

    return response; //Returns the response
}

//Takes in a response and checks if code is solver
bool Mastermind::IsSolved(const Response &r) {
    Response solved = Response(4, 0); //Sets what the solved response is

    //Uses response function to check if response is equal to solved response
    //Returns the result
    return solved.AreEqual(r); 
}

//Plays the mastermind game
void Mastermind::PlayGame() {

    //Initialize variables
    Code guess;
    Response currentResponse = Response(0, 0);
    int numGuesses = 0;
    
    //Initializes secret code and prints it out
    secretCode.InitializeRandomCode();
    PrintSecretCode();

    //While it is not solved and there are less than 10 guesses takes in a
    //user's guess, takes a response, displays the response and incriments 
    //the number of guesses
    while (!IsSolved(currentResponse) && numGuesses < 10) {
        guess = HumanGuess();
        currentResponse = GetResponse(guess, secretCode);
        cout << endl << "Response: ";
        currentResponse.PrintResponse();
        numGuesses++;
    }

    //Checks if loop exited based on winning or losing and print appropriate
    //response
    if (IsSolved(currentResponse)) {
        cout << "Congratulations! You Won!";
    } else {
        cout << "Sorry. You Lose";
    }
}
