#include "types.c"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define base -1
#define home -2
#define onApprouchcell -3

#define Bhawana 9
#define Kotuwa 27
#define Pita_Kotuwa 46

//player define
char *name[4] = {"Red","Green","Yellow","Blue"};

//for mysterycells
static int countMcells = 0;
int currentmcell;

// dice roll functuion
int roll_dice(){
    return (rand()%6)+1;
}

//who is the first player

int max = 0;
int maxIndex = 0;
char *maxPlayer = NULL;

void rollDice(){
    for(int i = 0; i< 4; i++){
        int roll = roll_dice();
        printf("%s rolls %d\n",name[i],roll);

        //search for first player per each round
        if (max < roll)
        {
            max = roll;
            maxPlayer = name[i];
            maxIndex = i;
        }
        
    }
    printf("\n%s player rolled the highest with %d and began the game first!!!!\n\n", maxPlayer,max);
}

//player order

void playerOrder(){
    printf("player order: ");
    for(int i = 0; i< 4; i++){
        printf("%s\t", name[(maxIndex + i) % 4]);
    }
}

//each player start positions on the board
int Spositions[] = {28,41,2,15};

//initialize playes & pieces
void initPlayers(){
    
    //for players
    for (int i = 0; i < 4; i++)
    {
        allPlayers[i].name = name[i];
        allPlayers[i].Sposition = Spositions[i];

        //for pieces
        for (int j = 0; j < 4; j++)
        {
            allPlayers[i].pieces[j] = base;
        }
        
    }
    

}


//if one player can capture another player pieces
int capture(int current_player,int piece_index, int newPosition){
    for (int i = 0; i < 4; i++)
    {
        if (i != current_player)
        {
            for (int j = 0; j < 4; j++)
            {
                if (allPlayers[i].pieces[j] == newPosition)
                {
                    //if capture send to the base
                    allPlayers[i].pieces[j] = base;
                    printf("%s's piece %d captured by %s!!!\n",allPlayers[i].name, (j + 1), allPlayers[current_player].name);
                    printf("%s's piece %d has to go to the base\n",allPlayers[i].name, (j + 1));
                    return 1;
                }
                
            }
            
        }
        
    }
    return 0;
}


//mysterycell cal
int mcellcal(){
    return (rand()%52+1);
}

//mysterycells
int mysterycells(){
    
    //countMcells = countMcells + 1;
    if (allPlayers[0].pieces[0] != base && allPlayers[1].pieces[0] != base && allPlayers[2].pieces[0] != base && allPlayers[3].pieces[0] != base && countMcells == 0)
    {
        countMcells = countMcells + 1;
        int mcell = mcellcal();
        currentmcell = mcell;
        printf(">>>>>>>>>>>>>>>>>>>>> A mystery cell appered in %d position\n",mcell);
            
    }else if (countMcells != 0)
    {
        countMcells = countMcells + 1;
        if (countMcells % 4 == 0)
        {
            int mcell = mcellcal();
            if (currentmcell == mcell)
            {
                return mysterycells();
            }else
            {
                int mcell = mcellcal();
                currentmcell = mcell;
                printf(">>>>>>>>>>>>>>>>>>>>> A mystery cell appered in %d position\n",mcell);
            }
            
            
        }
        
    }   
        
}

// mysterycells behaviour
int mysterycellbehave(int current_player,int piece_index){
    int teleport[3] = {9,27,46};
    int teleroll = (rand()%3);
    switch (teleroll)
    {
    case 0:
        allPlayers[current_player].pieces[piece_index] = teleport[0];
        printf("%s's piece %d teleport to the board position at %d (Bhawana)!!!\n",allPlayers[current_player].name, (piece_index + 1), Bhawana);
        break;
    case 1:
        allPlayers[current_player].pieces[piece_index] = teleport[1];
        printf("%s's piece %d teleport to the board position at %d (Kotuwa)!!!\n",allPlayers[current_player].name, (piece_index + 1), Kotuwa);
        break;
    case 2:
        allPlayers[current_player].pieces[piece_index] = teleport[2];
        printf("%s's piece %d teleport to the board position at %d (Pita-Kotuwa)!!!\n",allPlayers[current_player].name, (piece_index + 1), Pita_Kotuwa);
        break;                
    default:
        break;
    }
}


