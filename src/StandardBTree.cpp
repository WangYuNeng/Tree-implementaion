#include "StandardBTree.h"

void StandardBTree::insert ( int key )
{
    TreeNode *newNode = new TreeNode(key);
    insertOne(newNode);
}