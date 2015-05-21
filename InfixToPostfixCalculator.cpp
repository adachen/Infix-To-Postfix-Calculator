/***************************************************
Title: Infix to Postfix Calculator
Author: Ada Chen
Date Created: April 20th, 2015
Brief Purpose: Converts Infix expression to Postfix expressions and evaluates a postfix expression. Program will return the results
in a new file called "resultFile.txt".
***************************************************/

#ifndef INFIXTOPOSTFIXCALCULATOR_CPP_INCLUDED
#define INFIXTOPOSTFIXCALCULATOR_CPP_INCLUDED

//libraries
#include <iostream>
#include <string>
#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>
#include "InfixToPostfixCalculator.h" // class's header file

using namespace std;

InfixToPostfixCalculator::InfixToPostfixCalculator()
{

}  // end default constructor

InfixToPostfixCalculator::~InfixToPostfixCalculator()
{

}  // end destructor

bool InfixToPostfixCalculator::check_digit(string item) const throw(PreconditionViolatedException)
{
    //if the passed string is a digit, return true
    if((item == "0") || (item == "1") || (item == "2") || (item == "3")|| (item == "4")|| (item == "5")||
            (item == "6")|| (item == "7")|| (item == "8")|| (item == "9"))
        return true;
} //end digit check

bool InfixToPostfixCalculator::check_operator(string item) const throw(PreconditionViolatedException)
{
    //if the passed string is an operator, return true, if not, return false
    if ((item == "+") || (item == "-") || (item == "/") || (item == "*") || (item == "^"))
        return true;

    else
        return false;
} //end operator check

string InfixToPostfixCalculator::ReadInfix(string new_infix) //function checks infix functions for errors
{
    //variable declarations
    int open_brace = 0, closed_brace= 0, decimal= 0;
    string temp, next;
    int length = new_infix.length();

    for(int i =0; i< length; i++)
    {
        temp = new_infix[i]; //set a temporary string to the first character in the infix expression
        if(temp == " ")
            continue;

        if((i == 0)|| (i == (length-1)))
        {
            //checks to see if expression beings with a closed parenthesis, throw exception if it does
            if((i == 0) && (temp == ")"))
                throw PreconditionViolatedException("Cannot begin with a closed parenthesis. ");
            //checks to see if the expression begins or ends with an operator, throw exception if it does
            if(check_operator(temp))
                throw PreconditionViolatedException("Cannot begin or end with an operator. ");
            //checks to see if the expression begins or ends with a decimal, throw exception if it does
            if(temp ==".")
                throw PreconditionViolatedException("Cannot begin or end with a decimal. ");
        }

        //checks for inputs other than numbers and operators, throw exception if it doesn't
        if ((!check_operator(temp)) && (!check_digit(temp)) && (temp != ".") && (temp != "(")&& (temp != ")"))
            throw PreconditionViolatedException("Expression can only take numbers and operators. ");
        //checks to see if there is an operator followed by an open brace, throw exception if there is
        else if (temp == "(")
        {
            open_brace++; //keeps track of the amount of open braces
            next = new_infix[i+1]; //checks if the character after the open brace is an operator, throw exception if there is
            if (check_operator(next))
                throw PreconditionViolatedException("An open parenthesis cannot be followed by an operator. ");
        }
        //keeps track of closed braces to check for balanced braces
        else if (temp == ")")
        {
            closed_brace++;
        }

        else if (check_operator(temp))
        {
            next = new_infix[i+1]; //checks to see if there is another operator after an operator or a closed brace
            if ((check_operator(next)== true) || (next == ")"))    //throw exception if it there is
                throw PreconditionViolatedException("An operator cannot be followed by another operator or a closed parenthesis");
        }

        else if ((check_digit(temp)) || (temp == "."))
        {
            next = new_infix[i+1];
            decimal =0;                     //checks for correct placement of decimals
            if (next == ".")
            {
                decimal++;
                if (!check_digit(next))
                    throw PreconditionViolatedException("Invalid decimal placements");
            }
            while ((check_digit(next))|| (next == "."))
            {
                i++;
                if (next == ".")
                {
                    decimal++;           //cannot have a decimal followed by a decimal
                }
                if (decimal > 1)
                    throw PreconditionViolatedException("Invalid decimal placements");
                next = new_infix[i+1];
                continue;
            }
        }
    }
    //checks for balanced braces
    if (open_brace != closed_brace)
        throw PreconditionViolatedException("Unbalanced Parenthesis"); //throw exception if there are unbalanced parenthesis

    return new_infix;

}

