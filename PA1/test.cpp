/*
 * Author: Hwa Chien Hong
 * Date: 19/4/17
 * Assignment Number: PA2
 * File: test.cpp
 * Overview: The test file to test for the insert and find function of BST, 
 * hashtable and trie. Also uses the provided dictionary to test for 
 * validity of the program.
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


int main(int argc, char** argv)
{
    
    //Initialize words
    vector<std::string> words;
    vector<string>::iterator wit;
    vector<string>::iterator wen;
    //initialize nonwords
    set<string> nope;
    set<string>::iterator nit;
    set<string>::iterator nen;

    //Initialize data structures
    DictionaryBST d_bst;
    DictionaryHashtable d_ht;
    DictionaryTrie dt;
    int t_bst, t_ht, tt;
    
    
    words.push_back("harry");
    words.push_back("sriram");
    words.push_back("cse");
    words.push_back("crucio");
    words.push_back("autocomplete");
    words.push_back("jerry");
    words.push_back("cool");
    words.push_back("nobug");
    words.push_back("hundred");
    words.push_back("testing");
    //words.push_back("are you not entertained");
    //words.push_back("never gonna give you up");
    //words.push_back("");
    
    
    words.push_back("basketball");
    words.push_back("asterisk");
    words.push_back("basket");
    words.push_back("application");
    //words.push_back("a");
    words.push_back("app");
    words.push_back("gugglebee");
    words.push_back("waldos");
    
    words.push_back("hello world");
    words.push_back("are you not entertained");
    words.push_back("never gonna give you up");


    cout << "Inserting into Dictionaries..." << endl;

    wit = words.begin();
    wen = words.end();
    for(; wit != wen; ++wit)
    {
	cout << "Inserting: \"" << *wit << "\"... ";
	t_bst = d_bst.insert(*wit);
	t_ht = d_ht.insert(*wit);
	tt = dt.insert(*wit, 1);
	//cout << t_bst << " " << t_ht << " "<< tt << "... ";
	if(!t_bst)
	{
	    cout << "failed for DictionaryBST... ";
	}
	if(!t_ht)
	{
	    cout << "failed for DictionaryHashset... ";
	}
	if(!tt)
	{
	    cout << "failed for DictionaryTrie... ";
	}
	if(t_bst && t_ht && tt)
	{
	    cout << "PASSED! :D ";
	}
	cout << endl;
    }
    dt.insert("akme",5);
    dt.insert("aol", 2);
    dt.insert("aloof", 11);
    dt.insert("aloha", 15);
    dt.insert("angular", 20);

    cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

    wit = words.begin();
    wen = words.end();
    for(; wit != wen; ++wit)
    {
	cout << "Inserting: \"" << *wit << "\"... ";
	t_bst = d_bst.insert(*wit);
	t_ht = d_ht.insert(*wit);
	tt = dt.insert(*wit, 0);

	if(t_bst)
	{
	    cout << "failed for DictionaryBST... ";
	}
	if(t_ht)
	{
	    cout << "failed for DictionaryHashset... ";
	}
	if(tt)
	{
	    cout << "failed for DictionaryTrie... ";
	}
	if(!t_bst && !t_ht && !tt)
	{
	    cout << "PASSED! :D ";
	}
	cout << endl;
    }

    cout << endl;
    
    cout << "Testing find function on Dictionaries..." << endl;

    wit = words.begin();
    wen = words.end();
    for(; wit != wen; ++wit)
    {
	cout << "Finding: \"" << *wit << "\"... ";
	t_bst = d_bst.find(*wit);
	t_ht = d_ht.find(*wit);
	tt = dt.find(*wit);
	//cout << t_bst << " " << t_ht << " "<< tt << "... ";
	if(!t_bst)
	{
	    cout << "failed for DictionaryBST... ";
	}
	if(!t_ht)
	{
	    cout << "failed for DictionaryHashset... ";
	}
	if(!tt)
	{
	    cout << "failed for DictionaryTrie... ";
	}
	if(t_bst && t_ht && tt)
	{
	    cout << "PASSED! :D ";
	}
	cout << endl;
    } 
    
    /* Testing with large Dictionaries */
    DictionaryTrie dt1;
    ifstream fin;
    fin.open("freq_dict.txt");
    Utils::load_dict(dt1, fin);
    vector<std::string> vecs = dt1.predictCompletions("all", 10);
    for(unsigned int i = 0; i < vecs.size(); i++) {
       cout << "" + vecs[i] << endl;
    }
    return 0;
}
