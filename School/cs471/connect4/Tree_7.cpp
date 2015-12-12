#include "Tree_7.h"
#include <cstdlib>
using namespace std;

#define MULTIPLIER 6
#define DEPTHLIMIT 9
tree::tree()
{
	root=new node;
	for (int i=0;i<HEIGHT;i++) //Initialize to NOSLOT to all spots
	{
		for (int j=0;j<WIDTH;j++)
		{
			root->board[i][j] = NOSLOT;
		}
	}
	for (int i=0;i<WIDTH;i++)
	{
		root->children[i]=NULL;
	}
	root->minimax_value=MIN;
	root->depth=0;
	root->alpha=MIN;
	root->beta=MAX;
	count_test=0;
}

tree::tree(short int board[][WIDTH])
{
	root=new node;
	for (int i=0;i<HEIGHT;i++) //Initialize to NOSLOT to all spots
	{
		for (int j=0;j<WIDTH;j++)
		{
			root->board[i][j] = board[i][j];
		}
	}
	for (int i=0;i<WIDTH;i++)
	{
		root->children[i]=NULL;
	}
	root->minimax_value=MIN;
	root->depth=0;
	root->alpha=MIN;
	root->beta=MAX;
	count_test=0;
}


void tree::expand()
{

	int temp;
	//cout<<"Called Expand"<<endl;
	node *P = root; //Creates a pointer called P and P is now pointed at Root
	node *Q;
	node temp_top;
	int temp_heuristic=0;
	//Visit Node
	//Make P the value of the next child that has not been visited
	while (true) //Does until it breaks out.
	{
	//	cout<<endl;
	//	display(P);
	//	cout<<"alpha of P:"<<P->alpha<<endl;
	//	cout<<"beta of  P:"<<P->beta<<endl;
	//	cout<<"value of P:"<<P->minimax_value<<endl;
		//cin>>temp;
	//	cout<<"Top of While LOOP"<<endl;
	//	cout<<"This is the address of root "<<root<<endl;
	//	cout<<"This is the address of what P is pointed to "<<P<<endl;
		//cin>>temp;
	//Do heurisitic on this node only if it hasnt had a heuristic done

	if (checkWin(P)) //When its the win state
	{
	//	cout<<"WIN STATE"<<endl;
	//	cout<<"Terminal NODE"<<endl;
		updateHeuristic(P);
		if (!DFS_stack.empty())
		{
			P=(DFS_stack.top());
			DFS_stack.pop();
		}	
		else 
		{
			break;
		}
	}


	else if (alphabetaCut(P))//When its Cuttable
	{
	//	cout<<"ALPHABETA CUT HAPPENING"<<endl;
		updateHeuristic(P);//Updates the value of the P and carry over the value to parent node if it meets the right condition
		if (!DFS_stack.empty())
		{
			P=(DFS_stack.top());
			DFS_stack.pop();
		}	
		else 
		{
			break;
		}
	}
	
	else if (P->depth < DEPTHLIMIT) //Does if the current depth is larger
	{
		int count=0;
		for (int i=0;i<WIDTH;i++) //Checks all the children left to right until it can find one that hasnt been added or can be added
		{
			if (P->children[i] == NULL && (checkSlot(P,i) != -1))
			{
			//	cout<<"Pushes onto Stack"<<endl;
				DFS_stack.push(P); //Push P onto the stack.
			//	cout<<"Created Child for"<<i<<endl;
				Q=new node;
				initNode(P,i,Q);//Initializes node Q gives default values
				P->children[i]=Q; //Makes the child of P equal to Q.
				P=Q;		//Makes The child the new P 
				break;
			}
			else 
			{
			//	cout<<"Couldnt add child "<<i<<endl;
				count++;
			}
		}

		if (count==WIDTH) //If it can't add any nodes to its children then
		{
			//cout<<"Cant add any nodes to the node"<<endl;
			updateHeuristic(P); //Carrys over heurstics to the parent
			count=0;
			if (!DFS_stack.empty())
			{
			//cout<<"Popping from Stack"<<endl;
			P=(DFS_stack.top());
			DFS_stack.pop();
			}
			else 
			{
				break; 
			}
		}
		count =0;
	}	
	else //When its reached the depth limit then
	{
		updateHeuristic(P);//Updates the value of the P and carry over the value to parent node if it meets the right condition
		//cout<<"Reached Depth Limit:"<<endl;

		if (!DFS_stack.empty())
		{
	//		cout<<"Popping from Stack"<<endl;
			P=(DFS_stack.top());
	//		cout<<"This is the address of P "<<P<<endl;
			DFS_stack.pop();
		}	
		else 
		{
	//		cout<<"Exiting While Loop"<<endl;
			break;
		}
	}		
	}
}


