#ifndef B_TREE
#define B_TREE

#include <fstream>
#include <vector>
#include <string>

class Btree;
class TreeNode;

typedef bool Direction;
#define LEFT false
#define RIGHT true
class Btree
{
public:

    // function
    Btree();
    ~Btree();

    // function required by spec
    virtual void insert ( int key ) = 0;
    void printPreorder ( std::ofstream &output );
    void printLeftBoundary ( std::ofstream &output );

    /*
    virtual TreeNode* find ( int key );
    virtual void delete ( int key );
    */

protected:

    // data
    TreeNode *_dummy; // _dummy->left = root, _dummy->parent = _dummy

    // Basic method inserting one node
    void insertOne ( TreeNode *newNode );
    Direction getDirection ( TreeNode *parentNode, TreeNode *childNode );

    void printPreorder ( std::string &outputStr, TreeNode *curNode );

    int _curMaxLevel;
    void printLeftBoundary ( std::string &outputStr, TreeNode *curNode, int curLevel );
};

class TreeNode
{
public:

    // data
    TreeNode *_left, *_right, *_parent;
    int _key;

    // function
    TreeNode () { _left = _right = _parent = nullptr; };
    TreeNode ( int k ) { _left = _right = _parent = nullptr; _key = k; };
    ~TreeNode () {};

    TreeNode*& getChild ( Direction d ) { 
        if ( d == LEFT)
            return _left;
        else
            return _right;
    }

    void connectChild ( TreeNode *childNode, Direction d ) {
        this->getChild(d) = childNode;
        if ( childNode != nullptr ) 
            childNode->_parent = this;
    }
};


#endif