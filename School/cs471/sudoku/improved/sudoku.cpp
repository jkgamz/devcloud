#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

//Struct representing each space on the board
struct space{
	vector<int> available;
	int value;
	bool origLOCK;
};

//Define a board as a 2-dimensional array of spaces
struct board{
	space spaces[9][9];
	bool solved;
};

//Load a board from a file
board loadBoard(string name){

	cout << "Opening puzzle " << name << endl;

	board newBoard; //Board to return
	string newPuzzle; //Puzzle to load into new board
	
	//Open puzzle file
	ifstream inf;
	inf.open(name.data());
	
	//In case the file doesn't exist
	if(!inf){
		cout << "FILE DOES NOT EXIST" << endl;
		exit(1);
	}
	
	//Store puzzle in file in newPuzzle
	inf >> newPuzzle;
	cout << "NewPuzzle: " << newPuzzle << endl;
	
	//Close file
	inf.close();
	
	//Load newPuzzle into newBoard
	int stringPlace=0;
	
	for(int row=0; row<9; row++){
		for(int col=0; col<9; col++){
			newBoard.spaces[row][col].value = (int)newPuzzle[stringPlace] - 48;
			
			//Initialize space as unlocked
			newBoard.spaces[row][col].origLOCK = false;		
	
			if(((int)newPuzzle[stringPlace] - 48) != 0){
				newBoard.spaces[row][col].origLOCK = true;
				//cout << "Value at " << row << " " << col << " is " << (int)newPuzzle[stringPlace] << " LOCKING" << endl;
			}

			stringPlace++;
		}
	}
	
	return newBoard;
	
	
}

//Display a board
void display(board& boardToDisplay){
	
	cout << endl;
	
	for(int row=0; row<9; row++){
		for(int col=0; col<9; col++){
			if(boardToDisplay.spaces[row][col].value == 0)
				cout << " .  ";
			else{
				if(boardToDisplay.spaces[row][col].origLOCK)
					cout << "(" << boardToDisplay.spaces[row][col].value << ") ";
				else
					cout << " " << boardToDisplay.spaces[row][col].value << "  ";
			}
			if((col+1)%3 == 0) cout << "  ";
		}
		cout << endl << endl;
		if ((row+1)%3 == 0) cout << endl << endl;
	}
	return;
}

//Returns used values in the given row for the given board
vector<int> rowValues(int row, board& thisBoard){
	vector<int> values;
	
	for(int col=0; col<9; col++){
		if(thisBoard.spaces[row][col].value != 0)
			values.push_back(thisBoard.spaces[row][col].value);
	}
	
	return values;
}


//Returns used values in a given column for given board
vector<int> colValues(int col, board& thisBoard){
	vector<int> values;
	
	for(int row=0; row<9; row++){
		if(thisBoard.spaces[row][col].value != 0)
			values.push_back(thisBoard.spaces[row][col].value);
	}
	return values;
}