//function converts from an infix expression to a postfix expression
string InfixToPostfixCalculator::ConvertInfixToPostfix (const string input_infix)
{
    //variable declarations
    LinkedStack<string> a_stack;
    string position, value, postfix, final_postfix, InputInfix;


    InputInfix = ReadInfix(input_infix);

    for(int i=0; i<InputInfix.length(); i++)
    {
        if(isdigit(InputInfix[i]))
        {
            int counter = 0;
            postfix += InputInfix[i]; //adds digit to postfix expression

            for(int j=i+1; j<InputInfix.length(); j++) //loop keeps track of the amount of digits
            {
                if (isdigit(InputInfix[j]))
                {
                    postfix += InputInfix[j];       //combines digits
                    counter++;        //increases the amount of positions moved while in the while loop
                }
                else break;
            }

            i += counter;
            postfix += ","; //add comma after every number added

        }

        position = InputInfix[i];
        if(position == ")")
        {
            if(!a_stack.IsEmpty())      //if there is a closed brace, if the stack isn't empty
            {
                value = a_stack.Peek();  //set value to the top of the stack
                while(value != "(")
                {
                    value = a_stack.Pop();
                    postfix += value;
                    postfix += ",";             //keep popping value and add it to the postfix until you reach an open brace
                    value = a_stack.Peek();         //add comma after you add to the postfix
                }
                a_stack.Pop(); //pop the open brace
            }
        }
        else if(position == "(")
        {
            a_stack.Push(position); //if there is an open brace, push it onto the stack
        }
        else if(position == "+")
        {
            if(!a_stack.IsEmpty())
            {
                value = a_stack.Peek();
                while ((value != "(" ) && (!a_stack.IsEmpty()))
                {
                    value = a_stack.Pop();      //if there is an addition sign, as long as the stack isn't empty, pop and
                    postfix += value;               //add it to the postfix until you reach an open brace
                    postfix += ",";                    //add comma after you add to the postfix
                }
            }
            a_stack.Push(position);
        }
        else if(position == "-")
        {
            while(!a_stack.IsEmpty())
            {
                value = a_stack.Peek();
                if(value != "(" )
                {
                    value = a_stack.Pop();      //if there is a subtraction sign, as long as the stack isn't empty, pop and
                    postfix += value;               //add it to the postfix until you reach an open brace
                    postfix += ",";                     //add comma after you add to the postfix
                }
                else break;
            }
            a_stack.Push(position);
        }
        else if(position == "/")
        {
            while(!a_stack.IsEmpty())
            {
                value = a_stack.Peek();
                if((value != "(" ) && (value != "-") && (value != "+"))
                {
                    value = a_stack.Pop();      //if there is a division sign, as long as the stack isn't empty, pop and
                    postfix += value;           //add it to the postfix until you reach an open brace, subtraction or addition
                    postfix += ",";                 //add comma after you add to the postfix
                }
                else break;
            }
            a_stack.Push(position);
        }
        else if(position == "*")        //if there is a multiplication sign, as long as the stack isn't empty, pop and
        {
            while(!a_stack.IsEmpty())        //add it to the postfix until you reach an open brace, subtraction or addition
            {
                value = a_stack.Peek();          //add comma after you add to the postfix
                if((value != "(" ) && (value != "-") && (value != "+"))
                {
                    value = a_stack.Pop();
                    postfix += value;
                    postfix += ",";
                }
                else break;
            }
            a_stack.Push(position);
        }
        else if(position == "^")
        {
            a_stack.Push(position);     //push exponent sign onto stack
        }

    }

    while(!a_stack.IsEmpty())
    {
        value = a_stack.Pop();      //pop and add to the postfix along with commas
        postfix += value;
        postfix += ",";
    }

    for(int i = 0; i<postfix.length(); i++)
    {
        int length = postfix.length(); //loop deletes the extra comma at the end of every postfix expression
        postfix[length-1] = ' ';
    }

    return postfix;
}



