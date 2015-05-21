/***************************************************
Title: Programming Assignment 3
Author: Ada Chen
Date Created: April 20th, 2015
Brief Purpose: Converts Infix expression to Postfix expressions and evaluates a postfix expression. Program will return the results
in a new file called "resultFile.txt".
***************************************************/

#ifndef PRECONDITIONVIOLATEDEXCEPTION_H_INCLUDED
#define PRECONDITIONVIOLATEDEXCEPTION_H_INCLUDED

#include <stdexcept>
#include <string>

using namespace std;


// A simple exception class as a child of logic_error.
class PreconditionViolatedException : public logic_error
{
public:
   PreconditionViolatedException(const string& message = "");
}; // end PrecondViolatedExcep

//#include "PreconditionViolatedException.cpp"
#endif // PRECONDITIONVIOLATEDEXCEPTION_H
