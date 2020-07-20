// Authors: Bridget Goodwine & Hanjing Zhu
// Emails: bgoodwin@nd.edu & hzhu7@nd.edu
//
// merkle tree class for the data structures final project on blockchain

#ifndef MERKLETREE_H
#define MERKLETREE_H

#include "MerkleNode.h"
#include "Transaction.h"

#include<iostream>
#include<cstdlib>

template<class T>
class MerkleTree{

private:
  // tree root node
  MerkleNode<T> *root;

  // private insert method caled by public insert method
  void insert( MerkleNode<T>*& currPtr, const T& value, const int& t ) {

    // create new node with the value
    //MerkleNode<T> *newNode = new MerkleNode<T>( i );

    // if curr pointer is null, this is the location
    // set the pointer to the new value
    if( currPtr == NULL ) {
      currPtr = new MerkleNode<T>(value, t );
      return;
    }

    // if the TIMESTAMP is less than the current data, recurse left
    else if( t < currPtr->timestamp ) {
      insert( currPtr->left, value, t );
    }

    // if the TIMESTAMP is greater than the current data, recurse right
    else if( t > currPtr->timestamp ) {
      insert( currPtr->right, value, t );
    }
    else {
      std::cout << "Something went wrong..." << std::endl;
    }
  }

public:

  // default constructor
  MerkleTree() : root(NULL) {}

  //destructor
  ~MerkleTree() {
    // recursivly delete MerkleTree
    //deleteTree( root );
  }

  // public insert method calls the private one
  void insert( const T& value, const int& t ) {
    // value = the transaction
    // t = the timestamp
    insert( root, value, t );
  }

  void printInOrder( std::ostream& output, const MerkleNode<T>* currNode ) const {

    // return if currNode = NULL
    if( currNode == NULL ) {
      return;
    }

    // recursivly call left child
    printInOrder( output, currNode->left );
    output << currNode->value << " ";
    // recursvily call right child
    printInOrder( output, currNode->right );
  }

  friend std::ostream& operator<<( std::ostream& output, const MerkleTree<T>& theTree) {
    output << "In order: ";
    theTree.printInOrder( output, theTree.root );
    return output;
  }

};

#endif