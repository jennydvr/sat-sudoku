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
                    formula 
                                //<< ++ln //No hay que imprimir el numero de linea
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
                    formula 
                                //<< ++ln
                            << " -" << formulaToVariable(i, j, d)
                            << " -" << formulaToVariable(k, j, d)
                            << " 0\n";
        }
    }
}

void wawa(int tabRow, int tabCol)
{
    for (int i = tabRow; i < tabRow + 3; i++)
    {
        for (int j = tabCol; j < tabCol + 3; j++)
        {
            for (int x = tabRow; x < tabRow + 3; x++)
            {
                if (i > x)
                    continue;
                
                for (int y = tabCol; y < tabCol + 3; y++)
                {
                    if ((j > y) || (i == x && j == y))
                        continue;

                    for (int d = 1; d < 10; d++)
                    {                    
                        formula 
                                //<< ++ln  //No hay que imprimir el numero de linea                   
                                << " -" << formulaToVariable(i, j, d)
                                << " -" << formulaToVariable(x, y, d)
                                << " 0\n";
                        //cout << "P(i = " << i << ", j = " << j << ", d = " << d << ")    |   P(x = " << x << ", y = " << y << ", d = " << d << ")" <<  endl;
                    }
                }
            }
        }
    }
}

void createSubtFormula() {
    for (int i = 1; i < 10; i+=3)
    {        
        for (int j = 1; j < 10; j+=3)
        {
            wawa(i, j);
        }
    }
    return;
}

void createFileFormula(string line) {
    //ifstream inputfile(filename);
    
    /*if (!inputfile.is_open()) {
        cout << "Error: El archivo no existe.\n";
        exit(0);
    }*/
    
    for (int x = 0; x != '\0'; ++x) {
        //string line;
        //getline(inputfile, line);        
        
        int i = (x+1) / 9;
        int j = (x+1) % 9; 
        
        //for (int j = 0; j != 9; ++j) {
            if (line[x] == '\n')
                continue;
            
            int d = line[x] - 48;   // ascii(1) = 49
            
            if (1 <= d && d <= 9)
                formula 
                                //<< ++ln //No hay que imprimir el numero de linea
                    << " " << formulaToVariable(i + 1, j + 1, d) << " 0\n";
        //}
    }
    //inputfile.close();
}

void core(string s, int fileNum)
{
    ln = 0;
    formula.str("");

    // Start writing the formula
    cout << s.length() << endl;

    createFileFormula(s);
    createCellsFormula();
    createRowsFormula();
    createColumnsFormula();
    createSubtFormula();    


    // Write in a file
    stringstream ss;
    ss << "example" << fileNum << ".txt";
    string sss = ss.str();

    ofstream outputfile((char*)sss.c_str()) ; //(sss);
    outputfile << "p cnf 729 " << ln << endl;
    outputfile << formula.str() << endl;
    outputfile.close();
}



void readInputFile(const char *filename)
{
    ifstream inputfile(filename);
    
    if (!inputfile.is_open()) {
        cout << "Error: El archivo no existe.\n";
        exit(0);
    }

    stringstream zombie;

    //memset(zombie, '\0', sizeof(zombie));
    int index = 0; 

    while (!inputfile.eof())
    {
        string line;

        //getline(inputfile, line);

        inputfile >> line;

        if (line.empty())
            break;

        core(line, index);
        index++;
        continue;

        for (int j = 0; j != 81; ++j) {
            //int d = line[j] - 48;   // ascii(1) = 49            

            zombie << line[j];
            if ((j+1) % 9 == 0)
                zombie << endl;
        }   
        //core(zombie.str());
    }
    inputfile.close();
    //cout << zombie.str() << endl;
    //zombie << endl;
    //cout << zombie.str() << endl;
    
    /*
    for (int i = 0; i != 9; ++i) {
        string line;
        getline(inputfile, line);
        
        for (int j = 0; j != 9; ++j) {
            int d = line[j] - 48;   // ascii(1) = 49
            
            if (1 <= d && d <= 9)
                formula 
                                //<< ++ln //No hay que imprimir el numero de linea
                    << " " << formulaToVariable(i + 1, j + 1, d) << " 0\n";
        }
    }*/
    
    
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cout << "Error: Diga un nombre de archivo.\n";
        return 0;
    }

    readInputFile(argv[1]);
    return 0;   

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
