/***************************************************
Title: Programming Assignment 3
Author: Ada Chen
Date Created: April 20th, 2015
Brief Purpose: Converts Infix expression to Postfix expressions and evaluates a postfix expression. Program will return the results
in a new file called "resultFile.txt".
***************************************************/

//libraries
#include <iostream>
#include <fstream>
#include <cstddef>
#include <string>
#include <vector>
#include "InfixToPostfixCalculator.h"

using namespace std;

int main()
{
    InfixToPostfixCalculator calculator; //object declaration

    //variable declarations
    vector<string> a_list;
    string temp, postfixForm, expression;
    double result;

    //read file from text
    ifstream myfile("infixFile.txt");

    if(myfile.is_open()) //open file
    {
        while(!myfile.eof())
        {
            getline(myfile,temp);
            a_list.push_back(temp); //pushes contents of the file into a vector
        }
        myfile.close(); //close file
    }
    else
    {
        cout<<"Error. Unable to open the file. "<<endl; //if file doesn't open, output an error
    }

    //vector declaration
    vector<double> a_vector;

    for (int i=0; i<a_list.size(); i++) //loops through the vector with stored expressions
    {
        expression = a_list.at(i); //sets expression to the first line
        if(expression == " ") //continue the code if expression is a space
        {
            continue;
        }

        cout<< endl << "Infix form: "<< expression <<endl; //outputs each infix form in the vector

        postfixForm = calculator.ConvertInfixToPostfix(expression); //set postfixForm to the converted infix expression

        cout << "Postfix form: " << postfixForm << endl; //output the postfix form

        result = calculator.CalculatePostfix(postfixForm); //sets result to the calculated postfix expression

        a_vector.push_back(result); //stores all the results in a vector

        cout << "Result: " << result <<endl; //outputs all the results of each expression

    }

    cout << endl << "Results are also in an output file named 'resultFile.txt' ";

    ofstream my_file;
    my_file.open ("resultFile.txt");

    //creates a file named resultFile and outputs all the results from the vector
    if(my_file.is_open())
    {
        for(int i = 0; i<a_vector.size(); i++)
        {
            my_file << a_vector.at(i) << endl;
        }

        my_file.close();
    }

    return 0;
} //end main

