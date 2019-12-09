#include "Btree.h"
#include "StandardBTree.h"
#include "Splaytree.h"
#include <iostream>
#include <fstream>

int main(int argc, char const *argv[])
{
    Btree *tree = new SplayTree;
    std::ifstream fin;
    std::ofstream fout;
    int key;

    fin.open(argv[1]);
    fout.open(argv[2]);

    while ( fin >> key ) {
        tree->insert(key);
        tree->printPreorder( fout );
        tree->printLeftBoundary( fout );
    }

    fin.close();
    fout.close();

    
    return 0;
}