//calculates the postfix form and returns a double result
double InfixToPostfixCalculator::CalculatePostfix(const string &input_postfix)
{
    //Declaration of variables
    LinkedStack<double> num_stack;  //stack object
    string position, second_digit, answer = input_postfix;
    double temp2, num, num1, num2, value, result;

    int size;

    //the loop runs through the string character by character
    for(int i=0; i<answer.length(); i++)
    {
        position = answer[i];  //stores character as position

        if(position == "," || position == " ") //if there is a comma or space, skip to next character
        {
            continue;
        }

        if (check_digit(position))       //if the ch is a digit
        {
            int counter=0;
            //this checks to see if the number is one digit long or more
            for(int j=i+1; j<answer.length(); j++)
            {
                string item = "";
                item = answer[j]; //next character stored in item
                if ((check_digit(item)) || (item == ".")) //check to see if next character is a digit or decimal so you can combine digits
                {
                    position += item;  //combines digits
                    counter++; //increases the amount of positions moved while in the while loop
                }
                else break;
            }
            num = strtod(position.c_str(), NULL); //converts string to double
            num_stack.Push(num);  //pushes double back onto string
            i += counter;    //sets i to current position
            continue;
        }

        else if(position == "+")  //if position is + then pop two elements and add them
        {
            num1 = num_stack.Pop();  //pops number on top of the stack
            num2 = num_stack.Pop();  //pops number on top of the stack
            value = num1+num2;      //adds the doubles
            num_stack.Push(value);  //pushes the values onto the stack

        }
        else if(position == "-")  //if position is - then pop two elements and subtract them
        {
            num1 = num_stack.Pop();  //pops number on top of the stack
            num2 = num_stack.Pop();   //pops number on top of the stack
            value = num2-num1;       //subtracts the first double popped from the second double popped
            num_stack.Push(value);  //pushes the values onto the stack

        }
        else if (position == "*")  //if position is * then pop two elements and multiply them
        {
            num1 = num_stack.Pop();  //pops number on top of the stack
            num2 = num_stack.Pop();  //pops number on top of the stack
            value = num1*num2;        //multiplies the doubles
            num_stack.Push(value);   //pushes the values onto the stack

        }

        else if (position == "/")  //if position is / then pop two elements and divide them
        {
            num1 = num_stack.Pop();  //pops number on top of the stack
            num2 = num_stack.Pop();  //pops number on top of the stack
            value = num2/num1;      //divides the second double popped by the first
            num_stack.Push(value);   //pushes the values onto the stack

        }

        else if (position == "^")  //if position is ^ then pop two elements and solve the first one to the power of the second one
        {
            num1 = num_stack.Pop();  //pops number on top of the stack
            num2 = num_stack.Pop();  //pops number on top of the stack
            temp2 = 0;
            if(num1== 0)  //a number to the power of 0 is 1
            {
                temp2= 1;
            }
            else if (num1 == 1) //a number to the power of 1 is 0
            {
                temp2 = num2;
            }
            else
            {
                temp2= num2;
                for (int i=1; i<num1; i++)   //num2 to the power of num1
                {
                    temp2 = (num2* temp2);
                }
            }
            num_stack.Push(temp2);  //puch the result onto the stack
        }
        else
        {
            num = strtod(position.c_str(), NULL);  //converts string to double
            num_stack.Push(num);     //pushes double onto the stack
        }

    }

    result = num_stack.Pop();   //pops the result

    return result;  //returns the result
}

#endif
