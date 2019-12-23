#include "Btree.h"

using namespace std;

Btree::Btree ()
{
    _dummy = new TreeNode;
    _dummy->_parent = _dummy;
    _dummy->_key = INT32_MAX;
    treeSize = 0;
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
    treeSize +=1;
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
    outputStr += "\n";
    printUTF8( output, outputStr );
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
    outputStr += "\n";
    printUTF8( output, outputStr );
}

void Btree::printLeftBoundary ( string &outputStr, TreeNode *curNode, int curLevel )
{
    if ( curLevel > _curMaxLevel ) {
        if ( curLevel != 0 ) outputStr += " ";
        outputStr += to_string(curNode->_key);
        _curMaxLevel += 1;
    }

    if ( curNode->_left != nullptr )
        printLeftBoundary ( outputStr, curNode->_left, curLevel+1 );

    if ( curNode->_right != nullptr )
        printLeftBoundary ( outputStr, curNode->_right, curLevel+1 );
    
    return;
}

void Btree::printUTF8 ( ofstream &output, string &outputStr )
{
    string utf8Str = "";
    for ( size_t i = 0; i < outputStr.length(); ++i ) {
        switch (outputStr[i])
        {
        case '0':
            utf8Str += "\u0030";
            break;
        case '1':
            utf8Str += "\u0031";
            break;
        case '2':
            utf8Str += "\u0032";
            break;
        case '3':
            utf8Str += "\u0033";
            break;
        case '4':
            utf8Str += "\u0034";
            break;
        case '5':
            utf8Str += "\u0035";
            break;
        case '6':
            utf8Str += "\u0036";
            break;
        case '7':
            utf8Str += "\u0037";
            break;
        case '8':
            utf8Str += "\u0038";
            break;
        case '9':
            utf8Str += "\u0039";
            break;
        case ' ':
            utf8Str += "\u00A0";
            break;
        case '-':
            utf8Str += "\u002D";
            break;
        case '(':
            utf8Str += "\u0028";
            break;
        case ')':
            utf8Str += "\u0029";
            break;
        case '\n':
            utf8Str += "\x0D";
            utf8Str += "\x0A";
            // utf8Str += "\u000A";
            break;
        default:
            break;
        }
    }
    output << utf8Str;
}

void Btree::printTree ( ofstream &output ) 
{
    _order = 0;
    inorderTraverse ( _dummy );

    queue<std::pair<TreeNode*, int>> nodeQueue;
    std::pair<TreeNode*, int> curPair;
    TreeNode *curNode;
    int curLevel, preLevel = 0, curLevelChrCount = 0;
    string outputStr = "";

    nodeQueue.push( std::pair<TreeNode*, int>(_dummy->_left, 0) );

    while ( !nodeQueue.empty() )
    {
        curPair = nodeQueue.front();
        nodeQueue.pop();
        if ( curPair.first != nullptr ) {
            curNode = curPair.first;
            curLevel = curPair.second;
            nodeQueue.push(std::pair<TreeNode*, int>(curNode->_left, curLevel+1));
            nodeQueue.push(std::pair<TreeNode*, int>(curNode->_right, curLevel+1));
            if ( curLevel != preLevel ) {
                outputStr += "\n";
                preLevel = curLevel;
                curLevelChrCount = 0;
            }
            for ( int i = 0; i < (curNode->_order * 3 - curLevelChrCount); ++i ) {
                outputStr += " ";
            }
            outputStr += to_string(curNode->_key);
            curLevelChrCount = curNode->_order * 3 + 1 + (curNode->_key/10 > 0) + (curNode->_key/100 > 0);
        }
    }
    outputStr += "\n";
    printUTF8(output, outputStr);
}

void Btree::inorderTraverse ( TreeNode *curNode )
{
    if ( curNode == nullptr ) 
        return;

    inorderTraverse( curNode->_left );
    if ( curNode != _dummy ) {
        curNode->_order = _order;
        _order += 1;
    }
    inorderTraverse( curNode->_right );
}