//put pieces to home
int roadToHome(int current_player, int piece_index, int roll){
    char r_home[] = {'A', 'B', 'C', 'D', 'E', 'F'};

    static int new_position_index = -1;
    new_position_index += roll;

    if (new_position_index < 6)
    {
        printf("%s's piece %d moves to position %c\n", allPlayers[current_player].name, piece_index + 1, r_home[new_position_index -1]);
        return 0;
    }else if (new_position_index == 6)
    {
        allPlayers[current_player].pieces[piece_index] = home;
        printf("%s's piece %d has reached home!\n", allPlayers[current_player].name, piece_index + 1);
        new_position_index = 0; //for next piece 
        return 1;
    }else if (new_position_index > 6)
    {
        new_position_index = new_position_index - roll;  
        printf("%s's piece %d still stay on position %c\n", allPlayers[current_player].name, piece_index + 1, r_home[new_position_index -1]);
    }

    return 0;
}

//move pieces
int move_pieces(int current_player, int piece_index, int roll){
    //Approuch cell positions
    int ApproCell[4] = {26,39,0,13};

    if (allPlayers[current_player].pieces[piece_index] == base)
    {
        if (roll == 6)
        {
            allPlayers[current_player].pieces[piece_index] = allPlayers[current_player].Sposition;
            printf("%s's piece %d enters the board at position %d (start position)!!!\n",allPlayers[current_player].name, (piece_index + 1), allPlayers[current_player].Sposition);
        }else
        {
            printf("%s's piece %d still stay on home :(\n",allPlayers[current_player].name,piece_index + 1);
        }
        
        
    }else if (allPlayers[current_player].pieces[piece_index] == onApprouchcell)
    {
        roadToHome(current_player, piece_index,roll);
    }
    else
    {
        int newPosition = (allPlayers[current_player].pieces[piece_index] + roll) % 52;
        if (roll == 6)
        {
            allPlayers[current_player].pieces[piece_index] = newPosition;
            printf("%s's piece %d moved position %d\n", allPlayers[current_player].name, piece_index + 1, newPosition);
        }
        
        if (capture(current_player, piece_index, newPosition) || roll != 6)
        {
            allPlayers[current_player].pieces[piece_index] = newPosition;
            printf("%s's piece %d moved position %d\n", allPlayers[current_player].name, piece_index + 1, newPosition);
            if (newPosition == ApproCell[current_player])
            {
                allPlayers[current_player].pieces[piece_index] = onApprouchcell;
                printf("%s's piece %d landed on an APPROACH position %d!!!!\n",allPlayers[current_player].name, (piece_index + 1), ApproCell[current_player]);
            }else if (allPlayers[current_player].pieces[piece_index] == currentmcell)
            {
                printf("%s's piece %d enters on the mystrycell!!!\n",allPlayers[current_player].name, (piece_index + 1));
                mysterycellbehave(current_player,piece_index);
            }
            
            
        }
        
    }       
     
}


//check if all pieces in home
int allPiecesInHome(int current_player){
    for (int i = 0; i < 4; i++)
    {
        if (allPlayers[current_player].pieces[i] != home)
        {
            return 0;
        }
        
    }
    return 1;
    
}


//player red
int red(){
    int current_player = 0;
    int roll = roll_dice();
    printf("%s rolled %d\n", allPlayers[current_player].name,roll);

    int movePiece = -1; //still not define what piece to move
    
    for (int j = 0; j < 4; j++)
    {
        if (allPlayers[current_player].pieces[j] == onApprouchcell)
        {
            movePiece = j;
            break;
        }
        
    }


    //If no piece on an approach cell, try to find a piece that can capture
    if (movePiece == -1)
    {
        for (int j = 0; j < 4; j++)
        {
            if (allPlayers[current_player].pieces[j] != base && allPlayers[current_player].pieces[j] != home)
            {
                int newPosition = (allPlayers[current_player].pieces[j] + roll) % 52;

                if (capture(current_player,j,newPosition))
                {
                    movePiece = j;
                    break;
                }
                
            }
            
        }
        
    }

    if (movePiece == -1)
    {
        for (int j = 0; j < 4; j++)
        {
            if (allPlayers[current_player].pieces[j] != home)
            {
                movePiece = j;
                break;
            }
            
        }
        
    }

    //move selected piece
    if (movePiece != -1)
    {
        move_pieces(current_player, movePiece, roll);
        if (allPiecesInHome(current_player))
        {
            printf("\033[1;31m");
            printf("\n## %s wins the game by putting all pieces in home!!!!!!! :)\n\n",allPlayers[current_player].name);
            return 1; //game end
        }

        if (roll == 6)
        {
            return red();
        }
                
    }
    return 0;
        
}


