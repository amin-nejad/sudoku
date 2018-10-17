#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in)
    cout << "Failed!" << endl;
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << endl;
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3))
    cout << "  +===========+===========+===========+" << endl;
  else
    cout << "  +---+---+---+---+---+---+---+---+---+" << endl;
}

/* internal helper function */
void print_row(const char* data, int row) {
  cout << (char) ('A' + row) << " ";
  for (int i=0; i<9; i++) {
    cout << ( (i % 3) ? ':' : '|' ) << " ";
    cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
  }
  cout << "|" << endl;
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) 
    cout << (char) ('1'+r) << "   ";
  cout << endl;
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */

// function to check if a board is complete or not
bool is_complete(const char board [9][9]){
  for (int r=0;r<9;r++){
    for (int c=0;c<9;c++){
      if (board[r][c]=='.'){
	  return false;
	}
    }
  }
  return true;
}

bool make_move(const char position[2], const char digit, char board [9][9]){

  int row, col;
  row = get_row_number(position);
  col = get_col_number(position);
  
  if (is_position_valid(position) && isdigit(digit)
      && is_cell_empty(row,col,board)
      && no_row_repeat(row, digit, board)
      && no_col_repeat(col, digit, board)
      && no_box_repeat(row, col, digit, board)){

    board[row][col] = digit;
    return true;
  } else {
    return false;
  }
}



// helper function to check if cell is empty	   
bool is_cell_empty(const int row, const int col, const char board[9][9]){
  if (board[row][col]=='.'){
    return true;
  } else{
    return false;
  }
}

// helper function which returns the row number from the position
// works with both upper and lower case characters
int get_row_number(const char position[2]){

  int  row;
  row = static_cast<int>(position[0]);
  
  if (row >= 65 && row <= 73){
    row = row -65;
  } else if (row >= 97 && row <= 105){
    row = row - 97;
  }
  return row;
}

// helper function which returns the column number
int get_col_number(const char position[2]){

  int  col;
  col = static_cast<int>(position[1]) - 49;
  return col;
}
 

// helper function to check whether position given is syntactically valid
bool is_position_valid(const char position[2]){

  //verifies that string length is 2 characters
  if (!(strlen(position)==2)){
    return false;
  }
  
  int  row, col;
  row = static_cast<int>(position[0]);
  col = static_cast<int>(position[1]);

  // checks to see if row is within A-I (both lower and upper case) and col within 1-9
  if ((row >= 65 && row <= 73)||(row >= 97 && row <= 105)){
    if(col >= 49 && col <= 57){
	return true;
    }}
  return false;
}

// helper function to verify that there are no repeats of the digit in the same row
bool no_row_repeat(const int row, const char digit, const char board[9][9]){
  
  int  c;
  for (c=0; c<9; c++){
    if (board[row][c] == digit){
      return false;
    }
  }
  return true;
}

// helper function to verify that there are no repeats of the digit in the same column
bool no_col_repeat(const int col, const char digit, const char board[9][9]){
  
  int  r;
  for (r=0; r<9; r++){
    if (board[r][col] == digit){
      return false;
    }
  }
  return true;
}

// helper function to verify that there are no repeats of the digit in the same box
bool no_box_repeat(const int row, const int col, const char digit, const char board[9][9]){
  // co-ordinates r and c locate the top left cell in each 3x3 box 
  int r,c,i,j;
  r = row - (row % 3);
  c = col - (col % 3);

  // variables i and j loop through the box
  for (i = r; i < r + 3 ; r++){
    for (j = c; j < c + 3; c++){
      if (board[i][j] == digit)
	return false;
    }
  }
  return true;
}
