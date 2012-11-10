//
//  main.cpp
//  sat-solver
//
//  Created by Jenny Valdez on 10/11/12.
//  Copyright (c) 2012 Jenny Valdez. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

template <class T>
bool from_string(T& t,
                 const std::string& s,
                 std::ios_base& (*f)(std::ios_base&))
{
    istringstream iss(s);
    return !(iss >> f >> t).fail();
}

int formulaToVariable(int i, int j, int d) {
    return 81 * i + 9 * j + d - 72;
}

void createCellsFormula() {
    
}

void createRowsFormula() {
    
}

void createColumnsFormula() {
    
}

void createSubtFormula() {
    
}

void createFileFormula(string filename) {
    ifstream file(filename);
    
    if (!file.is_open()) {
        cout << "Error: El archivo no existe.\n";
        exit(0);
    }
    
    while (file.good()) {
        string line;
        getline(file, line);
        
        // Formula aca
    }
    
    file.close();
}

int main(int argc, const char *argv[]) {
    
    if (argc != 2) {
        cout << "Error: Diga un nombre de archivo.\n";
        return 0;
    }
    
    createFileFormula(argv[1]);
    
    return 0;
}
