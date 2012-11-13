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

// Current solved-instance
int current = 0;

// Name of file being solved
string filename;

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
                    formula << "-" << formulaToVariable(i, j, d)
                    << " -" << formulaToVariable(i, k, d)
                    << " 0\n";
                    ++ln;
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
                for (int k = i + 1; k < 10; ++k) {
                    formula << "-" << formulaToVariable(i, j, d)
                    << " -" << formulaToVariable(k, j, d)
                    << " 0\n";
                    ++ln;
                }
        }
    }
}

void subTabAux(int tabRow, int tabCol)
{
    for (int i = tabRow; i < tabRow + 3; ++i)
    {
        for (int j = tabCol; j < tabCol + 3; ++j)
        {
            for (int x = tabRow; x < tabRow + 3; ++x)
            {
                if (i > x)
                    continue;
                
                for (int y = tabCol; y < tabCol + 3; ++y)
                {
                    if ((j > y) || (i == x && j == y))
                        continue;
                    
                    for (int d = 1; d < 10; ++d)
                    {
                        formula << "-" << formulaToVariable(i, j, d)
                        << " -" << formulaToVariable(x, y, d)
                        << " 0\n";
                        ++ln;
                    }
                }
            }
        }
    }
}

void createSubtFormula() {
    for (int i = 1; i < 10; i += 3)
        for (int j = 1; j < 10; j += 3)
            subTabAux(i, j);
}

void createInstanceFormula(string line) {
    /*
     for (int x = 0; x != '\0'; ++x) {
     
     int i = (x+1) / 9;
     int j = (x+1) % 9;
     
     for (int j = 0; j != 9; ++j) {
     if (line[x] == '\n')
     break;
     
     int d = line[x] - 48;   // ascii(1) = 49
     
     if (1 <= d && d <= 9){
     formula << formulaToVariable(i + 1, j + 1, d) << " 0\n";
     ++ln;
     }
     }
     }
     */
}

void createFormula(string line) {
    // Clear variables
    ln = 0;
    formula.str("");
    
    // Create the formula
    createInstanceFormula(line);
    createCellsFormula();
    createRowsFormula();
    createColumnsFormula();
    createSubtFormula();
    
    // Create the filename
    stringstream name;
    name << filename << current << ".cnf";
    
    // Write all
    ofstream outputfile(name.str());
    outputfile << "p cnf 729 " << ln << endl;
    outputfile << formula.str() << endl;
    outputfile.close();
}

void readInputFile(const char *completeFilename) {
    ifstream inputfile(completeFilename);
    
    if (!inputfile.is_open()) {
        cout << "Error: El archivo no existe.\n";
        exit(1);
    }
    
    while (!inputfile.eof()) {
        string line;
        getline(inputfile, line);
        
        if (line.empty())
            break;
        
        // Encode this instance
        createFormula(line);
        ++current;
    }
    
    inputfile.close();
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cout << "Error: Diga un nombre de archivo.\n";
        return 1;
    }
    
    // Extract the name of the file
    filename = argv[1];
    int pos = (int) filename.find(".");
    filename = filename.substr(0, pos);
    
    // Read every instance
    readInputFile(argv[1]);
    
    return 0;
}
