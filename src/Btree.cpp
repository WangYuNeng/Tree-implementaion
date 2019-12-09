#include "Btree.h"

using namespace std;

Btree::Btree ()
{
    _dummy = new TreeNode;
    _dummy->_parent = _dummy;
    _dummy->_key = INT32_MAX;
}

Btree::~Btree ()
{
    vector<TreeNode*> nodeStack;
    TreeNode *curNode;

    nodeStack.push_back(_dummy);

    // DFS delete
    while ( !nodeStack.empty() )
    {
        curNode = nodeStack.back();
        nodeStack.pop_back();

        if ( curNode->_right != nullptr ) nodeStack.push_back(curNode->_right);
        if ( curNode->_left != nullptr ) nodeStack.push_back(curNode->_left);

        delete curNode;
    }
    
}

void Btree::insertOne ( TreeNode *newNode )
{

    TreeNode *curNode, *curParent;
    Direction parentDirection;

    curNode = _dummy->_left;
    curParent = _dummy;
    parentDirection = LEFT;

    while ( curNode != nullptr ) {
        curParent = curNode;
        parentDirection =  getDirection( curNode, newNode );
        curNode = curNode->getChild( parentDirection );
    }
    
    curParent->connectChild( newNode, parentDirection );

}

Direction Btree::getDirection ( TreeNode *node1, TreeNode *node2 )
{
    // Return node2 should belong to node1's right child or not
    return Direction(node1->_key < node2->_key); 
}

void Btree::printPreorder ( ofstream &output )
{
    string outputStr = "";
    printPreorder ( outputStr, _dummy->_left );
    output << outputStr << endl;;
}

void Btree::printPreorder ( string &outputStr, TreeNode *curNode )
{
    outputStr += to_string(curNode->_key);

    if ( curNode->_left != nullptr || curNode->_right != nullptr ) {
        outputStr += "(";

        if ( curNode->_left != nullptr ) {
            printPreorder ( outputStr, curNode->_left );
        }
        else outputStr += "-";
        outputStr += " ";

        if ( curNode->_right != nullptr )
            printPreorder ( outputStr, curNode->_right );
        else outputStr += "-";
        
        outputStr += ")";
    }
    
    return;
}

void Btree::printLeftBoundary ( ofstream &output )
{
    string outputStr = "";
    _curMaxLevel = -1;
    printLeftBoundary ( outputStr, _dummy->_left, 0 );
    output << outputStr << endl;;
}

void Btree::printLeftBoundary ( string &outputStr, TreeNode *curNode, int curLevel )
{
    if ( curLevel > _curMaxLevel )
        outputStr += to_string(curNode->_key);
        outputStr += " ";
        _curMaxLevel += 1;

    if ( curNode->_left != nullptr )
        printLeftBoundary ( outputStr, curNode->_left, curLevel+1 );

    if ( curNode->_right != nullptr )
        printLeftBoundary ( outputStr, curNode->_right, curLevel+1 );
    
    return;
}