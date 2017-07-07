/*
 * Author: Hwa Chien Hong
 * Date: 2/4/17
 * Assignment Number: PA2
 * File: DictionaryTrie.cpp	
 * Overview: The implementation file of the Trie implementation of the 
 * dictionary.
 */

#include "util.h"
#include "DictionaryTrie.h"
#include <iostream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <array>
#include <functional>
#include <list>

using namespace std;

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){root=NULL;}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
    unsigned const int space_index = 26;
    unsigned const int space_ASCII = 32;
    // checks validity of the string. If it is empty
    if(word.empty()) return false;
    if(root == NULL) root = new Node();

    Node * curr = root;
    for(unsigned int i = 0; i < word.length(); i++) {
	// if the index of hashmap is null, not yet added
	// add a new node pointer to that position

	// Specific case where the character is a space
	if((int)word.at(i) == space_ASCII && 
		(curr->hashmap)[space_index] == NULL) {
	    //cout << "1";
	    (curr->hashmap)[space_index] = new Node();
	    curr = (curr->hashmap)[space_index];
	    // not a space character
	} else if((int)word.at(i) != space_ASCII && 
		(curr->hashmap)[(int) word.at(i)-'a'] == NULL) {
	    (curr->hashmap)[(int) word.at(i)-'a'] = new Node();
	    curr = (curr->hashmap)[(int) word.at(i)-'a'];
	    //cout << "2";
	} else if((int)word.at(i) == space_ASCII) { 
	    //cout << "3";
	    curr = (curr->hashmap)[space_index];
	} else {
	    //cout << "4";
	    curr = (curr->hashmap)[(int) word.at(i)-'a'];
	}
    }
    // if the word was already inserted 
    if(curr->leafNode) return false;

    // arrives at a leaf node, can make leafNode boolean to be true
    curr->leafNode = true;
    curr->freq = freq; 

    return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{    
    unsigned const int space_ASCII = 32;
    unsigned const int space_index = 26;
    // checks validity of the string. If it is empty
    if(word.empty()) return false;

    Node * curr = root;
    for(unsigned int i = 0; i < word.length(); i++) {
	// if its a regular char, and node at that index does not exist
	if((int)word.at(i) != space_ASCII && 
		(curr->hashmap)[(int) word.at(i)-'a']==NULL){
	    return false;
	}

	// if its a space characer
	if((int)word.at(i) == space_ASCII && 
		(curr->hashmap)[space_index]==NULL) {
	    return false;
	} 

	if((int)word.at(i) == space_ASCII) { 
	    curr = (curr->hashmap)[space_index];
	} else {
	    curr = (curr->hashmap)[(int) word.at(i)-'a'];
	}
    }
    // if the word was found
    if( curr-> leafNode ) return true;

    return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
    std::vector<std::string> words;

    /* Step 1: find the given prefix */
    unsigned const int space_ASCII = 32;
    unsigned const int space_index = 26;
    const int size = 26;
    // checks validity of the string. If it is empty
    if(prefix.empty()) { 
	cout << "Invalid Input. Please retry with correct input" << endl;
	return words;
    }

    Node * curr = root;
    for(unsigned int i = 0; i < prefix.length(); i++) {
	// if its a regular char, and node at that index does not exist
	if((int)prefix.at(i) != space_ASCII && 
		(((int)prefix.at(i)-'a'< 0)||
		 ((int)prefix.at(i)-'a'> size))
		&& (curr->hashmap)[(int) prefix.at(i)-'a']==NULL){
	    cout << "Invalid Input. Please retry with correct input" << endl;
	    return words;
	}

	// if its a space characer
	if((int)prefix.at(i) == space_ASCII && 
		(curr->hashmap)[space_index]==NULL) {
	    cout << "Invalid Input. Please retry with correct input" << endl;
	    return words;
	} 

	if((int)prefix.at(i) == space_ASCII) { 
	    curr = (curr->hashmap)[space_index];
	} else {
	    curr = (curr->hashmap)[(int) prefix.at(i)-'a'];
	}
    }

    /* Step 2: search through the subtree rooted at the end of the prefix */
    // if the word was found
    unsigned int table_size = 27;
    unsigned int little_a = 97; 
    unsigned int space_ascii = 32;
    std::vector<pair<std::string, int>> temp_vec;
    std::queue<pair<Node*,string>> q;
    q.push(std::make_pair(curr, prefix));

    while(!q.empty()) {
	// get the element and then actually pop it out
	std::pair<Node*, string> temp = q.front();
	q.pop();

	// checks if the node states node being a word node
	if( (temp.first) -> leafNode ) { 
	    // push in a pair (string, freq of word)
	    //cout << temp.second + " and " +  (temp.first)->freq << endl;
	    temp_vec.push_back(std::make_pair(temp.second, (temp.first)->freq));
	}
	for(unsigned int i = 0; i < table_size; i++) {
	    if(((temp.first)->hashmap)[i] != NULL) {
		Node * first = ((temp.first)->hashmap)[i];
		string second;
		// transform the ASCII value to actual letter 
		if(i == 26) second = temp.second + string(1,static_cast<char>(space_ascii));
		else second = temp.second + string(1,static_cast<char>(i+little_a));
		//cout << second << endl;
		q.push(std::make_pair(first, second));
	    }
	}
    }

    /* Step 3: sort the vector of pairs containing the prefix */ 
    std::sort(temp_vec.begin(), temp_vec.end(),
	    [](const pair<std::string, int>& lhs, const pair<std::string, int>& rhs) {
	    return lhs.second > rhs.second; });

    /* Step 4: Only add the words needed */ 
    for(unsigned int j = 0; j < num_completions && j < temp_vec.size(); j++) {
	std::pair<std::string, int> pair = temp_vec[j];
	words.push_back(pair.first);
    }
    return words;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
    deleteAll(root);
}

void DictionaryTrie::deleteAll(Node * root) {
    if(!root) return;
    unsigned int table_size = 27;
    for(unsigned int i = 0; i < table_size; i++) {
	if(((root->hashmap)[i])) {
	    deleteAll((root->hashmap)[i]);
	}
    }
    delete(root);
}