tree::~tree()
{
	dTraverse(root);
	cout<<"deleted tree"<<endl;
}


	
void tree::deleteTree()
{	
	node *P = root;
	node *Q;
	root =NULL;
	for (int i=0;i<WIDTH;i++)
	{
		Q=P->children[i];
		if (Q!=NULL) //While its pointed to something
		{
			delete Q;
			Q=NULL;
			cout<<"Deleted Child "<<i<<" of root"<<endl;
		}

	}

	delete P;
	cout<<"deleted root"<<endl;
}


void tree::dTraverse(node *P)
{   

  if (P != NULL) 
    {
      dTraverse(P->children[0]);
      dTraverse(P->children[1]);
      dTraverse(P->children[2]);
      dTraverse(P->children[3]);
      dTraverse(P->children[4]);
      dTraverse(P->children[5]);
      dTraverse(P->children[6]);
      
      //cout<<"Deleted node "<<P<<endl;
      delete P;                  // deletes V
    }
}



void tree::initNode(node *P,int x,node *Q) //Initializes Node Q using information from node P;
{
  	int value=0;
  	

  	for (int i=0;i<HEIGHT;i++)
  	{
  		for (int j=0;j<WIDTH;j++)
  			Q->board[i][j] = P->board[i][j];
  	}

  	Q->depth=P->depth +1;
  	Q->alpha=P->alpha;
  	Q->beta=P->beta;
  	if (!push(Q,x)) // When its unpushable
  		{
  			cout<<"IMPOSSIBLE ERROR OCCURED";
  			exit(1);
  		}

  	if (Q->depth%2 ==0) //Its on the maximum level, where the minimum value is chosen so to before its actual heuristics is looked at initialize to MAX
  		Q->minimax_value=MIN;
  	else
  		Q->minimax_value=MAX; //Its on the minimum level, where the max value is chosen for the parent, so before its actual heuristics is initialize set to MIN


 	for (int i=0;i<WIDTH;i++)
 		Q->children[i]=NULL;
}


void tree::display(node *P)
{
	cout<<endl;
	for (int i=HEIGHT-1;i>=0;i--)
	{
		for (int j=0;j<WIDTH;j++)
		{
				cout<<P->board[i][j];
				cout<<" ";
		}
		cout<<endl;
	}

}

void tree::test()
{
	cout<<root->minimax_value<<endl;
	cout<<endl;
	for (int i=0;i<WIDTH;i++)
	{
		if (root->children[i] !=NULL)
		cout<<root->children[i]->minimax_value<<endl;
	}
}


int tree::checkSlot(node *P, int width_location)
{
	//CHECK bottom
	//INPUT as a location of width 
	int available_slot =-1; // Available slot is possible slot players can enter
							// -1 slot indicates no possible slot to enter.
	if (width_location>=WIDTH || width_location<0)
		return available_slot;
	for (int i=0;i<HEIGHT;i++) //Doesn't check top slot
	{	
		// Checks if the slot is occupied by either players
		if (P->board[i][width_location] == NOSLOT)
		{
			available_slot=i;
			break; //Leaves the for loop because it has available slot
		}
	}
	return available_slot;

}

