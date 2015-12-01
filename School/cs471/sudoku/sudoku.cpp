#include <iostream>
#include <vector>
using namespace std;

#define EMPTY 0;

//Struct representing each space on the board
struct space{
	vector<int> available;
	int value;
};

//Define a board as a 2-dimensional array of spaces
struct board{
	space spaces[9][9];
};

//Fill the board
void fill(board boardToFill){
	for(int row=0; row<9; row++){
		for(int col=0; col<9; col++){
			boardToFill.spaces[row][col].value = EMPTY;
		}
	}
	return;
}

//Display a board
void display(board boardToDisplay){
	
	cout << endl;
	
	for(int row=0; row<9; row++){
		for(int col=0; col<9; col++){
			if(boardToDisplay.spaces[row][col].value == EMPTY)
				cout << ". ";
			else
				cout << boardToDisplay.spaces[row][col].value << " ";
			if((col+1)%3 == 0) cout << " ";
		}
		cout << endl;
		if ((row+1)%3 == 0) cout << endl;
	}
	return;
}

//Returns used values in the given row for the given board
vector<int> rowValues(int row, board& thisBoard){
}

//Returns used values in a given column for given board
vector<int> colValues(int col, board& thisBoard){
}

//Returns used values in a given box for a given board
vector<int> boxValues(int box, board& thisBoard){
}

//Updates the available values for each space in the board
board forwardChecking(board checkThis){
	space currSpace;
	
	for(int row=0; row<9; row++){
		vector<int> rowVals = rowValues(row, checkThis); //Contains current row's used values
		
		for(int col=0; col<9; col++){
			vector<int> colVals = colValues(col, checkThis); //Contains current col's used values
			currSpace = checkThis.spaces[row][col];
			
			for(int val=0; val < currSpace.avaailable.size(); val++){
				
			}
		}
	}
			
}

//Returns true if board is failed -- unsolvable state
bool checkFail(board checkThis){
	
}

board solve(board solveThis){
	
	//Execute forward checking
	solveThis = forwardChecking(solveThis);
	
	//If not failed, do further evaluation
	if(!checkFail(solveThis)){
	
		//Choose the space(s) with the least available size and solve that
		
		int smallest=100;//variable for smallest size
		
		//Set smallest to smallest nonzero size
		for(int row=0; row<9; row++){
			for(int col=0; col<9; col++){
				if(solveThis.spaces[row][col].available.size() < smallest && solveThis.spaces[row][col].available.size() != 0)
					smallest = solveThis.spaces[row][col].size();
			}
		}
		
		//If there was a nonzero smallest, try using that value and solve from that
		if(smallest!=100){
			for(int row=0; row<9; row++){
				for(int col=0; col<9; col++){
					if(solveThis.spaces[row][col].available.size() == smallest){
						//Try all available numbers for space
						for(int value=
					}
				}
			}	
		}
		
	}//End if
		//If done, return the board
	
}

//Main driver
int main(){
	board puzzle;
	board solution;
	
	fill(puzzle);
	display(puzzle);

}
