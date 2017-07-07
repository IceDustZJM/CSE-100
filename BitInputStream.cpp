/*
 * Author: Hwa Chien Hong
 * Date: 4/5/17
 * Assignment Number: PA3
 * File: BitInputStream.cpp
 * Overview: 
 */
#include <iostream>
#include "BitInputStream.h"

//BitInputStream::BitInputStream(){ }

/** Read the next bit from the bit buffer.
 * Fill the buffer from the input stream first if needed. 
 * Return 0 if the bit read is 1.
 * return 0 if the bit read is 0.
 */
int BitInputStream::readBit() {
    // If all the bits in the buffer are read, fill the buffer first 
    if(nbits == 8) fill();
    
    int fullcount = 7;
    unsigned char mask = 0x80;
    unsigned char temp = 0x00;
    // Get the bit at the appropriate location in the bit buffer, and
    // return the appropriate int 
    temp = ((mask >> nbits) & buf); 
    temp = temp >> (fullcount - nbits);
    nbits++;  
    return temp; 
}

/** Fill the buffer from the input */
void BitInputStream::fill() {
    buf = in.get();
    nbits = 0;
}
