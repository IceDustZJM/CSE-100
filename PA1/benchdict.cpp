/*
 * Author: Hwa Chien Hong
 * Date: 22/4/17
 * Assignment Number: PA2
 * File: benchdict.cpp
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

int main(int argc, char* argv[])
{
    unsigned int min_size = atoi(argv[1]);
    unsigned int step_size = atoi(argv[2]);
    unsigned int num_iterations = atoi(argv[3]);
    std::string dictfile(argv[4]);

    vector<string>::iterator wit;
    vector<string>::iterator wen;

    cout << "Benchmarking DictionaryBST" << endl;

    for(unsigned int i = 0; i < num_iterations; i++) {
	// Create a new dictionary object and load min_size + i*step_size words
	// from the beginning of the dictionary file
	DictionaryBST* d_bst = new DictionaryBST();
	ifstream fin;
	fin.open(dictfile);

	Utils::load_dict(*d_bst, fin, min_size + i*step_size);

	// Read the next 100 words from the dictionary file 
	// then compute the time needed to find those words in the dict object
	vector<std::string> words;
	Utils::load_vector(words, fin, 100);

	// Compute the time to find uninserted words
	int many_times = 100;
	long long sum_time = 0;
	for(int j = 0; j < many_times; j++) {
	    Timer t;
	    t.begin_timer();
	    wit = words.begin();
	    wen = words.end();
	    for(; wit != wen; ++wit)
	    {
		d_bst->find(*wit);
	    }
	    long long time = t.end_timer();
	    sum_time += time;   
	}

	// Result printed out
	cout << "Dictsize: " << min_size + i*step_size;
	cout << '\t'; 
	cout << "Averaged Time: " << sum_time/many_times << endl;
	// Reset
	fin.clear();
	fin.seekg(0);

	delete d_bst;
    }

    cout << '\n';
    cout << "Benchmarking DictionaryHashtable" << endl;

    for(unsigned int i = 0; i < num_iterations; i++) {
	// Create a new dictionary object and load min_size + i*step_size words
	// from the beginning of the dictionary file
	DictionaryHashtable * d_ht = new DictionaryHashtable();
	ifstream fin;
	fin.open(dictfile);
	Utils::load_dict(*d_ht, fin, min_size + i*step_size);

	// Read the next 100 words from the dictionary file 
	// then compute the time needed to find those words in the dict object
	vector<std::string> words;
	Utils::load_vector(words, fin, 100);

	// Compute the time to find uninserted words
	int many_times = 100;
	long long sum_time = 0;
	for(int j = 0; j < many_times; j++) {
	    Timer t;
	    t.begin_timer();
	    wit = words.begin();
	    wen = words.end();
	    for(; wit != wen; ++wit)
	    {
		d_ht->find(*wit);
	    }
	    long long time = t.end_timer();
	    sum_time += time;   
	}

	cout << "Dictsize: " << min_size + i*step_size;
	cout << '\t'; 
	cout << "Averaged Time: " << sum_time/many_times << endl;
	// Reset
	fin.clear();
	fin.seekg(0);

	delete d_ht;
    }

    cout << '\n';
    cout << "Benchmarking DictionaryTrie" << endl;

    for(unsigned int i = 0; i < num_iterations; i++) {
	// Create a new dictionary object and load min_size + i*step_size words
	// from the beginning of the dictionary file
	DictionaryTrie * dt = new DictionaryTrie();
	ifstream fin;
	fin.open(dictfile);
	Utils::load_dict(*dt, fin, min_size + i*step_size);

	// Read the next 100 words from the dictionary file 
	// then compute the time needed to find those words in the dict object
	vector<std::string> words;
	Utils::load_vector(words, fin, 100);

	// Compute the time to find uninserted words
	int many_times = 100;
	long long sum_time = 0;
	for(int j = 0; j < many_times; j++) {
	    Timer t;	    
	    t.begin_timer();
	    wit = words.begin();
	    wen = words.end();
	    for(; wit != wen; ++wit)
	    {
		dt->find(*wit);
	    }
	    long long time = t.end_timer();
	    sum_time += time;   
	}

	cout << "Dictsize: " << min_size + i*step_size;
	cout << '\t'; 
	cout << "Averaged Time: " << sum_time/many_times << endl;
	// Reset
	fin.clear();
	fin.seekg(0);

	delete dt;
    }

    return 0;
}
