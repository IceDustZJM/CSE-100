/*
 * Author: Hwa Chien Hong
 * Date: 10/4/17
 * Assignment Number: PA1
 * File: BSTNode.hpp
 * Overview: This file contains the implementations of the BSTNode functions. 
 * One important function is the successor, which traverses through the tree
 * in order.
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>
#include <stack>

template<typename Data>
class BSTNode {
    public:
	BSTNode<Data>* left;
	BSTNode<Data>* right;
	BSTNode<Data>* parent;
	Data const data;   // the const Data in this node.

	/** Constructor.  Initialize a BSTNode with the given Data item,
	 *  no parent, and no children.
	 */
	BSTNode(const Data & d);

	/** Return the successor of this BSTNode in a BST, or 0 if none.
	 ** PRECONDITION: this BSTNode is a node in a BST.
	 ** POSTCONDITION:  the BST is unchanged.
	 ** RETURNS: the BSTNode that is the successor of this BSTNode,
	 ** or 0 if there is none.
	 */ 
	BSTNode<Data>* successor(); 
}; 

// Function definitions
// For a templated class it's easiest to just put them in the same file as the class declaration

template <typename Data>
BSTNode<Data>::BSTNode(const Data & d) : left(0), right(0), parent(0), data(d) {}

/* Return a pointer to the BSTNode that contains the item that is sequentially next 
 * in the tree */
template <typename Data>
BSTNode<Data>* BSTNode<Data>::successor() {
    BSTNode<Data> * curr = this; 

    // Case 0: if its a leaf node
    //if(curr->right == NULL && curr->left == NULL && curr->parent!=NULL) return curr->parent;

    // Case 1: if there is a right subtree, then the successor is the most left node of right subtree
    if(curr->right != NULL) {
	curr = curr->right;
	while(curr->left != NULL) curr = curr->left;
	return curr;
    }	  

    // Case 2: if there is no right subtree, the the successor is the immediate ancesotor whose left 
    // subtree contains this current node
    if(curr->parent != NULL) {
	BSTNode<Data> * par = curr->parent;

	while(par != NULL) {
	    if((par->left != NULL) && (par->left->data == curr->data)) break;
	    curr = par; 
	    par = curr->parent;
	}
	return par;
    }

    // will never get to this point. Here to remove warning
    return curr;
}

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
std::ostream & operator<<(std::ostream& stm, const BSTNode<Data> & n) {
    stm << '[';
    stm << std::setw(10) << &n;                 // address of the BSTNode
    stm << "; p:" << std::setw(10) << n.parent; // address of its parent
    stm << "; l:" << std::setw(10) << n.left;   // address of its left child
    stm << "; r:" << std::setw(10) << n.right;  // address of its right child
    stm << "; d:" << n.data;                    // its data field
    stm << ']';
    return stm;
}

#endif // BSTNODE_HPP
