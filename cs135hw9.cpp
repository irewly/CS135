/*
 * Name: Irene Wang, 5005298618, Assignment 9
 * Description: This program for "Battle Royale" mini terminal game. Game 
 * starts with 25 players represented by upper case alphabets randomly 
 * scattered across a grid. The user then press "Enter" to start and continue 
 * the game. With each round, a storm represented by 's' will progress across 
 * the grid towards the center, eliminating any player that it comes across. 
 * The last player standing will be declared the winner (in case of tie, 
 * randomly chosen).
 * Input: User press "Enter" key to start and continue the game rounds
 * Output: Battle Royale terminal game: Game name, randomly generated center 
 * point, specified size grid, specified number of player symbols scattered 
 * across the grid, storm 's' approaching the center one line at a time, round 
 * end message & round count, victory message and winner message
 */

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<cmath>
#include<stdio.h>

using namespace std;

//Important Constants
const int GRIDX = 50; //X-axis Size 
const int GRIDY = 14; //Y-Axis Size
const int PLAYERCNT = 25; //Number of Players Allowed
const int ROUNDCNT = 100; //Maximum Number of Rounds to Play
const bool ALIVE = true; //Player status
const bool DEAD = false; //Player status
const bool SAVELASTROUND = true; //Save last round so it doesn't get autoerased
const int INITSTORMSIZE = GRIDX; //Storm start out on a diameter the size of X grid

//Creating Coordinates
//Used in lieu of "0" to store X coordinate of player in "player" array
const int X = 0; 
//Used in lieu of "1" to store Y coordinate of player in "player" array
const int Y = 1; 
//Array size for 2D "player" array (2 columns)
const int COORDINATE = 2;

int main(){
    
    srand(time(NULL)); //random generation seed
    int x = rand() % 50; //randomly generated x coordinate of center
    int y = rand() % 14; //randomly generated y coordinate of center
    int ascii = 65; //ascii value for first player name 'A'
    int round = 0; //round count
    int s = 0;//used to signal storm to approach center
    int playerAlive = PLAYERCNT; //initial number of players that are alive
    int playerDead = 0; //number of players that are dead
    
    //arrays
    char grid[100][100]; //array used for generating grid
    int player[PLAYERCNT][COORDINATE]; //array storing player coordinates
    bool playerStatus[PLAYERCNT]; //array storing player status (ALIVE/DEAD)
    char survivor[PLAYERCNT]; //array storing names of players that are alive

    //Initialize grid with blanks ' '
    for(int i = 0; i < GRIDY; i++){
        for(int j = 0; j < GRIDX; j++){
            grid[i][j] = ' ';
        }
    }
    //Initialize all player status to ALIVE
    for(int i = 0; i < PLAYERCNT; i++){
        playerStatus[i] = ALIVE;
    }
    //Initialize player coordinate assignment 
    for(int i = 0; i < PLAYERCNT; i++){
        char playerName = ascii;
        //do while loop checks to see if randomly generated spot is avaiable
        //(not taken by a previous player)
        do{
            player[i][X] = rand() % 50;
            player[i][Y] = rand() % 14;
        }while(grid[player[i][Y]][player[i][X]] != ' '); 
        //playerName will be displayed on the grid in the random spot
        grid[player[i][Y]][player[i][X]] = playerName;
        //ascii value increase to prepare next player name (alphabet)
        ascii++;
    } 

    //Main game for loop
    for(int i = 0; i < ROUNDCNT; i++){

        char c; //player identifier 
        //cout greeting message and randomly generated center coordinates
        cout << "Center: (" << x << "," << y << ")" << endl;
        cout << "Wang Battle Royale!" << endl;
        //cout clean grid with randomly scattered players (1st round only)
        if(i == 0){    
            for(int i = 0; i < GRIDY; i++){
                for(int j = 0; j < GRIDX; j++){
                    cout << grid[i][j];
                }
                cout << endl;
            }
        }
        //after 1st round, storm will be integrated onto the grid
        else{
            //Storm generating for loop. "s" is used to signal storm to either increase
            //or decrease by one unit on either x or y axis to close in on the center.
            for(int i = 0; i < GRIDY; i++){
                //Storm approaching from left
                if((x - INITSTORMSIZE + s) < x && (x - INITSTORMSIZE + s) >= 0){
                    grid[i][x - INITSTORMSIZE + s] = 's';
                }   
                //Storm approaching from right
                if((INITSTORMSIZE + x - s) > x){
                    grid[i][INITSTORMSIZE + x - s] = 's';
                }
                for(int j = 0; j < GRIDX; j++){
                    //Storm approaching from top
                    if((y - INITSTORMSIZE + s) < y && (y - INITSTORMSIZE + s) >= 0){
                        grid[y - INITSTORMSIZE + s][j] = 's';
                    }
                    //Storm approaching from bottom
                    if((y + INITSTORMSIZE - s) > y){
                        grid[y + INITSTORMSIZE - s][j] = 's';
                    }
                    cout << grid[i][j];
                }
                cout << endl;
            }
            s++;
        }
        
        //for loop for keeping track of player status in survivor array
        
        //"survivor" stores the player identifier character 'c' if the player is alive
        //and stores a blank ' ' if the player is dead
        for(int i = 0; i < PLAYERCNT; i++){
            if(playerStatus[i] == ALIVE){
                c = i + 65;
                survivor[i] = c;
            }
            else{
                survivor[i] = ' ';
            }
        }

        //for loop for keeping track of player status 
        
        /* "playerStatus" updated to DEAD if 's' (storm) have taken over the player's
         * spot on the grid
         * "playerDead" count increase by one each time new DEAD is updated
         * "playerAlive" count calculated by subtracting number of dead players 
         * (playerDead) from total number of players (PLAYERCNT)
         */
        for(int i = 0; i < PLAYERCNT; i++){
            if(playerStatus[i] == ALIVE){
                if(grid[player[i][Y]][player[i][X]] == 's'){
                    playerStatus[i] = DEAD;
                    playerDead ++;
                    playerAlive = PLAYERCNT - playerDead;
                }
            }
            if(playerStatus[i] == ALIVE){
                c = i + 65;
            }
        }

        //round count increase by 1 each time
        round ++;
        
        //cout round end message, prompt user to press enter to continue
        cout << "Round " << round << " Complete. Press Enter To Continue ";
        
        //if only 1 player is left at this point, cout victory message and end game 
        if(playerAlive == 1){
            cout << "\nVictory Royale!" << endl;
            cout << "Player '" << c << "' wins!"<< endl;
            cout << "Game Over!" << endl;
            return 0;
        }
        
        /* If there are no players left (0), it means that multiple have died at the
         * same time in the previous round (tie). In this case, randomly generated
         * integer k (PLAYERCNT range) will be used to check and see if the 
         * corresponding spot in array "survivor" contains a ' ' (dead). If not
         * that means it has randomly chosen one of the survivors to be the winner.
         * cout alternate victory message.
         */ 
        if(playerAlive == 0){
            cout << "\nVictory Royale!" << endl;
            int k = rand() % PLAYERCNT;
            while(survivor[k] == ' '){
                k = rand() % PLAYERCNT;
            }
            cout << "Player '" << survivor[k] << "' nearly took the L, but won!";
            cout << endl;
            cout << "Game Over!" << endl;
            return 0;
        }

        //If user press any key other than enter, program terminates 
        if(cin.get() != '\n'){
            cout << "Error! Only Press Enter." << endl;
            return 0;
        }

        //If user press enter, program continues by clearing the screen and back to 
        //top of loop
        else{
            system("clear");
        }

    }

    return 0;
}

