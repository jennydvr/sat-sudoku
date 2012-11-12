#include <iostream>
#include <string>
#include <sstream>

int board [9][9];

struct Position{
    int row;
    int col;
    int cell;

    Position(int row, int col, int cell){};

};

Position invert(int position){
  Position pos;
  pos.row= position/81 + 1;
  pos.col = (position - position%9 +90 -81*(position/81 + 1))/9;
  pos.cell = position%9;
}

int main(int argc, const char *argv[]) {
 char* line; 
 ifstream inputfile(argv[1]);
    
    if (!inputfile.is_open()) {
        cout << "Error: El archivo no existe.\n";
        exit(0);
    }
    
    for (int i = 0; i != 9; ++i) {
        getline(inputfile, line);
	// Read SAT solver results.
        
    }
    
    inputfile.close();

} 
