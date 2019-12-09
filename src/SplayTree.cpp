#include "SplayTree.h"

void SplayTree::insert ( int key )
{
    TreeNode *newNode = new TreeNode(key);
    insertOne(newNode);
    splay(newNode);
}

void SplayTree::splay ( TreeNode *targetNode )
{
    Direction parentDirection, grandDirection;

    while ( targetNode->_parent != _dummy )
    {
        parentDirection = getDirection( targetNode->_parent, targetNode );
        if ( targetNode->_parent->_parent == _dummy ) {
            rotate( targetNode, parentDirection );
            break;
        } else {
            grandDirection = getDirection( targetNode->_parent->_parent, targetNode->_parent );
            if ( grandDirection == parentDirection ) zig_zig( targetNode, parentDirection );
            else zig_zag( targetNode, parentDirection );
        }
        
    }
    
}

void SplayTree::rotate ( TreeNode *targetNode, Direction parentDirection )
{
    /*
    left child -> rotate right
    right child -> rotate left
    */

    TreeNode *parentNode, *grandNode, *childNode;
    Direction grandDirection;

    parentNode = targetNode->_parent;
    grandNode = parentNode->_parent;
    grandDirection = getDirection( grandNode, parentNode );
    childNode = targetNode->getChild( !parentDirection );
    grandNode->connectChild( targetNode, grandDirection );
    targetNode->connectChild( parentNode, !parentDirection );
    parentNode->connectChild( childNode, parentDirection );
    
}

void SplayTree::zig_zig ( TreeNode *targetNode, Direction parentDirection )
{
    rotate( targetNode->_parent, parentDirection );
    rotate( targetNode, parentDirection );
}

void SplayTree::zig_zag ( TreeNode *targetNode, Direction parentDirection )
{
    rotate( targetNode, parentDirection );
    rotate( targetNode, !parentDirection );
}
