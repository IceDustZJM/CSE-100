/*
 * Author: Hwa Chien Hong
 * Date: 10/4/17
 * Assignment Number: PA1
 * File: BSTNodeInt.cpp
 * Overview: This file contains the definitions of the BSTNodeInt class. 
 */

#include "BSTNodeInt.h"

#include <iomanip>
#include <iostream>

  /** Constructor.  Initialize a BSTNode with the given Data item,
   *  no parent, and no children.
   */
BSTNodeInt::BSTNodeInt(int d) : left(0), right(0), parent(0), data(d) {} 


/** Overload operator<< to print a BSTNode's fields to an ostream. */
std::ostream & operator<<(std::ostream& stm, const BSTNodeInt & n) {
  stm << '[';
  stm << std::setw(10) << &n;                 // address of the BSTNode
  stm << "; p:" << std::setw(10) << n.parent; // address of its parent
  stm << "; l:" << std::setw(10) << n.left;   // address of its left child
  stm << "; r:" << std::setw(10) << n.right;  // address of its right child
  stm << "; d:" << n.data;                    // its data field
  stm << ']';
  return stm;
}