//player green
int green(){
    int current_player = 1;
    int roll = roll_dice();
    printf("%s rolled %d\n", allPlayers[current_player].name,roll);

    int movePiece = -1; //still not define what piece to move
    
    for (int j = 0; j < 4; j++)
    {
        if (allPlayers[current_player].pieces[j] == onApprouchcell)
        {
            movePiece = j;
            break;
        }
        
    }


    //If no piece on an approach cell, try to find a piece that can capture
    if (movePiece == -1)
    {
        for (int j = 0; j < 4; j++)
        {
            if (allPlayers[current_player].pieces[j] != base && allPlayers[current_player].pieces[j] != home)
            {
                int newPosition = (allPlayers[current_player].pieces[j] + roll) % 52;

                if (newPosition % 6 == 0)
                {
                    movePiece = j;
                    break;
                }
                
            }
            
        }
        
    }

    if (movePiece == -1)
    {
        for (int j = 0; j < 4; j++)
        {
            if (allPlayers[current_player].pieces[j] != home)
            {
                movePiece = j;
                break;
            }
            
        }
        
    }

    //move selected piece
    if (movePiece != -1)
    {
        move_pieces(current_player, movePiece, roll);
        if (allPiecesInHome(current_player))
        {
            printf("\033[1;32m");
            printf("\n## %s wins the game by putting all pieces in home!!!!!!! :)\n\n",allPlayers[current_player].name);
            return 1; //game end
        }

        if (roll == 6)
        {
            return green();
        }
                
    }
    return 0;
        
}


//player yellow
int yellow(){
    int current_player = 2;
    int roll = roll_dice();
    printf("%s rolled %d\n", allPlayers[current_player].name,roll);

    int movePiece = -1; //still not define what piece to move
    

    //if piece on approuchcell
    for (int j = 0; j < 4; j++)
    {
        if (allPlayers[current_player].pieces[j] == onApprouchcell)
        {
            movePiece = j;
            break;
        }
        
    }


    // If no piece on an approach cell, try to move a piece out of the base
    if (movePiece == -1)
    {
        for (int j = 0; j < 4; j++)
        {
            if (allPlayers[current_player].pieces[j] == -1)
            {
                movePiece = j;
                break;
            }

        }
        
    }


    // If no piece is off the board, move the first available piece
    if (movePiece == -1)
    {
        for (int j = 0; j < 4; j++)
        {
            if (allPlayers[current_player].pieces[j] != home)
            {
                movePiece = j;
                break;
            }
            
        }
        
    }

    //move selected piece
    if (movePiece != -1)
    {
        move_pieces(current_player, movePiece, roll);
        if (allPiecesInHome(current_player))
        {
            printf("\033[0;33m");
            printf("\n## %s wins the game by putting all pieces in home!!!!!!! :)\n\n",allPlayers[current_player].name);
            return 1; //game end
        }

        if (roll == 6)
        {
            return yellow();
        }
                
    }
    return 0;
        
}


//player blue
int blue(){
    int current_player = 3;
    int roll = roll_dice();
    printf("%s rolled %d\n", allPlayers[current_player].name,roll);

    int movePiece = -1; //still not define what piece to move
    
    // Check if any piece is on an approach cell
    for (int j = 0; j < 4; j++)
    {
        if (allPlayers[current_player].pieces[j] == onApprouchcell)
        {
            movePiece = j;
            break;
        }
        
    }


    //If no piece on an approach cell, try to find a piece that can capture
    if (movePiece == -1)
    {
        for (int j = 0; j < 4; j++)
        {
            if (allPlayers[current_player].pieces[j] != base && allPlayers[current_player].pieces[j] != home)
            {
                int newPosition = (allPlayers[current_player].pieces[j] + roll) % 52;

                if (capture(current_player,j,newPosition))
                {
                    movePiece = j;
                    break;
                }
                
            }
            
        }
        
    }

    if (movePiece == -1)
    {
        for (int j = 0; j < 4; j++)
        {
            if (allPlayers[current_player].pieces[j] != home)
            {
                movePiece = j;
                break;
            }
            
        }
        
    }

    //move selected piece
    if (movePiece != -1)
    {
        move_pieces(current_player, movePiece, roll);
        if (allPiecesInHome(current_player))
        {
            printf("\033[1;34m");
            printf("\n## %s wins the game by putting all pieces in home!!!!!!! :)\n\n",allPlayers[current_player].name);
            return 1; //game end
        }

        if (roll == 6)
        {
            return blue();
        }
                
    }
    return 0;
        
}