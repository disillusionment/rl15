/* * * * * * * * * * * * * * * * * * * * 
 * 
 * Roguelike in 15 steps
 * 
 * base.c  7-25-2017
 *
 * * * * * * * * * * * * * * * * * * * */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "map.h"


// ANSI Escape Code Defines
#define ANSINRM  "\x1B[0m"
#define ANSIRED  "\x1B[31m"
#define ANSIGRN  "\x1B[32m"
#define ANSIYEL  "\x1B[33m"
#define ANSIBLU  "\x1B[34m"
#define ANSIMAG  "\x1B[35m"
#define ANSICYN  "\x1B[36m"
#define ANSIWHT  "\x1B[37m"
#define ANSICLR  "\x1B[0;0H\x1B[2J"


int MapDisplayWidth  = 13;
int MapDisplayHeight = 13; 
int PlayerXLocation = 8;
int PlayerYLocation = 10;

void clearScreen(void) {
printf(ANSICLR);
}

void printOffset(int spaces) {

     for(int i=0;i<=spaces;i++) {
          printf("  ");
     }
}

void printFrameTB(void) {
     printf(ANSIBLU "+");
     printf("--------------------------");
     printf("+\n" ANSINRM);
}

void displayMap(int Width, int Height, int CenterX, int CenterY) {
     // CenterX-6 to CenterX+6
     // CenterY-6 to CenterY+6
     int IterateX, IterateY = 0;
     int XRange = ((MapDisplayWidth -1) / 2);
     int YRange = ((MapDisplayHeight -1) / 2);

     // display border
     clearScreen();
     printOffset(10);
     printFrameTB();

// TODO
// if PlayerX < XRange or > MapWidth - Xrange move player instead of map
// same with PlayerY
     
     // MAP MOVE
     for(IterateX = CenterX - XRange ; IterateX <= CenterX + XRange ; IterateX++) {
          printOffset(10);
          printf(ANSIBLU "|" ANSINRM);
          for(IterateY = CenterY - YRange ; IterateY <= CenterY + YRange ; IterateY++) {
       
               if(IterateX == CenterX && IterateY == CenterY) {
                    printf(" @");
               }  else  { 
                    printf(" %c",map[IterateX][IterateY]);
               } 
          }
          printf(ANSIBLU "|\n" ANSINRM);
     }
     // END MAP MOVE
     
     // PLAYER MOVES MAP DOESN'T
     // Figure out where @ goes.
     
     
     // print rest of map.
     // END OF PLAYER MOVES
     printOffset(10);
     printFrameTB();
}

void displayStats(void) {};

char getInput(void) {
     int kbin;
     printf("> ");
     system ("/bin/stty raw");
     kbin = getchar();
     system ("/bin/stty cooked");
     return(kbin);
}


void displayScreen(void) {
     displayMap(MapDisplayWidth, 
                MapDisplayHeight, 
                PlayerXLocation,
                PlayerYLocation);

   displayStats();



}



void impassable(void) {
   printf("Impassable!");
}

int passable(int checkMapX, int checkMapY) {
     char checkPass = map[checkMapX][checkMapY];
     if( (checkPass != 'X') &&
         (checkPass != 'x'))
     {
          return(1);
     }  else  {
          return(0);
     }
}

int main(int argc, char *argv[]) {
     int action;
     while(1) {
          displayScreen();
          action = getInput();
               switch(action) {
		  case '4':
		       if(passable(PlayerXLocation, PlayerYLocation - 1)) {
                            PlayerYLocation--;
		       }  else  {
                            impassable();
                       }
                       break;
		  case '1':
		       if(passable(PlayerXLocation,PlayerYLocation-1) && 
                          passable(PlayerXLocation+1,PlayerYLocation)) {
                            PlayerYLocation--;
		            PlayerXLocation++;
		       }  else  {
                            impassable();
                       }
                       break;
		  case '2':
                       if(passable(PlayerXLocation+1,PlayerYLocation)) {
		            PlayerXLocation++;
		       }  else  {
                            impassable();
                       }
                       break;
		  case '3':
		       if(passable(PlayerXLocation, PlayerYLocation+1) && 
                          passable(PlayerXLocation+1, PlayerYLocation)) {
                            PlayerYLocation++;
		            PlayerXLocation++;
		       }  else  {  impassable(); } break;
		  case '6':
                       if(passable(PlayerXLocation, PlayerYLocation+1)) {
		            PlayerYLocation++;
		        }  else  {
                             impassable();
                        }
                        break;
		  case '9':
                       if(passable(PlayerXLocation, PlayerYLocation+1) && 
                          passable(PlayerXLocation-1, PlayerYLocation)) {
		            PlayerYLocation++;
		            PlayerXLocation--;
		       }  else  {  
                            impassable(); 
                       }
                       break;
		  case '8':
                       if(passable(PlayerXLocation-1,PlayerYLocation)) {
		            PlayerXLocation--;
		       }  else  {
                            impassable(); 
                       }
                       break;
		  case '7':
                       if(passable(PlayerXLocation, PlayerYLocation-1) && 
                          passable(PlayerXLocation-1,PlayerYLocation)) {
		            PlayerYLocation--;
		            PlayerXLocation--;
		       }  else  {  
                            impassable(); }
                       break;
		  case 'q':
		       exit(0);
		       break;
                  default:
		       printf(ANSICYN "\n Unknown Command.\n");
                       sleep(1);
                       break;
		  }


          }
}