//Returns used values in a given box for a given board
vector<int> boxValues(int row, int col, board thisBoard){
	vector<int> values;
	
	//box 1
	if(row>=0 && row<=2 && col>=0 && col <=2){
		for(int r=0; r<=2; r++){
			for(int c=0; c<=2; c++){
				if(thisBoard.spaces[r][c].value != 0)
					values.push_back(thisBoard.spaces[r][c].value);
			}
		}
	}

	//box 2
	else if(row>=0 && row<=2 && col>=3 && col <=5){
		for(int r=0; r<=2; r++){
			for(int c=3; c<=5; c++){
				if(thisBoard.spaces[r][c].value != 0)
					values.push_back(thisBoard.spaces[r][c].value);
			}
		}
	}
	
	//box 3
	else if(row>=0 && row<=2 && col>=6 && col <=8){
		for(int r=0; r<=2; r++){
			for(int c=6; c<=8; c++){
				if(thisBoard.spaces[r][c].value != 0)
					values.push_back(thisBoard.spaces[r][c].value);
			}
		}
	}
	
	//box 4
	else if(row>=3 && row<=5 && col>=0 && col <=2){
		for(int r=3; r<=5; r++){
			for(int c=0; c<=2; c++){
				if(thisBoard.spaces[r][c].value != 0)
					values.push_back(thisBoard.spaces[r][c].value);
			}
		}
	}
	
	//box 5
	else if(row>=3 && row<=5 && col>=3 && col <=5){
		for(int r=3; r<=5; r++){
			for(int c=3; c<=5; c++){
				if(thisBoard.spaces[r][c].value != 0)
					values.push_back(thisBoard.spaces[r][c].value);
			}
		}
	}
	
	//box 6
	else if(row>=3 && row<=5 && col>=6 && col <=8){
		for(int r=3; r<=5; r++){
			for(int c=6; c<=8; c++){
				if(thisBoard.spaces[r][c].value != 0)
					values.push_back(thisBoard.spaces[r][c].value);
			}
		}
	}
	
	//box 7
	else if(row>=6 && row<=8 && col>=0 && col <=2){
		for(int r=6; r<=8; r++){
			for(int c=0; c<=2; c++){
				if(thisBoard.spaces[r][c].value != 0)
					values.push_back(thisBoard.spaces[r][c].value);
			}
		}
	}
	
	//box 8
	else if(row>=6 && row<=8 && col>=3 && col <=5){
		for(int r=6; r<=8; r++){
			for(int c=3; c<=5; c++){
				if(thisBoard.spaces[r][c].value != 0)
					values.push_back(thisBoard.spaces[r][c].value);
			}
		}
	}
	
	//box 9
	else if(row>=6 && row<=8 && col>=6 && col <=8){
		for(int r=6; r<=8; r++){
			for(int c=6; c<=8; c++){
				if(thisBoard.spaces[r][c].value != 0)
					values.push_back(thisBoard.spaces[r][c].value);
			}
		}
	}
	
	return values;
}


//Updates the available values for each space in the board
void forwardChecking(board& checkThis){
	
	bool rowExist = true;
	
	//Cycle through every space on board
	for(int row=0; row<9; row++){
		vector<int> rowVals = rowValues(row, checkThis); //Contains current row's used values
		
		for(int col=0; col<9; col++){
			vector<int> colVals = colValues(col, checkThis); //Contains current col's used values
			vector<int> boxVals = boxValues(row, col, checkThis); //Contains box's used values
			
			//Clear available values for space
			while(checkThis.spaces[row][col].available.size() > 0){
				checkThis.spaces[row][col].available.erase(checkThis.spaces[row][col].available.begin());
			}
			
			if(rowVals.size()==0){
				rowVals.push_back(0);
				rowExist = false;
			}
				
			//Load row
			for(int i=0; i<rowVals.size(); i++){
				checkThis.spaces[row][col].available.push_back(rowVals[i]);
			}

			
			//Load col
			for(int i=0; i<colVals.size(); i++){
				for(int j=0; j<checkThis.spaces[row][col].available.size(); j++){
					if(colVals[i] == checkThis.spaces[row][col].available[j])
						break;
					if(j == (checkThis.spaces[row][col].available.size() - 1))
						checkThis.spaces[row][col].available.push_back(colVals[i]);
				}
			}
			
			//Load box
			for(int i=0; i<boxVals.size(); i++){
				for(int j=0; j<checkThis.spaces[row][col].available.size(); j++){
					if(boxVals[i] == checkThis.spaces[row][col].available[j])
						break;
					if(j == (checkThis.spaces[row][col].available.size() - 1))
						checkThis.spaces[row][col].available.push_back(boxVals[i]);
				}
			}
			
			if(!rowExist){
				checkThis.spaces[row][col].available.erase(checkThis.spaces[row][col].available.begin());
				rowVals.erase(rowVals.begin());
				rowExist = true;
			}
				
			
			if(checkThis.spaces[row][col].available.size() == 0)
				return;
			
			vector<int> possibles;
			for(int i=1; i<=9; i++){
				possibles.push_back(i);
			}
			
			for(int a=0; a<checkThis.spaces[row][col].available.size(); a++){
				for(int p=0; p<possibles.size(); p++){
					if(possibles[p] == checkThis.spaces[row][col].available[a])
						possibles.erase(possibles.begin() + p);
				}
				
			}
			
			checkThis.spaces[row][col].available.swap(possibles);

			//Debugging couts
			/*
			cout << row << " " << col << ": "; 
			for(int i=0; i<checkThis.spaces[row][col].available.size(); i++){
			  cout << checkThis.spaces[row][col].available[i] << " ";
			}
			if(checkThis.spaces[row][col].origLOCK) cout << "LOCKED";
			cout << endl;
			*/
		}
	}	
}


