#include "Btree.h"

using namespace std;

Btree::~Btree()
{
    vector<TreeNode*> nodeStack;
    TreeNode *curNode;

    nodeStack.push_back(_root);

    // DFS delete
    while ( !nodeStack.empty() )
    {
        curNode = nodeStack.back();
        nodeStack.pop_back();

        if ( curNode->_right != NULL ) nodeStack.push_back(curNode->_right);
        if ( curNode->_left != NULL ) nodeStack.push_back(curNode->_left);

        delete curNode;
    }
    
}

void Btree::printInorder ( ofstream &output )
{
    string outputStr = "";
    printInorder ( outputStr, _root );
    output << outputStr << endl;;
}

void Btree::printInorder ( string &outputStr, TreeNode *curNode )
{
    outputStr += to_string(curNode->_key);

    if ( curNode->_left != NULL || curNode->_right != NULL )
        outputStr += "(";

        if ( curNode->_left != NULL ) {
            printInorder ( outputStr, curNode->_left );
            if ( curNode->_right != NULL )
                outputStr += " ";
        }

        if ( curNode->_right != NULL )
            printInorder ( outputStr, curNode->_right );

        outputStr += ")";
    
    return;
}

void Btree::printLeftBoundary ( ofstream &output )
{
    string outputStr = "";
    _curMaxLevel = -1;
    printLeftBoundary ( outputStr, _root, 0 );
    output << outputStr << endl;;
}

void Btree::printLeftBoundary ( string &outputStr, TreeNode *curNode, int curLevel )
{
    if ( curLevel > _curMaxLevel )
        outputStr += to_string(curNode->_key);
        outputStr += " ";
        _curMaxLevel += 1;

    if ( curNode->_left != NULL )
        printLeftBoundary ( outputStr, curNode->_left, curLevel+1 );

    if ( curNode->_right != NULL )
        printLeftBoundary ( outputStr, curNode->_right, curLevel+1 );
    
    return;
}