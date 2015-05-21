/***************************************************
Title: Programming Assignment 3
Author: Ada Chen
Date Created: April 20th, 2015
Brief Purpose: Converts Infix expression to Postfix expressions and evaluates a postfix expression. Program will return the results
in a new file called "resultFile.txt".
***************************************************/

#ifndef LINKEDSTACK_H_INCLUDED
#define LINKEDSTACK_H_INCLUDED

//libraries
#include <string>
#include <cstddef>
#include "StackInterface.h"
#include "Node.h"
#include "PreconditionViolatedException.h"
#include<iostream>
using namespace std;


template<class ItemType>
class LinkedStack
{
public:
    LinkedStack(); //constructor
    virtual ~LinkedStack(); //destructor

    bool IsEmpty() const;
    bool Push(const ItemType& new_item); //push values on the stack
    ItemType Pop(); //pops value from the stack
    ItemType Peek() const throw(PreconditionViolatedException); //peeks at the top of stack
private:
    Node<ItemType>* top_ptr_;
};

#include "LinkedStack.cpp"
#endif // LINKEDSTACK_H