//Returns true if board is failed -- unsolvable state
bool checkFail(board& checkThis){
	
	//If there are no available values
	for(int row=0; row<9; row++){
		for(int col=0; col<9; col++){
			if(checkThis.spaces[row][col].available.size() != 0)
				return false;
		}
	}
	
	//And there are still 0's
	for(int row=0; row<9; row++){
		for(int col=0; col<9; col++){
			if(checkThis.spaces[row][col].value == 0)
				return true; //Then the attempt has failed
		}
	}
	
	//Otherwise not failed
	return false;
}

bool checkWin(board& checkThis){
	for(int row=0; row<9; row++){
		for(int col=0; col<9; col++){
			if(checkThis.spaces[row][col].value == 0)
				return false;
		}
	}
	
	return true;
}

int recur=0;
//Sudoku Solver
board solve(board solveThis){
	board solution;
	
	cout << "called" << endl;
	
	//Execute forward checking
	forwardChecking(solveThis);
	
	//If not failed, do further evaluation
	if(!checkFail(solveThis)){
		system("clear");
		display(solveThis);		

		//For final interation - flag solved
		if(checkWin(solveThis)){
			solveThis.solved = true;
			return solveThis;
		}
	
		//Choose the space(s) with the least available size and solve that
		
		int smallest=100;//variable for smallest size
		
		//Find smallest nonzero size
		for(int row=0; row<9; row++){
			for(int col=0; col<9; col++){
				if(solveThis.spaces[row][col].available.size() < smallest && solveThis.spaces[row][col].available.size() != 0){
					if(!solveThis.spaces[row][col].origLOCK){
						smallest = solveThis.spaces[row][col].available.size();
					}
				}
			}
		}
		
		cout << "Smallest: " << smallest << endl;
		
		//If there was a nonzero smallest, try using that value and solve from that
		if(smallest!=100){
			for(int row=0; row<9; row++){
				for(int col=0; col<9; col++){
					if(solveThis.spaces[row][col].origLOCK == false && solveThis.spaces[row][col].available.size() == smallest){
						//Try all available numbers for space
						for(int avail=0; avail<solveThis.spaces[row][col].available.size(); avail++){
							//cout << "avail " << avail;
							for(int i=0; i<solveThis.spaces[row][col].available.size(); i++){
								cout << solveThis.spaces[row][col].available[i] << " ";
							}
							cout << endl;
							cout << solveThis.spaces[row][col].value << endl;
							solveThis.spaces[row][col].value = solveThis.spaces[row][col].available[avail];
							cout << solveThis.spaces[row][col].value << endl;
							solveThis.spaces[row][col].origLOCK == true;
							cout << " trying " << solveThis.spaces[row][col].value << " at " << row << " " << col << endl;
							solution = solve(solveThis);
							if(solution.solved)
								return solution;
							solveThis.spaces[row][col].origLOCK == false;
						}
					}
				}
			}	
		}
		
	}//End if
	cout << "This was reached :o" << endl;
}

bool solveNoMCV(board& solveThis, int row, int col){
	forwardChecking(solveThis);
	
	if(row==9)
		return true;
	
	if(solveThis.spaces[row][col].value){
			
		if(col == 8){
			if(solveNoMCV(solveThis, row+1, 0)) return true;
		}
		else{
			if(solveNoMCV(solveThis, row, col+1)) return true;
		}		
		return false;
	}
	
	if (solveThis.spaces[row][col].available.size() == 0){
		return false;
	}
	
	for(int i=0; i<solveThis.spaces[row][col].available.size(); i++){
		solveThis.spaces[row][col].value = solveThis.spaces[row][col].available[i];
		
		if(col == 8){
			if(solveNoMCV(solveThis, row+1, 0)) return true;
		}
		else{
			if(solveNoMCV(solveThis, row, col+1)) return true;
		}		
		solveThis.spaces[row][col].value = 0;
	}
		
}

