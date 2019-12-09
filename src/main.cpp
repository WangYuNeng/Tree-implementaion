#include "Btree.h"
#include "StandardBTree.h"
#include "Splaytree.h"
#include <iostream>
#include <fstream>

int main(int argc, char const *argv[])
{
    Btree *tree = new StandardBTree;
    std::ofstream fout;
    fout.open(argv[1]);

    int input_length, key;
    std::cin >> input_length;

    for ( int i = 0; i < input_length; i++ )
    {
        std::cin >> key;
        tree->insert(key);
        tree->printInorder( fout );
        tree->printLeftBoundary( fout );
    }

    
    return 0;
}
