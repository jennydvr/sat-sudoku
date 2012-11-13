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
#include <cstring>
#include <cmath>

using namespace std;

int board[9][9];

struct Position {
    int row;
    int col;
    int cell;
};

Position variableToFormula(int variable) {
    Position pos;
    pos.row = variable / 81 + 1;
    pos.cell = variable % 9 == 0 ? 9 : variable % 9;
    pos.col = (variable - pos.cell + 90 - 81 * pos.row) / 9;
    
    return pos;
}

int main(int argc, const char **argv) {
    if (argc != 2) {
        cout << "Error: Diga un nombre de archivo.\n";
        return 1;
    }
    
    ifstream inputfile(argv[1]);
    
    if (!inputfile.is_open()) {
        cout << "Error: El archivo no existe.\n";
        return 1;
    }
   
    while (inputfile.good()) {
        
        string line;
        getline(inputfile, line);
         
        // Read SAT solver results.
        if (line[0] == 's') {
            if (line.compare("s UNSATISFIABLE") == 0) {
                cout << "El tablero no puede resolverse.\n";
                return 0;
            }
            continue;
        }
        
        // If the line doesn't starts with 's', starts with 'v'
        string subline;
        istringstream streamline(line);
        
        while (getline(streamline, subline, ' ')) {
            if (subline.compare("v") == 0)
                continue;
            
            int variable = atoi(subline.c_str());
            Position pos = variableToFormula(abs(variable));
            
            if (variable > 0)
                board[pos.row - 1][pos.col - 1] = pos.cell;
		}
    }
    
    // Print the solution as table
  /*  cout << "-------------------------" << endl;

    for (int i = 0; i< 9 ; ++i) {
        if (i % 3 == 0 && i > 0) {
            cout << "|-----------------------|" <<  endl;
        }
	
        for (int j = 0; j < 9; ++j) {
            if (j % 3 == 0) {
                cout << "| ";
            }
            cout << board[i][j] << " ";
        }
        cout << "|" << endl;

    }
    cout << "-------------------------" << endl;
*/
    //Print the solution as required output
	for (int i = 0; i<9; ++i){
		for (int j = 0; j < 9; ++j){
		 cout<<board[i][j];
		}
	}
	cout << endl;
    inputfile.close();
}