bool tree::push(node *P,int width_location) //Pushes onto the board of whatever board
{
	int depth;
	short int turn;
	int height_location = checkSlot(P, width_location);
	if (height_location ==-1)
		return false;


	if (P->depth%2 == 1)
		turn = PLAYER1; // ASSUMING PLAYER 1 is AI
	else
		turn = PLAYER2; // ASSUMING PLAYER 2 is HUMAN
	P->board[height_location][width_location] = turn;
	return true;
}

void tree::updateHeuristic(node *P) // SHOULD BE CALLED MINIMAX!!!
{
	node *Q; //WIll be used to hold the parent of P

	if (P->depth == DEPTHLIMIT || checkWin(P)) //When P is the bottom Node
	{
		//cout<<count_test;
		//cout<<"Hit the heuristic function"<<endl;
		heuristic(P); //Updates the heuristic value of P
		//cout<<"Minimax value "<<P->minimax_value<<endl;
		alphabetaUpdate(P);// Fails to update

	}

	if (!DFS_stack.empty()) // When the stack is not empty 
	{
		Q=(DFS_stack.top()); // Q is the parent
	}
	else if (alphabetaCut(P))
		return;

	else 
		return; //Will usually be the root who will return and will be the only case when it wont update the heuristic

	if (P->depth%2 ==0) //When the depth is at the Max level, will have to return the Minimum to the Min Level
		{
			if (P->minimax_value <= Q->minimax_value)
			{
				Q->minimax_value=P->minimax_value; //Makes the Parent node contain the heuristic of child node
				alphabetaUpdate(Q);
			}
		}
	else //When the depth is at the Min Level, will have to return the Maximum to the Max Level
		{
			if (P->minimax_value >= Q->minimax_value) // When the child Heurisitic is greater than the parent node.
				{
				Q->minimax_value=P->minimax_value; //Makes the Parent node contain the heuristic of child node
				alphabetaUpdate(Q);
			}
		}

}

