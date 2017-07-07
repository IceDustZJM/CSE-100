/*
 * Author: Hwa Chien Hong
 * Date: 6/5/17
 * Assignment Number: PA3
 * File: compress.cpp
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

int main(int argc, char* argv[]) {
    unsigned int size = 256; 
    std::string infile(argv[1]);
    std::string outfile(argv[2]);

    unsigned char ch; 
    std::vector<int> freqs(size);
    /* Step 1: open the input file for reading */ 
    fstream fin(infile, fstream::in);
    int numChars = 0;
    /* Step 2: Read bytes from the file */
    while(fin >> noskipws >> ch) { 
          freqs[(int)ch]++;
          numChars++;
    } 
    fin.close(); 

    /* Step 3: use the byte count to contruct Huffman coding tree */ 
    HCTree tree; 
    tree.build(freqs);

    /* Step 4: open the output file for writing */ 
    ofstream output; 
    output.open(outfile, ios::binary);

    /* Step 5: write enough information to the output file to enable the
     * coding tree to be reconstructed when the file is read by the uncompress
     * program
     */
    // Only encode the meaningful counts 
    for(int i = 0; i < freqs.size(); i++) { 
	output.write(((char*)(&freqs.at(i))), sizeof(freqs.at(i)));
    } 
    output.write(((char*)(&numChars)), sizeof(numChars));  
    /* Step 6: open the input file again for reading */ 
    fstream fin1(infile, fstream::in);
    
    /* Step 7: using the Huffman coding tree, translate each byte from the 
     * input file into its code, and append these codes as a sequence of bits
     * to the output file, after the header 
     */
    BitOutputStream outputStream = BitOutputStream(output);
    while(fin1 >> noskipws >> ch) tree.encode(ch, outputStream); 
    outputStream.flush(); 
 
    /* Step 8: close the input and output file */ 
    fin1.close();
    output.close();  
}
