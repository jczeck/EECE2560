/* Response.h
*  Jenna Czeck
*  EECE 2560 Project 1
*  Header file for the response class
*/

#ifndef Project1_Response_h
#define Project1_Response_h

#include <iostream>

using namespace std;

class Response {
public:
    Response(int correct=0, int incorrect=0); //Constructor with default values
    int GetCorrect() const { return numCorrect; }; //Accessor
    void SetCorrect(int newCorrect); //Setter
    int GetIncorrect() const { return numIncorrect; }; //Accessor
    void SetIncorrect(int newIncorrect); //Setter
    bool AreEqual(const Response &r); //Checks if two responses are equaal
    void PrintResponse(); //Prints the response
private:
    int numCorrect;
    int numIncorrect;
};

#endif