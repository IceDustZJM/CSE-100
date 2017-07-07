/*
 * Author: Hwa Chien Hong
 * Date: 10/4/17
 * Assignment Number: PA1
 * File: BST.hpp
 * Overview: This file contains the definition of the template BST, as well as
 * the implementations of the defined functions.
 */

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
#include <algorithm>

template<typename Data>
class BST {
    public:
	/** define iterator as an aliased typename for BSTIterator<Data>. */
	typedef BSTIterator<Data> iterator;

	/** Default constructor.
	  Initialize an empty BST.
	  This is inlined because it is trivial.
	  */
	BST() : root(nullptr), isize(0) {}

	/** Default destructor.
	  Delete every node in this BST.
	  */
	~BST();

	/** Given a reference to a Data item, insert a copy of it in this BST.
	 *  Return a pair where the first element is an iterator 
	 *  pointing to either the newly inserted element or the element 
	 *  that was already in the BST, and the second element is true if the 
	 *  element was newly inserted or false if it was already in the BST.
	 * 
	 *  Note: This function should use only the '<' operator when comparing
	 *  Data items. (should not use ==, >, <=, >=)  
	 */
	std::pair<iterator, bool> insert(const Data& item);


	/** Find a Data item in the BST.
	 *  Return an iterator pointing to the item, or pointing past
	 *  the last node in the BST if not found.
	 *  Note: This function should use only the '<' operator when comparing
	 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
	 *  behind this, see the assignment writeup.
	 */
	iterator find(const Data& item) const;


	/** Return the number of items currently in the BST.
	*/ 
	unsigned int size() const;

	/** Return the height of the BST.
	  height of a tree starts with root at height 0
	  height of an empty tree is -1
	  */ 
	int height() const;


	/** Return true if the BST is empty, else false.
	*/
	bool empty() const;

	/** Return an iterator pointing to the first (smallest) item in the BST.
	*/ 
	iterator begin() const;

	/** Return an iterator pointing past the last item in the BST.
	*/
	iterator end() const;
	BSTNode<Data> * getRoot();
    private:

	/** Pointer to the root of this BST, or 0 if the BST is empty */
	BSTNode<Data>* root;

	/** Number of Data items stored in this BST. */
	unsigned int isize;

	/** Find the first element of the BST
	 * Helper function for the begin method above.
	 */ 
	static BSTNode<Data>* first(BSTNode<Data>* root);

	/** do a postorder traversal, deleting nodes
	*/
	static void deleteAll(BSTNode<Data>* n);

	static int heightHelper(BSTNode<Data>* n);
};


// ********** Function definitions ****************


/** Default destructor.
  Delete every node in this BST.
  */
template <typename Data>
BST<Data>::~BST() {
    deleteAll(root);
}


/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return a pair where the first element is an iterator pointing to either the newly inserted
 *  element or the element that was already in the BST, and the second element is true if the 
 *  element was newly inserted or false if it was already in the BST.
 * 
 *  Data items. (should not use ==, >, <=, >=)  
 */
template <typename Data>
std::pair<BSTIterator<Data>, bool> BST<Data>::insert(const Data& item) {
    if (!root) {
	root = new BSTNode<Data>(item);
	++isize;
	// Returns the iterator pointing to the newly inserted element
	return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(root), true);
    }

    BSTNode<Data>* curr = root;

    while (curr->left || curr->right) {
	if (item < curr->data) {
	    if(curr->left != NULL) curr = curr->left;
	    else break;
	} else if (curr->data < item) {
	    if(curr->right != NULL) curr = curr->right;
	    else break;
	} else {
	    // The first element of the pair is the iterator pointing to the element
	    // that was already in the BST
	    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(curr), false);
	}
    }

    // the first element of the returned pair is the iterator pointing to the
    // element that was already in the BST
    if(curr-> data == item) {
	return std::pair<BSTIterator<Data>,bool>(BSTIterator<Data>(curr),false);
    }

    // Ready to insert
    BSTNode<Data>* newNode = new BSTNode<Data>(item);
    if (item < curr->data) {
	curr->left = newNode;
	newNode->parent = curr;
    } else {
	curr->right = newNode;
	newNode->parent = curr;
    }

    ++isize;

    // first element of the returned pair is the newly inserted element
    return std::pair<BSTIterator<Data>, bool>(BSTIterator<Data>(newNode),true);
}


/** Find a Data item in the BST.
 *  Return an iterator pointing to the item, or pointing past
 *  the last node in the BST if not found.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
template <typename Data>
BSTIterator<Data> BST<Data>::find(const Data& item) const
{
    BSTNode<Data>* curr = root;
    while (curr) {
	if (curr->data < item) {
	    curr = curr->right;
	}
	else if (item < curr->data) {
	    curr = curr->left;
	}
	else {
	    // iterator pointing to the item found
	    return BSTIterator<Data>(curr);
	}
    }
    // pointing past the last node in the BST, because node not found
    return BSTIterator<Data>(nullptr);
}


/**
 * Parameter: N/A
 * Returns: unsigned int of the height 
 * Overview: Return the number of items currently in the BST.
 */ 
template <typename Data>
unsigned int BST<Data>::size() const
{
    return isize;
}

/**
 * Parameter: N/A
 * Returns: the height of the BST 
 * Overview: Return the height of the BST. returns 0 if empty tree
 */
template <typename Data> 
int BST<Data>::height() const
{ 
    if((root == NULL)||(root->right==NULL && root->left==NULL)) return 0;
    return heightHelper(root);
}

/**
 * Parameter: N/A
 * Returns: the root of the tree 
 * Overview: Return the root of the BST. A helper written to test
 */
template <typename Data>
BSTNode<Data> *BST<Data>::getRoot() {
    return root;
}

/**
 * Parameter: BSTNode pointer
 * Returns: the height of the tree
 * Overview: a helper method to the height function above
 */

template <typename Data>
int BST<Data>::heightHelper(BSTNode<Data>* n) {

    // if 0. would instead count the number of nodes in the tree
    // return -1 to account for counting of edges 
    if(n == NULL) return -1;
    int right = heightHelper(n->right);
    int left = heightHelper(n->left);

    // returning the larger number of the two and added with one
    return std::max(right, left)+ 1;
}

/** Return true if the BST is empty, else false.
*/ 
template <typename Data>
bool BST<Data>::empty() const
{
    if(root == NULL) return true;
    return false;
}

/** Return an iterator pointing to the first (smallest) item in the BST.
*/ 
template <typename Data>
BSTIterator<Data> BST<Data>::begin() const
{
    return BSTIterator<Data>(first(root));
}

/** Return an iterator pointing past the last item in the BST.
*/
template <typename Data>
BSTIterator<Data> BST<Data>::end() const
{
    return BSTIterator<Data>(nullptr);
}

/** Find the first element of the BST
 * Helper function for the begin method above.
 */ 
    template <typename Data>
BSTNode<Data>* BST<Data>::first(BSTNode<Data>* root)
{
    BSTNode<Data>* curr = root;
    while(curr->left!=NULL) curr = curr->left;
    return curr;
}

/** do a postorder traversal, deleting nodes
*/
template <typename Data>
void BST<Data>::deleteAll(BSTNode<Data>* n){
    if(n != NULL) {
	deleteAll(n->left);
	deleteAll(n->right);
	delete n;
    }
}
#endif //BST_HPP
