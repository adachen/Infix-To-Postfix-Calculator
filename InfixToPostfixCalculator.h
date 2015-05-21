/***************************************************
Title: Programming Assignment 3
Author: Ada Chen
Date Created: April 20th, 2015
Brief Purpose: Converts Infix expression to Postfix expressions and evaluates a postfix expression. Program will return the results
in a new file called "resultFile.txt".
***************************************************/

#ifndef INFIXTOPOSTFIXCALCULATOR_H_INCLUDED
#define INFIXTOPOSTFIXCALCULATOR_H_INCLUDED

//libraries
#include <string>
#include <iostream>
#include <cstddef>
#include "LinkedStack.h"
using namespace std;

class InfixToPostfixCalculator //class
{
public:
    InfixToPostfixCalculator();       // Default constructor
    ~InfixToPostfixCalculator();      // Destructor

    //public functions
    string ConvertInfixToPostfix (const string input_infix); //function converts an infix expression to postfix expression
    double CalculatePostfix(const string &input_postfix); //function calculates a postfix expression

private:
    //private functions
    string ReadInfix(string new_infix); //function checks for errors in an infix expression
    bool check_digit(string item) const throw(PreconditionViolatedException); //function checks if the string is a digit
    bool check_operator(string item) const throw(PreconditionViolatedException); //function checks if the string is an operator

};

#endif