void tree::heuristic(node *P)
{	
	
	/*
	P->minimax_value = count_test;
	
	*/
	//Variables
	count_test++;
	int p1Count=0;
	int p2Count=0;
	
	//////For each player://////
	for(int currPlayer=PLAYER1; currPlayer<3 ; currPlayer++)
	{
		//////Add consecutives for rows//////
		int count=0;
		int rowCount=0;

		for (int i=0;i<HEIGHT;i++) //Cycle through all cols of each row
		{
			for (int j=0;j<WIDTH;j++)
			{
				//Count consecutives for row
				if (P->board[i][j] == currPlayer){ 
					count++;
				}
				else 
					count =0;
				
				//Update row count and apply multiplier if consecutive of 3 is found.
				if (count==2)
					rowCount+=2;
				else if (count==3){
					rowCount-=2;
					rowCount+=MULTIPLIER*3;
				}
				else if (count==4){
					rowCount-=MULTIPLIER*3;
					rowCount+=MULTIPLIER*50;
				}

			}
			
			//Update total player scores
		//	cout<<"Current Player is"<<currPlayer<<endl;
			if (currPlayer==PLAYER1)
				p1Count+=rowCount;
			else if (currPlayer==PLAYER2)
				p2Count+=rowCount;	
			rowCount=0;
		}
		//cout<<"ROW:"<<endl;
		//cout<<"DISPLAYING: P1COUNT"<<p1Count<<endl;
		//cout<<"DISPLAYING: P2COUNT"<<p2Count<<endl;
		//////Add consecutives for columns//////
		count=0;
		int colCount=0;

		for (int j=0;j<WIDTH;j++) //Cycle through all the rows of each col
		{
			for (int i=0;i<HEIGHT;i++)
			{
				//Count consecutives for column
				if (P->board[i][j] == currPlayer)
					count++;
				else 
					count =0;

				//Update column count and apply multiplier if consecutive of 3 is found.
				if (count==2)
					colCount+=2;
				else if (count==3){
					colCount-=2;
					colCount+=MULTIPLIER*3;
				}
				else if (count==4){
					colCount-=MULTIPLIER*3;
					colCount+=MULTIPLIER*50;
				}
				
			}
			
			//Update total player scores
			if (currPlayer==PLAYER1)
				p1Count+=colCount;
			else if (currPlayer==PLAYER2)
				p2Count+=colCount;	
			colCount=0;
		}

		//cout<<"COLUMN:"<<endl;
		//cout<<"DISPLAYING: P1COUNT"<<p1Count<<endl;
		//cout<<"DISPLAYING: P2COUNT"<<p2Count<<endl;

		//////Add consecutives for diagonals//////
		count=0;
		int diagCount=0;

		//Define arrays for analysis ranges
		int array_i_l2r[7] = {2,1,0,0,0,0};
		int array_j_l2r[7] = {0,0,0,1,2,3};

		int array_i_r2l[7] = {0,0,0,0,1,2};
		int array_j_r2l[7] = {3,4,5,6,6,6};

		for (int k=0;k<6;k++) 
		{
			count=0;
			int i_l2r;
			int j_l2r;
			i_l2r=array_i_l2r[k];
			j_l2r=array_j_l2r[k];

			//CONNECT 4 Diagonal bottom left to top right
			// Need to check starting from 2,0;1,0; 0,0; 0,1; 0,2; 0,3;
			// JG: We only care about the diags that can be won, so only these diags are counted for heuristic
			for (;i_l2r<HEIGHT && j_l2r<WIDTH;i_l2r++,j_l2r++) 
			{
				//Count consecutives for diagonal
				if (P->board[i_l2r][j_l2r] == currPlayer)
					count++;
				else 
					count=0;

				//Update diagonal count and apply multiplier if consecutive of 3 is found.
				if (count==2)
					diagCount+=2;
				else if (count==3){
					diagCount-=2;
					diagCount+=MULTIPLIER*3;
				}
				else if (count==4){
					diagCount-=MULTIPLIER*3;
					diagCount+=MULTIPLIER*50;
				}
				//cout<<"Diagonal Count for L2R"<<endl;
				//cout<<"Location "<<i_l2r<<" "<<j_l2r<<endl;
				//cout<<diagCount<<endl;
			}

			//Update player totals
			if (currPlayer==PLAYER1)
				p1Count+=diagCount;
			else if (currPlayer==PLAYER2)
				p2Count+=diagCount;	
			diagCount=0;
			//cout<<"Diag LEFT:"<<endl;
			//cout<<"DISPLAYING: P1COUNT"<<p1Count<<endl;
			//cout<<"DISPLAYING: P2COUNT"<<p2Count<<endl;
		}

		for (int k=0;k<6;k++) 
		{
			count=0;
			int i_r2l;
			int j_r2l;

			i_r2l=array_i_r2l[k];
			j_r2l=array_j_r2l[k];

			//CONNECT 4 Diagonal bottom right to top left
			// Need to check starting from 2,0;1,0; 0,0; 0,1; 0,2; 0,3;
			// JG: We only care about the diags that can be won, so only these diags are counted for heuristic
			for (;i_r2l<HEIGHT && j_r2l>=0;i_r2l++,j_r2l--) 
			{
				//Count consecutives for diagonal
				if (P->board[i_r2l][j_r2l] == currPlayer)
					count++;
				else 
					count=0;
				
				//Update diagonal count and apply multiplier if consecutive of 3 is found.
				if (count==2)
					diagCount+=2;
				else if (count==3){
					diagCount-=2;
					diagCount+=MULTIPLIER*3;
				}
				else if (count==4){
					diagCount-=MULTIPLIER*3;
					diagCount+=MULTIPLIER*50;
				}
				//cout<<"Diagonal Count for R2L"<<endl;
				//cout<<"Location "<<i_r2l<<" "<<j_r2l<<endl;
				//cout<<diagCount<<endl;
			}
			

			//Update player totals
			if (currPlayer==PLAYER1)
				p1Count+=diagCount;
			else if (currPlayer==PLAYER2)				
				p2Count+=diagCount;
			diagCount=0;
			//cout<<"Diag RIGHT:"<<endl;
			//cout<<"DISPLAYING: P1COUNT"<<p1Count<<endl;
			//cout<<"DISPLAYING: P2COUNT"<<p2Count<<endl;
		}
	}
		//////Subtract opposing player's number from player's number and return//////
		P->minimax_value= (DEPTHLIMIT/P->depth)*(p1Count - p2Count);
		
		//display(P);
		//cout<<"DISPLAYING: P1COUNT"<<p1Count<<endl;
		//cout<<"DISPLAYING: P2COUNT"<<p2Count<<endl;




}


