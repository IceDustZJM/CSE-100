/*
 * Author: Hwa Chien Hong
 * Date: 5/6/17
 * Assignment Number: PA3
 * File: HCTree.cpp
 * Overview: The implementation file of the HCTree methods. The methods 
 * requried to be written are listed from the .h file. 
 */
#include <queue>
#include <stack>
#include <iostream>
#include <fstream>
#include "HCTree.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"

/* 
 * Description: method that builds the Huffman tree based on the frequency 
 * of characters passed in as a vecotr
 * Parameter: the vector containing the frequencies of each character
 * Return: void 
 */
void HCTree::build(const vector<int>& freqs) {
    // a priority queue that compares differently 
    std::priority_queue<HCNode*, std::vector<HCNode*>, HCNodePtrComp> q;

    // Step 1: translate the freqs into a priority queue so that we can 
    // construct the tree in an ordered form 
    for(unsigned int i = 0; i < freqs.size(); i++) { 
	// Only add a new Node to the priority queue if count is not zero
	if(freqs.at(i) != 0) { 
	    HCNode * n = new HCNode(freqs.at(i), i);
	    // leaves[i] points to the leaf node containing byte i
	    leaves[i] = n; 
	    q.push(n);
	}
    }  

    // Step 2: construct the actual Huffman tree
    while(!q.empty()) {
	// creating the parent which would merge the next two consecutive 
	// elements 
	HCNode * par = new HCNode(0,0);
	/* Initializing sequence */ 
	// 1. Get the first element from queue
	// 2. pop the element off, so that we can access the next
	// 3. assign the left and right child of dummy parent 
	// 4. assign the parent of the left and right child

	HCNode * right = q.top();
	q.pop();
	par -> c0 = right;
	right -> p = par;

	HCNode * left = q.top();
	q.pop(); 
	par -> c1 = left;
	left -> p = par;

	// Set the combine count of the two children 
	par->count = (right->count) + (left->count);

	// once the bottom level is done, proceed to the second level
	q.push(par); 

	// the root is the newest parent in the queue 
	if(q.size() == 1) { 
	    root = q.top();
	    q.pop();
	}
    }
}


void HCTree::encode(byte symbol, BitOutputStream& out) const{
    std::stack<int> stack; 

    // Step 1: find the correct leaf to traverse upward from 
    HCNode * n = leaves[symbol]; 

    // Algorithm:for each symbol in the message, output the sequence
    // of bits given by 1's and 0's on the path from the root of the 
    // tree to that symbol. 
    // if(n == NULL)return;

    // Step 2: traverse upward until the root is reached 
    while(n != root) {
	// if its the 0th child 
	if(n->p->c0 == n) stack.push(0);
	// if its the 1th child 
	else if (n->p->c1 == n) stack.push(1);
	// must traverse up, so reassign to parent
	n = n->p;
    } 

    while(!stack.empty()) { 
	out.writeBit(stack.top());
	stack.pop(); 
    }
}


/* 
 * Description: the encoding methods that takes in the byte to be encded and 
 * the output file where the encoded sequence will go. 
 * Parameter: the byte symbol to be encoded, and the output file stream to be
 * printed to
 * Return: void 
 */
void HCTree::encode(byte symbol, ofstream& out) const{
    std::stack<int> stack; 

    // Step 1: find the correct leaf to traverse upward from 
    HCNode * n = leaves[symbol]; 

    /*  
     * Algorithm: for each symbol in the message, output the sequence
     * of bits given by 1's and 0's on the path from the root of the 
     * tree to that symbol. 
     */
    //if(n == NULL)return;
    // Step 2: traverse upward until the root is reached 
    while(n != root) {
	// if its the 0th child 
	if(n->p->c0 == n) stack.push(0);
	// if its the 1th child 
	else if (n->p->c1 == n) stack.push(1);
	// must traverse up, so reassign to parent
	n = n->p;
    } 

    while(!stack.empty()) { 
	out << stack.top();
	stack.pop(); 
    }
}


int HCTree::decode(BitInputStream& in) const{
    // while children still exist, traverse downward until the child node
    // is reached. then output the symbol
    HCNode * n = root; 
    if(root == NULL) return -1;

    // till we reach the leaf node
    while(n->c0 || n->c1) { 
	int bit = in.readBit();
	if(bit == 0) n = n->c0;
	else if (bit==1)  n = n->c1;
	else return -1;
    } 
    return n->symbol;  
}

/* 
 * Description: Decode method that decode each individual coded sequence
 * and then proceed to output the represented symbol
 * Parameter: the file stream that is being passed in to be decoded
 * Return: int -> the symbol represented by the coded sequence 
 */
int HCTree::decode(ifstream& in) const{
    // while children still exist, traverse downward until the child node
    // is reached. then output the symbol
    HCNode * n = root; 
    if(root == NULL) return -1;

    // till we reach the leaf node
    while(n->c0 || n->c1) { 
	int bit = in.get()-'0';
	if (bit == 0) n = n->c0;
	else if (bit==1)  n = n->c1;
	else return -1;
    } 
    return n->symbol;    
}

/* 
 * Description: Helper method to recursively delete the allocated node
 * on the heap. 
 * Parameter: the root node, which will be passed in
 * Return: void 
 */
void HCTree::deleteAll(HCNode * n) {
    if(n != NULL) { 
	deleteAll(n->c0);
	deleteAll(n->c1);
	delete n;
    }
}

HCTree::~HCTree() { deleteAll(root); } 
