/* Code.cpp
*  Jenna Czeck
*  EECE 2560 Project 1
*  Implementation of the code class
*/

#include "Code.h"

// Constructor with inputted code, takes 4 ints, assumes ints will be in range
Code::Code(int a, int b, int c, int d) {

    // Initializing the code
    code.push_back(a);
    code.push_back(b);
    code.push_back(c);
    code.push_back(d);
}

// Initializes the random code
void Code::InitializeRandomCode() {
    code.clear(); //Clears the code
    
    //Seeds the random number generator with the time
    srand(time(NULL));

    //Pushes back four random numbers
    code.push_back(rand() % 6);
    code.push_back(rand() % 6);
    code.push_back(rand() % 6);
    code.push_back(rand() % 6);

} //End InitializeRandomCode

// Checks the number of correct numbers with const ref to a code
int Code::CheckCorrect(const Code &c) {
    int numCorrect = 0; //Initialize the number of correct as 0

    //Iterates throught the code
    for (int i = 0; i < (int)code.size(); i++) {

        //If the number at i is equal in both codes, increment numCorrect
        if (c.code.at(i) == code.at(i)) {
            numCorrect++;
        }
    }
    return numCorrect;
} //End CheckCorrect

// Checks the number of incorrect numbers with const ref to a code
int Code::CheckIncorrect(const Code &c) {
    int numIncorrect = 0; //Stores the number of incorrect numbers
    int codeSize = (int)code.size(); //
    bool incriment = true; //If we should incriment numIncorrect

    //Vector of digits already found to be incorrect
    vector<int> foundIncorrect = vector<int>(0);

    //Goes through the code and counts the number of incorrect digits
    for (int i = 0; i < codeSize; i++) { //For each number in the code
        if (c.code.at(i) != code.at(i)) { //If not a correct digit 

            //For each number in passed code
            for (int j = 0; j < codeSize; j++) { 

                //If not in the same locate and if c[j] = code[i] 
                if (i != j && c.code.at(j) == code.at(i)) {
                    int incorrectNum = code.at(i); //Stores number value

                    //Checks that it is not a correct digit at j
                    if (code.at(j) == c.code.at(j)) {
                        incriment = false; //If so do not incriment
                    }

                    //Go through foundIncorrect numbers and see if just found
                    //digit is on the list
                    for (int k = 0; k < (int)foundIncorrect.size(); k++) {
                        if (foundIncorrect.at(k) == incorrectNum)
                            incriment = false; //If so do not incriment
                    }
                    if (incriment) { //If incriment has not been set false
                        numIncorrect++; //Incriment numIncorrect

                        //Add incorrectNum to list of found
                        foundIncorrect.push_back(incorrectNum);
                    }
                    incriment = true; //Rest incriment to true
                    break; //Move to next number in code
                }
            } //Close j loop
        } //Close check if equal
    } //Close i looop
    return numIncorrect;
} //End CheckIncorrect