bool tree::alphabetaUpdate(node *P)//Changes the values of alpha and beta whether they are a max or a min
{
	if (P->depth%2 ==0)//MAX NODE: Updates alpha 
	{
		if (P->minimax_value > P->alpha)
		{
			P->alpha = P->minimax_value;
			return true;
		}
			return false;
	}

	else //MIN NODE: Updates beta
	{
		if (P->minimax_value < P->beta)
		{
			P->beta = P->minimax_value;
			return true;
		}
			return false;
	}
}

bool tree::alphabetaCut(node *P)
{
	if (P->depth%2 ==0) // When its the max node
	{
		if (P->minimax_value >= P->beta && P->minimax_value != MIN)
			return true;
	}

	else //When its a min node
	{
		if (P->minimax_value <= P->alpha && P->minimax_value !=MAX)
			return true;
	}
	return false; //False when there is no cut

}



bool tree::checkWin(node *P)
{	
	int turn;
	if (P->depth%2 == 1)
		turn = PLAYER1; // ASSUMING PLAYER 1 is AIs
	else
		turn = PLAYER2; // ASSUMING PLAYER 2 is HUMAN
	int player = turn;

	int count=0;
	for (int i=0;i<HEIGHT;i++) //Checking rows
	{
		for (int j=0;j<WIDTH;j++)
		{
			if (P->board[i][j] == player)
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
			if (P->board[i][j] == player)
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
			if (P->board[i_l2r][j_l2r] == player)
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
			if (P->board[i_r2l][j_r2l] == player)
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

int tree::bestChoice()
{
	for (int i=0;i<WIDTH;i++)
	{
		if (root->children[i] !=NULL)
		{
			if (root->minimax_value == root->children[i]->minimax_value)
			{
				return i;
			}
		}
	}

}

void tree::testHeuristic()
{
	cout<<"TESTING HEURISTIC"<<endl;
	node *P;
	P = new node;
	for (int i=0;i<HEIGHT;i++) //Initialize to NOSLOT to all spots
	{
		for (int j=0;j<WIDTH;j++)
		{
			P->board[i][j] = NOSLOT;
		}
	}

	bool answer;
	int h;
	int w;
	int player;
	do 
	{
	cout<<"Enter the Height:";
	cin>>h;
	cout<<"Enter the Width:";
	cin>>w;
	cout<<"Enter the player:";
	cin>>player;
	if (h>HEIGHT || h<0)
		cout<<"Error Do over"<<endl;
	else if (w>WIDTH || w<0)
		cout<<"Error Do Over"<<endl;
	else
		P->board[h][w] =player;

	display(P);
	cout<<"Do you want to know the heuristic of this?"<<endl;
	cin>> answer;
	if (answer)
	{
		heuristic(P);
		cout<<"Heuristic of this is "<<P->minimax_value<<endl;
	}
	
	cout<<"Do you want to continue?"<<endl;
	cin>>answer;
	if (!answer)
	{
		break;
	}
	} while(true);

}

