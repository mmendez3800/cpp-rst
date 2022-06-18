/******************************************************************************

File Name:    RST.hpp
Description:  This program creates a class called RST, creating a randomized
              search tree, allowing us to perform various functions such as
              inserting a node, rotating parts of our tree to the left or
              right, and finding a node.
              
******************************************************************************/


#ifndef RST_HPP
#define RST_HPP
#include "BST.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;


/******************************************************************************
class RST

Description: Creates a RST, or randomized search tree, which will allow us to
    insert nodes, rotate nodes left or right, and to locate nodes in our tree

Public functions:
    insert        - Inserts a node into our RST if it does not exist yet
    BSTinsert     - Calls the insert function of BST class
    findAndRotate - Finds a node in the tree and rotates it left or right
******************************************************************************/
template <typename Data>
class RST : public BST<Data> {

public:


  /****************************************************************************
  Function Name:  insert
  Purpose:        This function inserts an item into our RST
  Description:    This function calls BSTinsert to insert a node into our RST.
                  It then checks to see if the insert is successful or not. If
                  it is, it will check to see if the priority of the node
                  matches with the structure of the RST. If not, it will rotate
                  the node either to the left or to the right depending on its
                  position. It will keep doing this until the node is in a
                  position where both the BST and treap properties are met
  Input:          item: the data of the BSTNode we are attempting to insert 
                  into our tree
  Result:         true if the insert was performed successfully
                  false if the insert was performed unsuccessfully
  ****************************************************************************/
  virtual bool insert(const Data& item) {

    /* Variable to indicate whether insertiong was successful or not */
    bool inserted = false;

    BSTNode<Data>* current = BST<Data>::root;
    BSTNode<Data>* insertingNode = new BSTNode<Data> (item);

    /* If statement is executed when current does not exist */
    if (!current) {
      BST<Data>::root = insertingNode;
      inserted = true;
    }

    /* While loop is executed while current exists */
    while (current) {

      /* If statement is executed when data of current is less than item */
      if (current -> data < item) {

        /* If statement is executed when current's right child doesn't exist */
        if (!current -> right) {

          /* We set insertingNode as current's right child and set our variable
           * to true */
          current -> right = insertingNode;
          current -> right -> parent = current;
          inserted = true;
          break;
        }

        else

          /* Recursion is used to traverse down the right subtree */
          current = current -> right;
      }

      /* Else if statement is executed when data of current is greater than
       * item */
      else if (item < current -> data) {

        /* If statement is executed when current's left child doesn't exist */
        if (!current -> left) {

          /* We set insertingNode as current's left child and set our variable
           * to true */
          current -> left = insertingNode;
          current -> left -> parent = current;
          inserted = true;
          break;
        }

        else

          /* Recursion is used to traverse down the left subtree */
          current = current -> left;
      }

      else
        break;
    }

    /* If statement is executed when insertion is successful */
    if (inserted)
      ++BST<Data>::isize;

    else {

      /* We free the node created since it was not inserted into our BST */
      delete insertingNode;
      return inserted;
    }

    insertingNode -> priority = rand();

    /* If statement is executed if current, insertingNode's parent, does not
     * exists */
    if (!current)
      return inserted;

    /* While loop executes as long as priority of insertingNode is less than
     * priority of current */
    while (insertingNode -> priority < current -> priority) {

      /* If statement is executed when current's left child is the same as
       * insertingNode */
      if (current -> left == insertingNode) {

        /* rotateRight method is called and current is updated */
        rotateRight(current, insertingNode);
        current = insertingNode -> parent;
      }

      else {

        /* rotateLeft method is called and current is updated */
        rotateLeft(current, insertingNode);
        current = insertingNode -> parent;
      }

      /* If statement is executed when current does not exist, meaning
       *insertingNode has become the root of our RST */
      if (!current)
        break;
    }

    return inserted;
  }

private:


