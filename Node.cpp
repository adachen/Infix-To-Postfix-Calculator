/***************************************************
Title: Programming Assignment 3
Author: Ada Chen
Date Created: April 20th, 2015
Brief Purpose: Converts Infix expression to Postfix expressions and evaluates a postfix expression. Program will return the results
in a new file called "resultFile.txt".
***************************************************/

#ifndef NODE_CPP
#define NODE_CPP

#include "Node.h"
#include <cstddef>

template<class ItemType>
Node<ItemType>::Node() : next_node_(NULL)
{
} // end default constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& an_item) : item_(an_item), next_node_(NULL)
{
} // end constructor

template<class ItemType>
Node<ItemType>::Node(const ItemType& an_item, Node<ItemType>* next_node) :
    item_(an_item), next_node_(next_node)
{
} // end constructor

template<class ItemType>
void Node<ItemType>::SetItem(const ItemType& an_item)
{
    item_ = an_item;
} // end setItem

template<class ItemType>
void Node<ItemType>::SetNext(Node<ItemType>* next_node)
{
    next_node_ = next_node;
} // end setNext_Node_Ptr

template<class ItemType>
ItemType Node<ItemType>::GetItem() const
{
    return item_;
} // end getItem

template<class ItemType>
Node<ItemType>* Node<ItemType>::GetNext() const
{
    return next_node_;
} // end getNext_Node_Ptr

#endif
