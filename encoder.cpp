//
//  encoder.cpp
//  sat-solver
//
//  Created by Jenny Valdez on 10/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;

// Line number - for the output file
int ln = 0;

// Output string
stringstream formula;

int formulaToVariable(int i, int j, int d) {
    return (i - 1) * 81 + (j - 1) * 9 + d;
}

void createCellsFormula() {
    
}

void createRowsFormula() {
    // Fixed row number
    for (int i = 1; i < 10; ++i) {
        // Fixed cell value
        for (int d = 1; d < 10; ++d) {
            // !Pijd v !Pikd
            for (int j = 1; j < 10; ++j) {
                for (int k = j+1; k < 10; ++k) {
                    formula << ++ln
                            << " -" << formulaToVariable(i, j, d)
                            << " -" << formulaToVariable(i, k, d)
                            << " 0\n";
                }
            }
        }
    }
}

void createColumnsFormula() {
    // Fixed column number
    for (int j = 1; j != 10; ++j) {
        // Fixed number
        for (int d = 1; d != 10; ++d) {
            // !Pijd v !Pkjd  -  just variate the row
            for (int i = 1; i != 10; ++i)
                for (int k = i + 1; k < 10; ++k)
                    formula << ++ln
                            << " -" << formulaToVariable(i, j, d)
                            << " -" << formulaToVariable(k, j, d)
                            << " 0\n";
        }
    }
}

void createSubtFormula() {
    
}

void createFileFormula(const char *filename) {
    ifstream inputfile(filename);
    
    if (!inputfile.is_open()) {
        cout << "Error: El archivo no existe.\n";
        exit(0);
    }
    
    for (int i = 0; i != 9; ++i) {
        string line;
        getline(inputfile, line);
        
        for (int j = 0; j != 9; ++j) {
            int d = line[j] - 48;   // ascii(1) = 49
            
            if (1 <= d && d <= 9)
                formula << ++ln << " " << formulaToVariable(i + 1, j + 1, d) << " 0\n";
        }
    }
    
    inputfile.close();
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cout << "Error: Diga un nombre de archivo.\n";
        return 0;
    }
    
    // Start writing the formula
    createFileFormula(argv[1]);
    createCellsFormula();
    createRowsFormula();
    createColumnsFormula();
    createSubtFormula();
    
    // Write in a file
    ofstream outputfile("example.txt");
    outputfile << "p cnf 729 " << ln << endl;
    outputfile << formula.str() << endl;
    outputfile.close();
    
    return 0;
}
