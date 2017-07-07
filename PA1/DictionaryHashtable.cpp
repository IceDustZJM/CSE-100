/*
 * Author: Hwa Chien Hong
 * Date: 19/4/17
 * Assignment Number: PA2
 * File: DictionaryHashtable.h
 * Overview: The implementation file of the hashtable  implementation of the 
 * dictionary.
 */

#include "util.h"
#include "DictionaryHashtable.h"

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word) {
    if(word.empty()) return false;
    return (hashtable.insert(word).second);
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const {
    if(word.empty()) return false;
    return (hashtable.find(word) != hashtable.end());
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){ hashtable.clear(); }
