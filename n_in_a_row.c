///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for CS 354 Fall 2020, Deb Deppeler
//
////////////////////////////////////////////////////////////////////////////////
// Main File:        n_in_a_row.c
// This File:        n_in_a_row.c
// Other Files:      None. 
// Semester:         CS 354 Fall 2020
//
// Author:           Rhea Cherian
// Email:            rcherian@wisc.edu
// CS Login:         cherian
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          None. 
//
// Online sources:   None. 
////////////////////////////////////////////////////////////////////////////////
   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
     
char *DELIM = ",";  // commas ',' are a common delimiter character for data strings
     
/* COMPLETED:       
 * Retrieves from the first line of the input file,
 * the size of the board (number of rows and columns).
 * 
 * fp: file pointer for input file
 * size: pointer to size
 */
void get_dimensions(FILE *fp, int *size) {      
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, fp) == -1) {
        printf("Error in reading the file.\n");
        exit(1);
    }

    char *token = NULL;
    token = strtok(line, DELIM);
    *size = atoi(token);
}       
 
/* TODO:
 * Returns 1 if and only if the board is in a valid state.
 * Otherwise returns 0.
 * 
 * board: heap allocated 2D board
 * size: number of rows and columns
 */
int n_in_a_row(int **board, int size) {

    int numX = 0; //keeps count of the number of x's on the board 
    int numO = 0; //keeps count of the number of o's on the board
    int count = 0; //keeps track of how many x's and o's are in current row,
   // column, diagnol, if there's an x, count increments positively -
   // if there's an o, count decrements
    int x_wins = 0; //keeps count of the number of wins for x
    int o_wins = 0; //keeps count of the number of wins for o


    //if even-sized board, it's an invalid board so returns 0
    if(size % 2 == 0){
	return 0;
    }

    //iterating through the rows first
    for(int i = 0; i < size; i++){
       count = 0; 
       for(int j = 0; j < size; j++){
       	  if(*(*(board + i) + j) == 1){
	     count++; //1 represents an x, so count increments positively
	     numX++; //incrementing the number of x's only once 
	  }

	  if(*(*(board+i)+j) == 2){
	     count--; //2 represents an o, so count decrements by 1
	     numO++;  //incrementing the number of o's only once  
	  }
       }

       if(count == size){
	  x_wins++;
       }

       if(count == -1 * size){
	  o_wins++;
       }
    }

    //iterating through the columns next
    for(int i = 0; i < size; i++){
       count = 0; 
       for(int j = 0; j < size; j++){
          if(*(*(board + j) + i) == 1){
	     count++;
	  }

	  if(*(*(board + j) + i) == 2){
	     count--; 
	  }
       }

       if(count == size){
	   x_wins++; 
       }

       if(count == -1 * size){
           o_wins++; 
       }
    }

    count = 0; 
    //left-right diagonal
    for(int i = 0; i < size; i++){
       if(*(*(board + i) + i) == 1){
          count++; 
       }
       if(*(*(board + i) + i) == 2){
          count--; 
       }
    }

    if(count == size){
       x_wins++;
    }

    if(count == -1 * size){
       o_wins++; 
    }

    //right-left diagonal
    count = 0;
    int i = 0;  
    for(int j = size - 1; j >= 0; j--){
       if(*(*(board + j) + i) == 1){
          count++;
       }

       if(*(*(board + j) + i) == 2){
          count--; 
       }

       i++;
    }

    if(count == size){
	x_wins++;
    }

    if(count == -1 * size){
	 o_wins++; 
    }

    //if there's not the same number x's as o's, or 1 more x than o,
    //then board is invalid, so returns 0

    if((numX - numO) > 1 || (numX - numO) < 0){
	 return 0; 
    }

    //only one or zero winners. otherwise, board is invalid, returns 0
    if((x_wins + o_wins) > 1){
	return 0; 
    }

    return 1;   
}    
  
 
   
/* PARTIALLY COMPLETED:
 * This program prints Valid if the input file contains
 * a game board with either 1 or no winners; and where
 * there is at most 1 more X than O.
 * 
 * argc: CLA count
 * argv: CLA value
 */
int main(int argc, char *argv[]) {              
     
    //TODO: Check if number of command-line arguments is correct.
    if(argc != 2){
      printf("commandline arguments incorrect\n solution: ./n_in_a_row <filename>\n");
      exit(1);
    }
    //Open the file and check if it opened successfully.
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Can't open file for reading.\n");
        exit(1);
    }

    //Declare local variables.
    int size; //board size
    int *sizeptr = &size; //ptr to board size 
    int **board; //stores board

    //TODO: Call get_dimensions to retrieve the board size.
    get_dimensions(fp, sizeptr);

    //TODO: Dynamically allocate a 2D array of dimensions retrieved above.
    board = malloc(sizeof(int*)*size); 
    for(int i = 0; i < size; i++){
      board[i] = malloc(sizeof(int*)*size);
    }
    //Read the file line by line.
    //Tokenize each line wrt the delimiter character to store the values in your 2D array.
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < size; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file.\n");
            exit(1);
        }

        token = strtok(line, DELIM);
        for (int j = 0; j < size; j++) {
            //TODO: Complete the line of code below
            //to initialize your 2D array.
            *(*(board+i)+j)  = atoi(token);
            token = strtok(NULL, DELIM);
        }
    }

    //TODO: Call the function n_in_a_row and print the appropriate
    //output depending on the function's return value.
    

    int resultingBoard = n_in_a_row(board, size); 
    if(resultingBoard == 1){
      printf("valid\n");
    }else{
      printf("invalid\n");
    }
    //TODO: Free all dynamically allocated memory.
    for(int i = 0; i < size; i++){
    	free(*(board+i));
    }
    free(board);
    board = NULL;
    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file.\n");
        exit(1);
    } 
     
    return 0;       
}       



                                        // FIN
