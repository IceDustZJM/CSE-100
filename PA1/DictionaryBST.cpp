/*
 * Author: Hwa Chien Hong
 * Date: 19/4/17
 * Assignment Number: PA2
 * File: DictionaryBST.h
 * Overview: The implementation file of the BST implementation of the 
 * dictionary.
 */
#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){ }

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word) { 
    if(word.empty()) return false;
    return ((set.insert(word)).second);
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const {
    if(word.empty()) return false;
    return (set.find(word) != set.end());
}

/* Destructor */
DictionaryBST::~DictionaryBST(){ set.clear(); }
