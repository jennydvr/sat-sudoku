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

using namespace std;

int board[9][9];

struct Position {
    int row;
    int col;
    int cell;
};

Position formulaToVariable(int position) {
    Position pos;
    pos.row = position / 81 + 1;
    pos.col = (position - position % 9 + 90 - 81 * (position / 81 + 1)) / 9;
    pos.cell = position % 9;
    
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
	
        if (line[1] == 's' && line.compare("SATISFIABLE") != 0) {
            cout << "El tablero no puede resolverse.\n";
            return 0;
        }
	else if (line[0] == 's' && line.compare("SATISFIABLE") == 0)
		 continue;
	else if (line[0] == 'v'){  
		
	   string subline;
		istringstream streamline(line);
		while (getline(streamline, subline, ' ')){
		string value;
		istringstream lineString(subline);
		getline(lineString, value, ' ');
		if (value.compare("v") == 0)
		  continue;
		int variable = atoi(value.c_str());
		
		
		Position pos = formulaToVariable(variable);
		if (variable > 0){
		//cout << "var - row - col - value " << variable << " " << pos.row << " " <<
	//	pos.col << " " << pos.cell << endl;
			board[pos.row-1][pos.col-1] = pos.cell;
		}
		}
	}
  
    }
cout << "----------------------" << endl;

  for (int i = 0; i< 9 ; ++i){
	if (i % 3 == 0 && i > 0){
	  cout <<"---------------------|"<<  endl;
	}
	
	for (int j = 0; j < 9; ++j){
	if (j % 3 == 0){
	  cout << "|";
	}
	  cout << board[i][j] << " ";
	}
cout << "|" << endl;

    }
cout << "----------------------" << endl;
    inputfile.close();
}
