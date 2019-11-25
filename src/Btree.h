#ifndef B_TREE
#define B_TREE

#include <fstream>
#include <vector>

class Btree;
class TreeNode;

class Btree
{
public:

    // function
    Btree() {};
    ~Btree();

    // function required by spec
    virtual void insert ( int key );
    void printInorder ( std::ofstream &output );
    void printLeftBoundary ( std::ofstream &output );

    /*
    virtual TreeNode* find ( int key );
    virtual void delete ( int key );
    */

protected:

    // data
    TreeNode *_root;

};

class TreeNode
{
public:

    // data
    TreeNode *_left, *_right, *_parent;
    int _key;

    // function
    TreeNode () { *_left = *_right = *_parent = NULL; };
    TreeNode ( int k ) { *_left = *_right = *_parent = NULL; _key = k; };
    ~TreeNode () {};
};


#endif