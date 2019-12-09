#include "Btree.h"

class SplayTree: public Btree
{
public:
    void insert ( int key );
private:
    // splay target node to top
    void splay ( TreeNode *targetNode );

    // rotate target node to its parent's position
    void rotate ( TreeNode *targetNode, Direction parentDirection );

    // splay operations
    void zig_zig ( TreeNode *targetNode, Direction parentDirection );
    void zig_zag ( TreeNode *targetNode, Direction parentDirection );
};