//Solve Mode
void solver(){
	board puzzle;
	int inRow, inCol, inValue;
	
	system("clear");
	cout << "//Freeplay Mode//" << endl << endl;
	
	string response;
	cout << "Enter puzzle name to open: ";
	cin >> response;
	
	puzzle = loadBoard(response.data());
	
	system("clear");
	display(puzzle);
	
	cout << "Solving..." << endl;
	
	solveNoMCV(puzzle, 0, 0);
	
	display(puzzle);
	
	system("read -p 'Puzzle Solved [Press ENTER]'");
}
//Freeplay Mode
void freeplay(){
	board puzzle;
	int inRow, inCol, inValue;
	
	system("clear");
	cout << "//Freeplay Mode//" << endl << endl;
	
	string response;
	cout << "Enter puzzle name to open: ";
	cin >> response;
	
	puzzle = loadBoard(response.data());
	
	while(1){
		
		if(checkWin(puzzle)){
			cout << "Puzzle solved!!" << endl;
			break;
		}
		
		system("clear");
		display(puzzle);
		
		forwardChecking(puzzle);
		cout << "Enter value (row, column, value): ";
		cin >> inRow >> inCol >> inValue;
		
		if(puzzle.spaces[(inRow-1)][(inCol-1)].origLOCK){
			system("read -p 'Original puzzle value; cannot change [Press ENTER]'");
			continue;
		}
		
		puzzle.spaces[(inRow-1)][(inCol-1)].value = inValue;
	
		for(int i=0; i<puzzle.spaces[(inRow-1)][(inCol-1)].available.size(); i++){
			
			if(puzzle.spaces[(inRow-1)][(inCol-1)].available[i] == inValue)
				break;
			if(i==(puzzle.spaces[(inRow-1)][(inCol-1)].available.size() - 1))
				system("read -p 'WARNING: input value violates a constraint [Press ENTER]'");
				
		}
	}
	
	system("read -p 'Press enter to return to menu...'");
}
//Assist Mode
void assist(){
	board puzzle;
        int inRow, inCol, inValue;

	system("clear");
        cout << "//Freeplay Mode//" << endl << endl;

        string response;
        cout << "Enter puzzle name to open: ";
        cin >> response;

        puzzle = loadBoard(response.data());

        while(1){

                if(checkWin(puzzle)){
                        cout << "Puzzle solved!!" << endl;
                        break;
                }

                system("clear");
                display(puzzle);

                forwardChecking(puzzle);
                cout << "Enter row and column (row, column): ";
                cin >> inRow >> inCol;

		cout << "Domain for " << inRow << " " << inCol << " is [ ";
		for(int i=0; i<puzzle.spaces[(inRow-1)][(inCol-1)].available.size(); i++)
			cout << puzzle.spaces[(inRow-1)][(inCol-1)].available[i] << " ";
		cout << "]" << endl << "Enter value: ";
		cin >> inValue;
		cout << endl;

                if(puzzle.spaces[(inRow-1)][(inCol-1)].origLOCK){
                        system("read -p 'Original puzzle value; cannot change [Press ENTER]'");
                        continue;
                }

                puzzle.spaces[(inRow-1)][(inCol-1)].value = inValue;

                for(int i=0; i<puzzle.spaces[(inRow-1)][(inCol-1)].available.size(); i++){

                        if(puzzle.spaces[(inRow-1)][(inCol-1)].available[i] == inValue)
                                break;
                        if(i==(puzzle.spaces[(inRow-1)][(inCol-1)].available.size() - 1))
                                system("read -p 'WARNING: input value violates a constraint [Press ENTER]'");

                }
        }

        system("read -p 'Press enter to return to menu...'");
}

//Main driver
int main(){
	
	int response;
	
	while(1){
		
		system("clear");
		
		cout << "~~SUDOKU~~" << endl << endl
			 << "Game Modes:" << endl
			 << "(1) Freeplay" << endl
			 << "(2) Assist" << endl
			 << "(3) Solve" << endl
			 << "(0) Exit" << endl << endl
			 << "Enter desired game mode: ";
		
		cin >> response;
		
		switch(response){
			case 1: freeplay(); break;
			case 2: assist(); break;
			case 3: solver(); break;
			case 0: exit(1);
			default: break;
		}
	}
	
	return 0;

}
