/*
 * Author: Hwa Chien Hong
 * Date: 10/4/17
 * Assignment Number: PA1
 * File: main.cpp
 * Overview: This file implements the main method which is the application
 * of the templated BST. By inserting 11347 actors name, and allowing the
 * user to find the actors name.
 */

#include "BST.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <cstddef>

/**
 *  IMPORTANT!! DO NOT CHANGE THE LINES THAT DO I/O BELOW.
 *
 *  Note that size, height, and name are local variables in main that you 
 *  should update accordingly. Also note that actor/actress names will be 
 *  in all caps, last name followed by first name 
 *  (except in odd cases, eg. "50 CENT" and "ICE-T")
 */

using namespace std;

int main(int argc, char* argv[])
{
    //Size of tree should be stored in local variable size.
    //Height of tree should be stored in local variable height.
    //Input name will be stored in a string name
    unsigned int size = 0;
    int height = 0;
    std::string name = "";

    //Check for Arguments
    if(argc != 2){
	cout << "Invalid number of arguments.\n" 
	    << "Usage: ./main <input filename>.\n";
	return -1;
    }

    //Open file 
    ifstream in;
    in.open(argv[1]);

    //Check if input file was actually opened
    if(!in.is_open()) 
    {
	cout<< "Invalid input file. No file was opened. Please try again.\n";
	return -1;
    }
    else {

	// Follow the comments below to add code:

	// Create a new BST here
	BST<string> bst;

	while (getline(in, name)) {
	    // add the name string to the BST
	    bst.insert(name); 
	}

	// Get the height of the BST and store it in height
	height = bst.height();

	// Get the size of the BST and store it in size
	size = bst.size();

	// DO NOT CHANGE THE LINES BELOW
	cout << "Size of tree: " << size << endl;
	cout << "Height of tree: " << height << endl;

	char prompt = 'y';
	while (prompt != 'n') {
	    cout << "Enter actor/actress name: " << endl;
	    getline(cin, name);

	    // Change the if statment to check is name is in the BST
	    if (bst.find(name) != bst.end()) {
		cout << name << " found!" << endl;
	    }
	    else {
		cout << name << " NOT found" << "\n";
	    }
	    cout << "Search again? (y/n)" << endl;
	    cin >> prompt;  // Get the first character
	    // Then ignore until newline
	    cin.ignore( numeric_limits <streamsize> ::max(), '\n' );  
	}
	in.close();

    }
    return 0;
}
