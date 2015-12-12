#ifndef Tree_7
#define Tree_7

#include <iostream>
#include <stack>
using namespace std;
#define HEIGHT 6 		//Height of Board
#define WIDTH 7 		//Width of Board
#define NOSLOT 0 		//Slot of Nothing
#define PLAYER1 1		//The Player1 (AI)
#define PLAYER2 2   	//The Player2

#define MAX  2000000	//For the highest value
#define MIN -2000000	//For the Lowest value




struct node
{
  node *children[WIDTH]; //Array for each children
  short int board[HEIGHT][WIDTH]; 	//Board of the game
  short int depth;					//Depth level of the current node
  int alpha; 		//Alpha value used for ALPHABETA algorithim
  int beta;			//Beta value used for ALPHABETA algorithim
  int minimax_value; //Is the value formed by using heuristic evaluation function.

};   

class tree
{
protected:
	node* root;	//The root node 
	int count_test; //Test count that will be used to increment each time heuristic is called by teriminal node
	stack<node*> DFS_stack; //Is used for the stack to see who the parent of the child is.
public:
	tree();	//Tree constructor for Tree with an empty board
	tree(short int [][WIDTH]); //Tree constructor for tree based on a matrix (Board of game)
	~tree(); //Destructor which will be called at the end
	void deleteTree(); // Deletes the tree 
	void expand();  //Expands the nodes creating children in a depth limited search. Will also use minimax/alphabeta algorithims
					//When the nodes are being created
	void dTraverse(node *P);	//Deallocates all nodes within the tree.
	void initNode(node *P,int,node *Q); //Updates Node Q based on information given by Node P
	void display(node *P); //Displays the board state
	void test(); //Displays the children nodes minimax value
	int checkSlot(node *P,int); //Checks the possible location it will put the next slot into
	bool push(node *P,int); //Pushes slot based on the Node and the player location
	void heuristic(node *P); //Applies the evaulation function within the Node
	void updateHeuristic(node *P); //Calls Heuristic and will update the parent nodes of the values
									//Will also update alphabeta values 
	bool alphabetaCut(node *P); //Prunes the tree when the alphabeta conditions are met to prune
	bool alphabetaUpdate(node *P); //Updates the alphabeta values of the node
	bool checkWin(node *P); //Checks if the following node has won
	int bestChoice(); //Call after calling expand.
	void testHeuristic(); //Is a testing function to see the effeciency of the heuristic based on a custom board state
							//Created from this function.
};

#endif