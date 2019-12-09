#include "StandardBTree.h"

void StandardBTree::insert ( int key )
{
    TreeNode *newNode = new TreeNode(key);

    TreeNode *curNode, *curParent;
    bool parentDirection;

    curNode = _dummy->_left;
    curParent = _dummy;
    parentDirection = LEFT;

    while ( curNode != nullptr ) {
        curParent = curNode;
        if ( curNode->_key > key ) {
            parentDirection = LEFT;
            curNode = curNode->_left;
        } else {
            parentDirection = RIGHT;
            curNode = curNode->_right;
        }
    }
    
    newNode->_parent = curParent;
    if ( parentDirection == LEFT )
        curParent->_left = newNode;
    else
        curParent->_right = newNode;

}