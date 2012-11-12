//
//  decoder.cpp
//  sat-solver
//
//  Created by Grace Gimon on 10/11/12.
//  Copyright (c) 2012 Grace Gimon. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

int board[9][9];

struct Position {
    int row;
    int col;
    int cell;
};

Position invert(int position) {
    Position pos;
    pos.row = position / 81 + 1;
    pos.col = (position - position % 9 + 90 - 81 * (position / 81 + 1)) / 9;
    pos.cell = position % 9;
    
    return pos;
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cout << "Error: Diga un nombre de archivo.\n";
        return 0;
    }
    
    ifstream inputfile(argv[1]);
    
    if (!inputfile.is_open()) {
        cout << "Error: El archivo no existe.\n";
        return 0;
    }
    
    while (inputfile.good()) {
        string line;
        getline(inputfile, line);
        
        // Read SAT solver results.
        
    }
    
    inputfile.close();
}
