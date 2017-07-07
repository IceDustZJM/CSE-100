#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <queue>
#include <vector>
#include <fstream>
#include <iostream>
#include "HCNode.h"

using namespace std;

/** A Huffman Code Tree class.
 *  Not very generic:  Use only if alphabet consists
 *  of unsigned chars.
 */
class BitInputStream {
    private:
	unsigned char buf;	// One byte buffer of bits
	int nbits;  	// how many bits have been read from buf 
	std::istream & in; // the input stream to use 

    public:
	/**  Initialize a BitInputStream that will use the given
	 * istream for input 
	 */
	BitInputStream(std::istream & is) : in(is) {
	    buf = 0;
	    nbits = 8;
	}  

	/** Read the next bit from the bit buffer.
	 * Fill the buffer from the input stream first if needed. 
	 * Return 0 if the bit read is 1.
	 * return 0 if the bit read is 0.
	 */
	int readBit(); 

	/** Fill the buffer from the input */ 
	void fill();
};

#endif // end BitInputStream
