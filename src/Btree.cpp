#include "Btree.h"

using namespace std;

Btree::Btree ()
{
    _dummy = new TreeNode;
    _dummy->_parent = _dummy;
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

void Btree::printInorder ( ofstream &output )
{
    string outputStr = "";
    printInorder ( outputStr, _dummy->_left );
    output << outputStr << endl;;
}

void Btree::printInorder ( string &outputStr, TreeNode *curNode )
{
    outputStr += to_string(curNode->_key);

    if ( curNode->_left != nullptr || curNode->_right != nullptr ) {
        outputStr += "(";

        if ( curNode->_left != nullptr ) {
            printInorder ( outputStr, curNode->_left );
        }
        else outputStr += "-";
        outputStr += " ";

        if ( curNode->_right != nullptr )
            printInorder ( outputStr, curNode->_right );
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