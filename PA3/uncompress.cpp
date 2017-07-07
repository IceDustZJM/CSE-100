/*
 * Author: Hwa Chien Hong
 * Date: 6/5/17
 * Assignment Number: PA3
 * File: uncompress.cpp
 * Overview: 
 */
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include "HCTree.h"
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

using namespace std;

/** 
 * Checkpoint Submission Code:
 * std::getline(fin, value);
 * freqs[idx++] = stoi(value);
 */ 

int main(int argc, char* argv[]) {
    unsigned int size = 256;
    std::string infile(argv[1]);
    std::string outfile(argv[2]);

    std::vector<int> freqs(size);
    /* Step 1: open the input file for reading */ 
    //ifstream fin(infile, fstream::in);
    ifstream fin;
    fin.open(infile);
    int readN;
    int i = 0;
    while(i < freqs.size()) {
	fin.read((char*)&readN, sizeof(readN));
	freqs[i++] = readN;  
    } 
    int numChars; 
    fin.read((char*)&numChars, sizeof(numChars));   
    /* Step 2: Read the file header and reconstruct the tree */
    HCTree tree; 
    tree.build(freqs);

    /* Step 3: open the output file for writing */ 
    ofstream output;  
    output.open(outfile);
    BitInputStream inputStream = BitInputStream(fin);
    
    /* Step 4: using the tree, decode the bits from the input file into
     * the appropriate sequence of bytes, writing them to the output file
     */ 
    while(numChars != 0 && !(fin.eof())) {   
	if(fin.eof()) break;
        int c = tree.decode(inputStream); 
	// checks if the root is null, if so, then break. prevents seg fault
	if(c==-1)break;
        unsigned char ch = (unsigned char)c;
	output << ch;
        numChars--;
    } 

    /* Step 8: close the input and output file */ 
    fin.close();
    output.close(); 
}
