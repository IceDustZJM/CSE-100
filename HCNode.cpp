/*
 * Author: Hwa Chien Hong
 * Date: 5/6/17
 * Assignment Number: PA3
 * File: HCTree.cpp
 * Overview: The implementation file of the HCNode methods. The methods 
 * requried to be written are listed from the .h file. 
 */ 

#include "HCNode.h"

//HCNode::~HCNode() {}

bool HCNode::operator<(const HCNode& other) {
    // if they have the same amount of count, resort to symbol resolution
    if(other.count == this->count) return other.symbol < this->symbol;

    // otherwise just compare the counts 
    return other.count < this->count;
}
