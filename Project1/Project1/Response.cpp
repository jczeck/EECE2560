#include "Response.h"
/* Response.cpp
*  Jenna Czeck
*  EECE 2560 Project 1
*  Implementation of Response class
*/

#include "Response.h"

//Constructor for the response, which sets numCorrect and numIncorrect
Response::Response(int correct, int incorrect) {
    numCorrect = correct;
    numIncorrect = incorrect;
}

//Sets numCorrect
void Response::SetCorrect(int newCorrect) {
    numCorrect = newCorrect;
}

//Sets numIncorrect
void Response::SetIncorrect(int newIncorrect) {
    numIncorrect = newIncorrect;
}

//Takes a const ref to a response and returns if it is equal to this response
bool Response::AreEqual(const Response &r) {
    if (r.GetCorrect() == numCorrect && r.GetIncorrect() == numIncorrect) {
        return true;
    } else {
        return false;
    }
}

//Prints out the value of the response
void Response::PrintResponse() {
    cout << "(" << numCorrect << "," << numIncorrect << ")" << endl;
}
