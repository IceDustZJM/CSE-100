/*
 * Author: Hwa Chien Hong
 * Date: 22/4/17
 * Assignment Number: PA2
 * File: benchhash.cpp
 * Overview: The file to calculate the time needed to find words that
 * were not inserted. The data structures tested were BST, hashtable, and 
 * Trie. The begin and end timer were timed to record the runtime. 
 */

#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<fstream>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#define LETTERS 26
using namespace std;

unsigned int function1(std::string const & s, unsigned int tablesize);
unsigned int function2(std::string const & s, unsigned int tablesize);

int main(int argc, char* argv[])
{   
    std::string dictfile(argv[1]);
    unsigned int num_words = atoi(argv[2]);
    unsigned int tablesize = 2*num_words;

    cout << "Printing the statistics for hash function 1 with hash table size " << tablesize << endl;
    ifstream fin;
    fin.open(dictfile);

    // Read the num_words from the dictionary file 
    // then compute the time needed to find those words in the dict object
    vector<std::string> vec;
    Utils::load_vector(vec, fin, num_words);

    std::vector<unsigned int> word_count(tablesize);
    std::vector<std::string>::iterator it;
    // hashing the words into the newly created vector
    for(it = vec.begin(); it < vec.end(); it++) {
	int idx = function1(*it, tablesize);
	word_count[idx]++;
    }

    unsigned int max = 0;
    // find the biggest number in vector 
    for(unsigned int i = 0; i < word_count.size(); i++) {
	if(word_count[i] > max) max = word_count[i];
    }
    std::vector<unsigned int> slots0(max+1);
    // Printing out information about individual slots and hits 
    unsigned int var = 0;
    cout << "#hits" << '\t' << "slots receiving the #hits" << endl;
    // printing out the slot and the hits 
    for(unsigned int i = 0; i < max + 1; i++) {
	int count = 0;
	for(unsigned int j = 0; j < word_count.size(); j++) {
	    if(i == word_count[j]) count++;
	} 
	if(count != 0) {
	    cout << i;
	    cout << '\t';
	    cout << count;
	    cout << endl;

	    // to answer 3b
	    slots0[i] = count;
	}
    } 
    

    for(unsigned int i = 0; i < max+1; i++) {
	unsigned int temp = 0;
	for(unsigned int j = i; j < max+1; j++) {
	    temp += slots0[j];
	}
	var+=(temp*i);
    }   
    cout << "The average number of steps for a successful search for hash function 1 would be " << (float)var/(float)num_words << endl;
    cout << "The worst case steps that would be needed to find a word is " << max << endl;

    /* FOR HASH FUNCTION 2 */ 
    cout << endl;
    cout << "Printing the statistics for hash function 2  with hash table size " << tablesize << endl;

    std::vector<unsigned int> word_count1(tablesize);
    std::vector<std::string>::iterator it1;
    // hashing the words into the newly created vector
    for(it1 = vec.begin(); it1 < vec.end(); it1++) {
	int idx = function2(*it1, tablesize);
	//cout << "the hash idx is " << idx << endl;
	word_count1[idx]++;
    }

    max = 0;
    // find the biggest number in vector 
    for(unsigned int i = 0; i < word_count1.size(); i++) {
	if(word_count1[i] > max) max = word_count1[i];
    }
    std::vector<unsigned int> slots(max+1);
    unsigned int var1 = 0;
    cout << "#hits" << '\t' << "slots receiving the #hits" << endl;
    // printing out the slot and the hits 
    for(unsigned int i = 0; i < max + 1; i++) {
	int count = 0;
	for(unsigned int j = 0; j < word_count1.size(); j++) {
	    if(i == word_count1[j]) count++;
	} 
	if(count != 0) {
	    cout << i;
	    cout << '\t';
	    cout << count;
	    cout << endl;

	    // to answer 3b
	    slots[i] = count;
	}
    }

    for(unsigned int i = 1; i < slots.size(); i++) {
	unsigned int temp = 0;
	for(unsigned int j = i; j < slots.size(); j++) {
	    temp += slots[j];
	}
	var1+=(temp*i);
    }   

    cout << "The average number of steps for a successful search for hash function 2 would be " << (float)var1/(float)num_words << endl;
    cout << "The worst case steps that would be needed to find a word is " << max << endl;

    return 0;
}

/*
 * Obtained from "Handbook of Algorithms and Data Structures"
 * A book by Gaston H. Gonnet
 */

unsigned int function1(std::string const & s, unsigned int tablesize) {
    unsigned int i;
    for(i = 0; i < s.length(); i++ ) {
	i = 131*i + (int)s.at(i);
    }
    return i % tablesize;
}

/*
 * Obtained from a previous UCSD CSE 100 Class slide
 * taught by Paul Kube
 */ 

unsigned int function2(std::string const & s, unsigned int tablesize) {
    unsigned int hashVal = 0;
    for(unsigned int i = 0; i < s.length(); i++) {
	hashVal += s[i];
    }
    return hashVal % tablesize;
}
