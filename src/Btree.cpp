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
    
}

void Btree::printLeftBoundary ( ofstream &output )
{
    
}