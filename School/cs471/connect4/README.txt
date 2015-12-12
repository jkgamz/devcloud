README

Jacob Gamez & Jupiter Whitworth
Connect4 AI
CS 471
11/2/15


How to compile:
Within a UNIX environment, use "g++ Tree_7.h" then "g++ Tree_7.cpp Connect4.cpp" This will compile the program into "a.o" which will be the executable of the program.

How to run:
You run the program within a UNIX environment and either "./a.out" if you have compiled, or use the precompiled executable call "Connect4_AI.out" You then run "./Connect4_AI.out"

Within Gameplay:

You will be asked to either move first or second. 

Depending on the choices, the AI will make a decision and will approximately take 5-10 seconds (Maybe shorter or longer). Or the player will make a decision.
When the player makes the decision, the user will then input the width_location it would like to place their token. Invalid width_location will cause a retry and will make the player input again.
This switches back and forth until there is a winner or a tie.

Within the board:
1 within the board will indicate the location where the AI's token is located while
2 within the board will indicate the location where the Players Token is located.
0 within the board will indicate the free space, where neither player has moved.




