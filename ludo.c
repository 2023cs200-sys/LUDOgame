#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gamelogic.c"


int main(){
    srand(time(NULL));
    //roll_dice();
    rollDice();
    playerOrder();
    initPlayers();
    int game_over = 0;


    switch(maxIndex){
        case 0:
            while (!game_over) {
                static int i = 0;
                i += 1;
                printf("\n=============================== round %d!!========\n",i);
                mysterycells();
                game_over = red();
                if (game_over) break;
                game_over = green();
                if (game_over) break;
                game_over = yellow();
                if (game_over) break;
                game_over = blue();
                       
            }
            break;
        case 1:
            while (!game_over) {
                static int i = 0;
                i += 1;
                printf("\n=============================== round %d!!========\n",i); 
                mysterycells();
                game_over = green();
                if (game_over) break;
                game_over = yellow();
                if (game_over) break;
                game_over = blue();
                if (game_over) break;
                game_over = red();
                        
            }
            break;
        case 2:
            while (!game_over) {
                static int i = 0;
                i += 1;
                printf("\n=============================== round %d!!========\n",i); 
                mysterycells();
                game_over = yellow();
                if (game_over) break;
                game_over = blue();
                if (game_over) break;
                game_over = red();
                if (game_over) break;
                game_over = green();
                        
            }
            break;
        case 3:
            while (!game_over) {
                static int i = 0;
                i += 1;
                printf("\n=============================== round %d!!========\n",i); 
                mysterycells();
                game_over = blue();
                if (game_over) break;
                game_over = red();
                if (game_over) break;
                game_over = green();
                if (game_over) break;
                game_over = yellow();
                     
            }
            break;            
    }

    return 0;

}