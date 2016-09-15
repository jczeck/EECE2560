/* Code.h
*  Jenna Czeck
*  EECE 2560 Project 1
*  Header file of the code class
*/

#ifndef Project1_Code_h
#define Project1_Code_h

#include <vector>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Code {
public:
    Code() {}; //Default Constructor
    Code(int a, int b, int c, int d); //Constructor with code inputed
    void InitializeRandomCode();    //Initializes a the code randomly
    int CheckCorrect(const Code &c); //Returns number of correct digits
    int CheckIncorrect(const Code &c); //Returns number of incorrect digits
    vector<int> GetCode() { return code; }; //Accessor for code

private:
    vector<int> code;
};

#endif