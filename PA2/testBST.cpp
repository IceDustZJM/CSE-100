/*
 * Author: Hwa Chien Hong
 * Date: 10/4/17
 * Assignment Number: PA1
 * File: testBST.cpp
 * Overview: This file is the tester for both the template and the regular int 
 * BST classes. All the methods such as insert, size, empty, and find are 
 * tested in this file. The first half of the file covers the BSTInt tree, 
 * while the second half covers the template tree. 
 */

#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    v.push_back(3);
    v.push_back(4);
    v.push_back(1);
    v.push_back(100);
    v.push_back(-33);
    v.push_back(2);
    //v.push_back(2);
    v.push_back(5);
    v.push_back(6);
    v.push_back(7);
    v.push_back(8);
    v.push_back(9);
    v.push_back(10);
    v.push_back(11);
    //v.push_back(11);

    /* Create an instance of BST holding int */
    BSTInt b;

    /* Test empty */ 
    bool emp = b.empty();
    if(! emp) { 
	cout << "Incorrect bool return of empty" << endl;
	return -1;
    }

    // Could use: for(auto item : v) { instead of the line below
    for(int item : v) {
	bool pr = b.insert(item);
	if(! pr ) {
	    cout << "Incorrect bool return value when inserting " << item 
		<< endl;
	    return -1;
	}
    }

    /* Test size. */
    //cout << "Size is: " << b.size() << endl;
    if(b.size() != v.size()) {
	cout << "... which is incorrect." << endl;
	return -1;
    }

    /* Test find return value. */
    // Test the items that are already in the tree
    for(int item : v) {
	if(!b.find(item)) {
	    cout << "Incorrect return value when finding " << item << endl;
	    return -1;
	}
    }

    /* Test height */ 
    int height = b.height();
    bool h = (9 == height);

    if(! h) {
	cout << "Incorrect bool return value of height " << height
	    << endl;
	return -1;
    }

    /* Personal Test Cases tested here */   

    b.insert(12);
    v.push_back(12);    

    int height1 = b.height();
    bool h1 = (10 == height1);

    if(! h1) {
	cout << "Incorrect bool return value of height " << height1
	    << endl;
	return -1;
    }

    /* Test size II */
    //cout << "Size is: " << b.size() << endl;
    if(b.size() != v.size()) {
	cout << "... which is incorrect." << endl;
	return -1;
    }

    // Inserting duplicate, should return false when trying to insert
    bool incInsert = b.insert(12);
    if( incInsert ) {
	cout << "Incorrect bool return value with insert duplicate" << incInsert << endl;
	return -1;
    }

    // Inserting valid number, should return true when trying to insert
    bool anotherInsert = b.insert(406);
    v.push_back(406);
    if( !anotherInsert ) {
	cout << "Incorrect bool return value with insert duplicate" << anotherInsert << endl;
	return -1;
    }

    /* Test size II */
    //cout << "Size is: " << b.size() << endl;
    if(b.size() != v.size()) {
	cout << "... which is incorrect." << endl;
	return -1;
    }

    /* Test empty II */ 
    bool emp1 = b.empty();
    if(emp1) { 
	cout << "Incorrect bool return of empty1" << endl;
	return -1;
    } 

    /* Personal Test Cases stop here */ 

    // Test the template version of the BST with ints 
    BST<int> btemp;
    for (int item : v) {
	// The auto type here is the pair of BSTIterator<int>, bool
	cout << "Inserting " << item << " into the int template-based BST...";
	auto p = btemp.insert(item);
	if (*(p.first) != item) {
	    cout << "Wrong iterator returned.  "
		<< "Expected " << item << " but got " << *(p.first) << endl;
	    return -1;
	}
	if (!p.second) {
	    cout << "Wrong boolean returned.  Expected true but got " 
		<< p.second << endl;
	    return -1;
	}
	cout << "success!" << endl;

    }

    // Now test finding the elements we just put in
    for (int item: v) {
	cout << "Finding " << item << "...." << endl;
	BSTIterator<int> foundIt = btemp.find(item);
	if (*(foundIt) != item) {
	    cout << "incorrect value returned.  Expected iterator pointing to "
		<< item << " but found iterator pointing to " << *(foundIt) 
		<< endl;
	    return -1;
	}
	cout << "success!" << endl;
    }

    // cout << "Height of " << btemp.height() << "...";

    // Test the iterator: The iterator should give an in-order traversal

    // Sort the vector, to compare with inorder iteration on the BST

    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) {
	if(! (it != en) ) {
	    cout << *it << "," << *vit 
		<< ": Early termination of BST iteration." << endl;
	    return -1;

	}
	cout << *it << endl;
	if(*it != *vit) {
	    cout << *it << "," << *vit 
		<< ": Incorrect inorder iteration of BST." << endl;
	    return -1;
	}
	++it;
    }

    /* Personal Test Cases Start Here */

    //cout << "success!" << endl;
    /*
       BSTNode<int> * root= btemp.getRoot();
       while(root->left!=NULL) root = root->left;

       cout << (*root).data << endl;
       BSTNode<int> * second = (*root).successor();
       if(second != NULL ) cout << (*second).data << endl;
       BSTNode<int> * third = (*second).successor();
       if(third != NULL ) cout << (*third).data << endl;
       BSTNode<int> * four = (*third).successor();
       if(four != NULL ) cout << (*four).data << endl;
       BSTNode<int> * five = (*four).successor();
       if(five != NULL ) cout << (*five).data << endl;
       BSTNode<int> * six = (*five).successor();
       if(six != NULL ) cout << (*six).data << endl;
       BSTNode<int> * seven = (*six).successor();
       if(seven != NULL ) cout << (*seven).data << endl;
       */

    btemp.insert(406);

    /* Test size II */
    //cout << "Size is: " << b.size() << endl;
    if(btemp.size() != v.size()) {
	cout << "... which is incorrect." << endl;
	return -1;
    }

    cout << "All tests passed!" << endl;
    return 0;
}
