/*
 * Author: Hwa Chien Hong
 * Date: 4/5/17
 * Assignment Number: PA3
 * File: BitOutputStream.cpp
 * Overview: 
 */
#include <iostream>
#include "BitOutputStream.h"

//BitOutputStream::BitOutputStream(){ }

/** Write the least significant bit of the argument to 
 * the bit buffer, and increment the bit buffer index.
 * But flush the buffer first, if it is full 
 */
void BitOutputStream::writeBit(int i) {
    // flushing the buffer first, since its full    
    int fullcount = 8;
    
    if(nbits == fullcount) flush(); 
    nbits++;
    // use the bitwise OR operator
    int offset = fullcount - nbits; 
    unsigned int temp = i << offset; 
    buf = buf | temp;
    
}

/** Send the buffer to the output, and clear it */
void BitOutputStream::flush() {
    out.put(buf);
    out.flush();
    buf = nbits = 0;
}
