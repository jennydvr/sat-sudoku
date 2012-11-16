//
//  encoder.cpp
//  sat-solver
//
//  Created by Christian Chomiak on 15/11/12.
//  Copyright (c) 2012 Christian Chomiak. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>

using namespace std;


bool revisateste(string line)
{
    int matrix [9][9]; 

//cout << line << endl;
     for (int x = 0; x != 81; x++) //line.size()
     {     
         int ii = x / 9;
         int jj = (x + 9) % 9;
         
         //cout << "i: " << ii << " | j:" << jj << endl;

         int d = line[x] - 48;   // ascii(1) = 49
         
        //cout << "x: " << line[x] << "| d: " << d << endl;

         if (1 <= d && d <= 9) {
             matrix[ii][jj] = d;        
         }
     }
    
    int sum;    

    //Primer chequeo rapido y barato. Si la suma de los elementos de una fila
    //es distinto a 45, el tablero esta malo. Que sea igual a 45 no garantiza
    //que no hayan elementos repetidos, por lo que se pasa a hacer los chequeo
    //exhaustivo posteriores.
    for (int i = 0; i < 9; ++i)
    {
        sum = 0;
        for (int j = 0; j < 9; ++j)        
            sum += matrix[i][j];

        if (sum != 45)
        {
            cout << "[Q] STAHP! Hay un error en las filas del tablero:\n" << line << endl;
            return false;           
        }
    }

    //Chequeo que no haya repetido en las filas
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)  
        {
            for (int k = j + 1; k < 9; k++)
                if (matrix[i][j] == matrix[i][k])
                {
                    cout << "STAHP! Hay un error en las filas del tablero:\n" << line << endl;
                    return false; 
                }
        }      

    //Chequeo que no haya repetido en las columnas
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)  
        {
            for (int k = j + 1; k < 9; k++)
                if (matrix[j][i] == matrix[k][i])
                {
                    cout << "STAHP! Hay un error en las columnas del tablero:\n" << line << endl;
                    return false; 
                }
        }      

    //Chequeo que no haya repetido en los subtableros
    for (int a = 0; a < 9; a += 3)
        for (int b = 0; b < 9; b += 3)        
            for (int i = a; i < a + 3; ++i)            
                for (int j = b; j < b + 3; ++j)                
                    for (int x = a; x < a + 3; ++x)                              
                        for (int y = b; y < b + 3; ++y)
                        {
                            if (i == x && j == y)
                                continue;

                            if (matrix[i][j] == matrix[x][y])
                            {
                                cout << "STAHP! Hay un error en los subtaleros del tablero:\n" << line << endl;
                                return false; 
                            }
                        }
                    
                
            
        
    return true;
}

void readInputFile(const char *completeFilename) {
    ifstream inputfile(completeFilename);

    bool result = true;
    
    if (!inputfile.is_open()) {
        cout << "Error: El archivo no existe.\n";
        exit(1);
    }
    
    while (!inputfile.eof()) {
        string line;
        getline(inputfile, line);
        
        if (line.empty())
            continue;
        
        if (!isdigit(line[0]))
            continue;

        result &= revisateste(line);
    }
    
    if (result)
        cout << "\nTodas las soluciones son correctas. Yey! :D\n" << endl;

    inputfile.close();
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        cout << "Error: Diga un nombre de archivo.\n";
        return 1;
    }

    // Extract the name of the file
    string filename = argv[1];
    int pos = (int) filename.find(".");
    filename = filename.substr(0, pos);
    
    // Read every instance
    readInputFile(argv[1]);
    
    return 0;
}