  /****************************************************************************
  Function Name:  rotateRight
  Purpose:        This function rotates a parent and child node to the right
  Description:    This function performs a 'right rotation' that changes the
                  structure of the tree without interfering with the size, data
                  content, and left -> right order of nodes. This is done by
                  changing the 'left', 'right', and/or 'parent' pointers of a
                  subset of nodes without changint their priority values
  Input:          par:  The parent node in the RST with a left child 
                  child:  The left child of par
  Result:         The placement of par and child will be different in our tree,
                  placing child in place of par and placing par as the right
                  child of child
  ****************************************************************************/
  void rotateRight( BSTNode<Data>* par, BSTNode<Data>* child ) {

    /* We create nodes to hold the data of child's right child and par's
     * parent */
    BSTNode<Data>* temp = child -> right;
    BSTNode<Data>* parParent = par -> parent;

    /* If statement is executed if parParent exists */
    if(parParent) {

      /* If statement is executed if par is the same as parParent's left
       * child */
      if(par == parParent -> left)
        parParent -> left = child;

      else
        parParent -> right = child;
    }

    else

      /* We update the root since we can determine that par is the current root
       * of our tree */
      BST<Data>::root = child;

    /* We update the left, right, and parent pointers of child and par */
    child -> right = par;
    par -> left = temp;
    child -> parent = par -> parent;
    par -> parent = child;

    /* If statement is executed if temp exists */
    if(temp)
      temp -> parent = par;
  }


  /****************************************************************************
  Function Name:  rotateLeft
  Purpose:        This function rotates a parent and child node to the left
  Description:    This function performs a 'left rotation' that changes the
                  structure of the tree without interfering with the size, data
                  content, and left -> right order of nodes. This is done by
                  changing the 'left', 'right', and/or 'parent' pointers of a
                  subset of nodes without changint their priority values
  Input:          par:  The parent node in the RST with a left child 
                  child:  The right child of par
  Result:         The placement of par and child will be different in our tree,
                  placing child in place of par and placing par as the left
                  child of child
  ****************************************************************************/
  void rotateLeft( BSTNode<Data>* par, BSTNode<Data>* child ) {

    /* We create nodes to hold the data of child's left child and par's
     * parent */
    BSTNode<Data>* temp = child -> left;
    BSTNode<Data>* parParent = par -> parent;

    /* If statement is executed when parParent exists */
    if(parParent) {

      /* If statement is executed when par is the same as parParent's left
       * child */
      if(par == parParent -> left)
        parParent -> left = child;

      else
        parParent -> right = child;
    }

    else

      /* We update the root since we can determine that par is the current root
       * of our tree */
      BST<Data>::root = child;

    /* We update the left, right, and parent pointers of child and par */
    child -> left = par;
    par -> right = temp;
    child -> parent = par -> parent;
    par -> parent = child;

    /* If statement is executed if temp exists */
    if(temp)
      temp -> parent = par;
  }

public:


  /****************************************************************************
  Function Name:  BSTinsert
  Purpose:        This function inserts a node into our tree
  Description:    This function calls the insert function from our BST class
                  and inserts a node into the tree. This differs from the
                  insert method of RST since it does not rotate nodes due to
                  priority
  Input:          item: The data of the BSTNode we are attempting to insert
                  into our tree
  Result:         true if the node was inserted successfully
                  false if the node was inserted unsuccessfully
  ****************************************************************************/
  bool BSTinsert(const Data& item) { 
    return BST<Data>::insert(item);
  }
 

  /****************************************************************************
  Function Name:  findAndRotate
  Purpose:        This function finds and rotates a node in our tree
  Description:    This function locates the node for an item and rotates it left
                  or right without changing the left -> right order of nodes in
                  the RST
  Input:          item:         The data of the BSTNode we are attempting to
                                rotate
                  leftOrRight:  Boolean to determine if we rotate left or right
                                if true then left, if false then right
  Result:         0 if the item was found and had a child to rotate with
                  1 if the item was not found / it had no child to rotate with
                  -1 if the rotation failed for other reasons
  ****************************************************************************/
  int findAndRotate(const Data& item, bool leftOrRight) {
     BSTNode<Data>* current = RST<Data>::root;
     while ( current != 0 ) {
       if ( item < current->data ) {
         current = current->left;
       }
       else if ( current->data < item ) {
         current = current->right;
       }
       else {  // already in the tree
         break;
       }
     }
     
     if (current == 0 or current->data != item) {
       return 1;
     }
     
     if (leftOrRight) {
       if (current->right == 0) {
         return 1;
       }
       BSTNode<Data>* right = current->right;
       rotateLeft(current, current->right);
       
       // make sure we actually do a rotation
       if (current->right == right) {
         return -1;
       }
     }
     else {
       if (current->left == 0) {
         return 1;
       }
       BSTNode<Data>* left = current->left;
       rotateRight(current, current->left);
       
       // make sure we actually do a rotation
       if (current->left == left) {
         return -1;
       }
     }
     return 0;
  }
};


#endif // RST_HPP
