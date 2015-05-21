/***************************************************
Title: Programming Assignment 3
Author: Ada Chen
Date Created: April 20th, 2015
Brief Purpose: Converts Infix expression to Postfix expressions and evaluates a postfix expression. Program will return the results
in a new file called "resultFile.txt".
***************************************************/

#ifndef LINKEDSTACK_CPP_INCLUDED
#define LINKEDSTACK_CPP_INCLUDED

//libraries
#include "LinkedStack.h"
#include <iostream>
#include <cstddef>
#include <cstring>

using namespace std;

template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : top_ptr_(NULL)
{
}  // end default constructor


template<class ItemType>
LinkedStack<ItemType>::~LinkedStack()
{
    // Pop until stack is empty
    while (!IsEmpty())
        Pop();

}  // end destructor

template<class ItemType>
bool LinkedStack<ItemType>::IsEmpty() const
{
    return top_ptr_ == NULL;
}


template<class ItemType>
bool LinkedStack<ItemType>::Push(const ItemType& new_item)
{
    Node<ItemType>* new_node_ptr = new Node<ItemType>(new_item, top_ptr_);
    top_ptr_ = new_node_ptr;
    new_node_ptr = NULL;
    return true;
}

template<class ItemType>
ItemType LinkedStack<ItemType>::Pop()
{
    ItemType item_popped;
    if (IsEmpty()) return false;
    // Stack is not empty; delete top
    Node<ItemType>* node_to_delete_ptr = top_ptr_;
    item_popped = node_to_delete_ptr->GetItem();
    top_ptr_ = top_ptr_->GetNext();

    // Return deleted node to system
    node_to_delete_ptr->SetNext(NULL);
    delete node_to_delete_ptr;
    node_to_delete_ptr = NULL;

    return item_popped;
}  // end pop

template<class ItemType>
ItemType LinkedStack<ItemType>::Peek() const throw(PreconditionViolatedException)
{
    /*if (IsEmpty())
      throw PreconditionViolatedException("Peek() called with empty stack");*/
    return top_ptr_->GetItem();
}  // end peek
// End of implementation file.

#endif
