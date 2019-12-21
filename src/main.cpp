#include "Btree.h"
#include "StandardBTree.h"
#include "Splaytree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream fin;
    ofstream B_bound, B_PRep, B;
    ofstream S_bound, S_PRep, S;
    string line;

    bool have_digit=false;
    int key = 0;

    fin.open(argv[1]);
    B_bound.open("../output/BTree_boundary.txt");
    B_PRep.open("../output/BTree_PRep.txt");
    B.open("../output/BTree.txt");
    S_bound.open("../output/STree_boundary.txt");
    S_PRep.open("../output/STree_PRep.txt");
    S.open("../output/STree.txt");
    
    // size_t size = fin.tellg();
    // char *memblock = new char [size];
    // fin.seekg (0, ios::beg);
    // fin.read (memblock, size);
    // fin.close();
// 
    // for ( int i = 0; i < size; ++i ) {
        // cout << int(memblock[i]) << " ";
    // }
    // cout << endl << size << endl;
    // return 0;

    while ( getline(fin, line) ) {

        Btree *btree = new StandardBTree;
        Btree *stree = new SplayTree;
        for ( size_t i = 0; i < line.length(); ++i ) {
            cout << int(line[i]) << " ";
            if ( line[i] >= '\x30' and line[i] <= '\x39' ) {
                key = key * 10 + (line[i] - '\x30');
                have_digit = true;
            } else if ( have_digit ){
                btree->insert(key);
                stree ->insert(key);
                key = 0;
                have_digit = false;
            }                      
            // cout << key << " " << line[i] << " " << int(line[i]) << endl << flush;
        }
        cout << endl;

        btree->printPreorder( B_PRep );
        btree->printLeftBoundary( B_bound );
        btree->printTree( B );
        stree->printPreorder( S_PRep );
        stree->printLeftBoundary( S_bound );
        stree->printTree( S );

        delete btree;
        delete stree;

    }

    fin.close();
    B_bound.close();
    B_PRep.close();
    B.close();
    S_bound.close();
    S_PRep.close();
    S.close();


    
    return 0;
}
