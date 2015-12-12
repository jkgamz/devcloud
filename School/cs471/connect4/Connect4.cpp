#include <iostream>
#include <cstdlib>
#include "Tree_7.h"
using namespace std;


short int board[HEIGHT][WIDTH]; 
						//If NOSLOT: No player, open space
					 	//If PLAYER1: Player 1 slot
						//If PLAYER2: Player 2 slot
int checkSlot(int); //Checks if a slot is addable to the specified width location. Returns -1 is not addable.
bool push(int, int);//Pushes a token within a slot. Takes in the location and the width location and the PLayer at arguments
void display(); 	//displays the board of the game
bool checkWin(int); //returns true if its a win state for the specified Player
bool checkTie(); //returns true if its a tie. returns false if not.

int main()
{
	for (int i=0;i<HEIGHT;i++) //Initialize to NOSLOT to all spots
	{
		for (int j=0;j<WIDTH;j++)
		{
			board[i][j] = NOSLOT;
		}
	}


	
	int width_location;
	int turn = PLAYER1;
	int player;
	int winner;

	char answer;
	
	system("clear");
	cout<<"//Player VS AI Connect 4//"<<endl;

	cout<<"Do you want to go first? (y/n)"<<endl;
	cin>>answer;
	
	if (answer != 'n' && answer != 'N')
		turn = PLAYER2;
		
	while (true) //The actual game for Player vs AI
	{
		system("clear");
		display();
		
		if (turn == PLAYER1)
		{
			player=PLAYER1;
			tree *AI = new tree(board);
			cout<<"AI is thinking..."<<endl;
			AI->expand();
			system("clear");
			//display();
			//cout<<"AI has made the best choice at location "<<AI->bestChoice()<<endl;
			push(AI->bestChoice(),PLAYER1);
			delete AI;
		}

		else
		{
			player=PLAYER2;
			cout<<"Your turn"<<endl;
		do 
		{
			cout<<"Enter column:";
			cin>>width_location;
			if (!push(width_location,player))
				cout<<"Invalid Location at "<<width_location<<". Please input width_location again"<<endl;
			else 
				break;
		} while(true);
		}

		if (checkWin(player))
		{
			winner = player;
			break;
		}

		else if (checkTie())
		{
			winner = NOSLOT;
			break;
		}


		if (turn == PLAYER1)
			turn = PLAYER2;
		else 
			turn = PLAYER1;
	}
	


	//Indicates the Winner of the game
	if (winner == PLAYER1){
		system("clear");
		display();
		cout<<"You lost... AI is the winner!!!"<<endl;
	}
	else if (winner == PLAYER2)
		cout<<"You Win!!! You are stronger than the computer"<<endl;
	else if (winner == NOSLOT)
		cout<<"Its a TIE!!!"<<endl;

	return 0;
}



int checkSlot(int width_location) 
//Checks if the given slot is pushable and returns the next available height location
//Where a slot can be pushed in. Will return -1 if it can't push in.
{
	//CHECK bottom
	//INPUT as a location of width 
	int available_slot =-1; // Available slot is possible slot players can enter
	if (width_location>=WIDTH || width_location<0)
		return available_slot;
	for (int i=0;i<HEIGHT;i++) //Doesn't check top slot
	{	
		// Checks if the slot is occupied by either players
		if (board[i][width_location] == NOSLOT)
		{
			available_slot=i;
			break; //Leaves the for loop because it has available slot
		}
	}
	return available_slot;
}

bool push(int width_location, int player)
//Pushes a token down a column given a widthlocation and whos player it is
//Will return true if it successfully pushes.
//Will return false if failed to push
{

	int height_location = checkSlot(width_location);
	if (height_location == -1)
	{
		return false;
	}

	board[height_location][width_location] = player;
	return true;
}

void display()
//Displays the game board
{
	cout<<endl;
	cout<<"  0   1   2   3   4   5   6 "<<endl;
	cout<<" ---------------------------"<<endl;
	for (int i=HEIGHT-1;i>=0;i--)
	{
		for (int j=0;j<WIDTH;j++)
		{
			if(board[i][j] == 0)
				cout << "  . ";
			if(board[i][j] == 1)
				cout << "  X ";
			if(board[i][j] == 2)
				cout << "  O ";
		}
		cout<<endl;
		if(i!=0)
			cout<<endl;
	}
	cout<<" ---------------------------"<<endl;
	cout<<endl;
	return;
}

bool checkTie()
//Checks if there is a tie within the game
{
	for (int i=0;i<HEIGHT;i++)
	{
		for (int j=0;j<WIDTH;j++)
		{
			if (board[i][j] == NOSLOT)
				return false;
		}
	}

	return true;

}


bool checkWin(int player)
//Checks who won the game based on the input of which player it is
//Will return true if that player has won
//Will return false if that player has not won
{	
	int count=0;
	for (int i=0;i<HEIGHT;i++) //Checking rows
	{
		for (int j=0;j<WIDTH;j++)
		{
			if (board[i][j] == player)
				count++;
			else 
				count =0;
			if (count==4)
				return true;
		}
		count =0;
	}
	count =0;
	for (int j=0;j<WIDTH;j++) //Checking the column;
	{
		for (int i=0;i<HEIGHT;i++)
		{
			if (board[i][j] == player)
				count++;
			else 
				count =0;
			if (count==4)
				return true;
		}
		count =0;
	}
	count =0;

	int array_i_l2r[7] = {2,1,0,0,0,0};
	int array_j_l2r[7] = {0,0,0,1,2,3};

	int array_i_r2l[7] = {0,0,0,0,1,2};
	int array_j_r2l[7] = {3,4,5,6,6,6};
	

	for (int k=0;k<6;k++) 
	{
		int i_l2r;
		int j_l2r;
		int i_r2l;
		int j_r2l;
		i_l2r=array_i_l2r[k];
		j_l2r=array_j_l2r[k];
		for (;i_l2r<HEIGHT && j_l2r<WIDTH;i_l2r++,j_l2r++) //CONNECT 4 Diagonal bottom left to top right
		// Need to check starting from 2,0;1,0; 0,0; 0,1; 0,2; 0,3;
		{
			if (board[i_l2r][j_l2r] == player)
				count++;
			else 
				count =0;
			if (count==4)
				return true;
		}
	count=0;
		i_r2l=array_i_r2l[k];
		j_r2l=array_j_r2l[k];
		for (;i_r2l<HEIGHT && j_r2l>=0;i_r2l++,j_r2l--) //CONNECT 4 Diagonal bottom right to top left
		// Need to check starting from 2,0;1,0; 0,0; 0,1; 0,2; 0,3;
		{
			if (board[i_r2l][j_r2l] == player)
				count++;
			else 
				count=0;
			if (count==4)
				return true;
		}
		//		cout<<"DID I BREAK HERE?"<<endl;

	count=0;
	}
	return false;
}



//Player vs Player Game
/* 
	while (true)
	{
		if (turn == PLAYER1)
			player=PLAYER1;
		else
			player=PLAYER2;
		cout<<"Player"<<player<<"'s turn"<<endl;
		do 
		{
			cout<<"Enter Width location:";
			cin>>width_location;
			if (!push(width_location,player))
				cout<<"Invalid Location at "<<width_location<<". Please input width_location again"<<endl;
			else 
				break;
		} while(true);

		display();

		if (checkWin(player))
		{
			winner = player;
			break;
		}

		if (turn == PLAYER1)
			turn = PLAYER2;
		else 
			turn = PLAYER1;
	}
*/
