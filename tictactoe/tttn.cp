// NxN tic-tac-toes
#include <iostream>
#include <cstdlib>
using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);


/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/**
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */
int checkForWinner(char grid[], int dim);

/**
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 *
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);

/**
 * @brief Get the Ai Choice for the current player and update grid object
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If an error occurred or a choice was unable to be made
 * @return false If a play was successfully made
 */
bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player);

/**
 * @brief Picks a random location for the current player and update grid
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If no viable location to be played
 * @return false If a play was successfully made
 */
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player);


/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c)
{
    return grid[(r*dim) + c];
}

int idxToRow(int idx, int dim)
{
    return idx / dim ;
}

int idxToCol(int idx, int dim)
{
    return idx % dim;
}

void printTTT(char grid[], int dim)
{
  // For loop that goes through the rows, and nested for loop for looping
  // through the columns
  for (int r = 0; r < dim; r++) {
    for (int c = 0; c < dim; c++) {
      // Use getEntryAtRC to find the location at the row and column
      cout << " " << getEntryAtRC(grid, dim, r, c);
      // If statement that prints the vertical line
      if (c < dim - 1) {
        // print the vertical line
        cout << " |";
      }
      else {
        cout << " ";
      }
    }
    cout << endl;
    if (r < dim -1) {
      for (int i = 0; i < (dim*4) - 1; i++) {
          cout << "-";
        }
        cout << endl;
    }
  }
}

int checkForWinner(char grid[], int dim) {
  // initialize the count
  int count_x = 0;
  int count_o = 0;
  // check rows
  for (int r = 0; r < dim; r++) {
    count_x = 0;
    count_o = 0;
    // loop through the cols
    for (int c = 0; c < dim; c++) {
      if (getEntryAtRC(grid, dim, r, c) == 'X') {
        count_x++;
        }
      else if (getEntryAtRC(grid, dim, r, c) == 'O') {
        count_o++;
        }
    }
      // checking if you won tic tac toe
    if (count_x == dim) {
      return 1;
    }
    else if (count_o == dim) {
      return 2;
      }
  }

    // check for columns
  for (int c = 0; c < dim; c++) {
    count_x = 0;
    count_o = 0;
    // loop through the rows
    for (int r = 0; r < dim; r++) {
      if (getEntryAtRC(grid, dim, r, c) == 'X') {
        count_x++;
        }
      else if (getEntryAtRC(grid, dim, r, c) == 'O') {
        count_o++;
        }
    }
    // checking if you won tic tac toe
    if (count_x == dim) {
      return 1;
      }
    else if (count_o == dim) {
      return 2;
      }
  }

    // check for diagonal
  count_x = 0;
  count_o = 0;
  for (int r = 0; r < dim; r++) {
    // if the diagonal at both rows is X then increment count_x
    if (getEntryAtRC(grid, dim, r, r) == 'X') {
      count_x++;
      }
    // if the check finds a O on both rows increment count_o
    else if (getEntryAtRC(grid, dim, r, r) == 'O') {
      count_o++;
      }
  }
  // if count_x is equal to the dimension, return 1
  if (count_x == dim) {
    return 1;
    }
  // if count_o is equal to dimension, return 2
  else if (count_o == dim) {
    return 2;
    }

  // check for the second diagonal
  count_x = 0;
  count_o = 0;
  for (int r = 0; r < dim; r++) {
    if (getEntryAtRC(grid, dim, r, (dim - r - 1)) == 'X') {
      count_x++;
      }
    else if (getEntryAtRC(grid, dim, r, (dim - r - 1)) == 'O') {
      count_o++;
      }
  }
  if (count_x == dim) {
    return 1;
    }
    else if (count_o == dim) {
    return 2;
    } 
    else {
      return 0;
    }
}

bool checkForDraw(char grid[], int dim) {
  int count_x, count_o;
  // check rows
  for (int r = 0; r < dim; r++) {
      count_x = 0;
      count_o = 0;
      // loop through the cols
      for (int c = 0; c < dim; c++) {
          if (getEntryAtRC(grid, dim, r, c) == 'X') {
              count_x++;
          }
          else if (getEntryAtRC(grid, dim, r, c) == 'O') {
              count_o++;
          }
      }
      // checking if it's a win
      if (count_x == 0|| count_o == 0) {
          return false;
      }
  }
  // check for columns
  for (int c = 0; c < dim; c++) {
    count_x = 0;
    count_o = 0;
    // loop through the rows
    for (int r = 0; r < dim; r++) {
      if (getEntryAtRC(grid, dim, r, c) == 'X') {
        count_x++;
      }
      else if (getEntryAtRC(grid, dim, r, c) == 'O') {
        count_o++;
      }
    }
    // checking if it's a draw 
    if (count_x == 0 || count_o == 0) {
      return false;
    }
  }
  // check for diagonal
  count_x = 0;
  count_o = 0;
  for (int r = 0; r < dim; r++) {
    if (getEntryAtRC(grid, dim, r, r) == 'X') {
      count_x++;
    }
    else if (getEntryAtRC(grid, dim, r, r) == 'O') {
      count_o++;
    }
  }
  // checking if it's a draw
  if (count_x == 0 || count_o == 0) {
      return false;
  }
  // check for the opposite diagonal
  count_x = 0;
  count_o = 0;
  for (int r = 0; r < dim; r++) {
      if (getEntryAtRC(grid, dim, r, dim - r - 1) == 'X') {
        count_x++;
      }
      else if (getEntryAtRC(grid, dim, r, dim - r - 1) == 'O') {
        count_o++;
      }
  }
  // checking if it's a draw
  if (count_x == 0 || count_o == 0) {
    return false;
  }
  else {
    return true;
  }
}

bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player)
{
int count_x = 0;
int count_o = 0;
// check rows
for (int r = 0; r < dim; r++) {
  count_x = 0;
  count_o = 0;
  int index = -1;
  // loop through the cols
  for (int c = 0; c < dim; c++) {
    if (getEntryAtRC(grid, dim, r, c) == 'X') {
      count_x++;
      }
    else if (getEntryAtRC(grid, dim, r, c) == 'O') {
      count_o++;
      }
    if (getEntryAtRC(grid, dim, r, c) == '?') {
      index = c + (r * dim);
    }
  }
    // check what the move should be based on the other inputs
  if (count_x == dim - 1 && index != -1) {
    if (player == 'X') {
      grid[index] = 'X';
    }
    else {
      grid[index] = 'O';
    }
    return false;
  }
  else if (count_o == dim - 1 && index != -1) {
    if (player == 'X') {
      grid[index] = 'X';
    }
    else {
      grid[index] = 'O';
    }
    return false;
    }
}

  // check for columns
for (int c = 0; c < dim; c++) {
  count_x = 0;
  count_o = 0;
  int index = -1;
  // loop through the rows
  for (int r = 0; r < dim; r++) {
    if (getEntryAtRC(grid, dim, r, c) == 'X') {
      count_x++;
      }
    else if (getEntryAtRC(grid, dim, r, c) == 'O') {
      count_o++;
      }
    if (getEntryAtRC(grid, dim, r, c) == '?') {
      index = dim*r + c;
    }
  }
  // checking what the move should be based on the other inputs
  if (count_x == dim -1 && index != -1) {
    if (player == 'X') {
      grid[index] = 'X';
    }
    else {
      grid[index] = 'O';
    }
    return false;
    }
  else if (count_o == dim -1 && index != -1) {
    if (player == 'X') {
      grid[index] = 'X';
    }
    else {
      grid[index] = 'O';
    }
    return false;
    }
}

  // check for diagonal
count_x = 0;
count_o = 0;
int index = -1;
for (int r = 0; r < dim; r++) {
  // if the diagonal at both rows is X then increment count_x
  if (getEntryAtRC(grid, dim, r, r) == 'X') {
    count_x++;
  }
  // if the check finds a O on both rows increment count_o
  else if (getEntryAtRC(grid, dim, r, r) == 'O') {
    count_o++;
  }
  if (getEntryAtRC(grid, dim, r, r) == '?') {
    index = dim*r + r;
  }
}
// checking waht the move should be based on the diagonal inputs
if (count_x == dim - 1 && index != -1) {
  if (player == 'X') {
      grid[index] = 'X';
    }
    else {
      grid[index] = 'O';
    }
  return false;
  }

else if (count_o == dim - 1 && index != -1) {
  if (player == 'X') {
      grid[index] = 'X';
    }
    else {
      grid[index] = 'O';
    }
  return false;
}

// check for the second diagonal
count_x = 0;
count_o = 0;
index = -1;
for (int r = 0; r < dim; r++) {
  if (getEntryAtRC(grid, dim, r, (dim - r - 1)) == 'X') {
    count_x++;
    }
  else if (getEntryAtRC(grid, dim, r, (dim - r - 1)) == 'O') {
    count_o++;
    }
  if (getEntryAtRC(grid, dim, r, (dim - r - 1)) == '?') {
    index = dim*r + (dim - r - 1);
  }
}
// checking what the moves should be based on the inputs in the second diagonal
if (count_x == dim -1 && index != -1) {
  if (player == 'X') {
      grid[index] = 'X';
    }
    else {
      grid[index] = 'O';
    }
  return false;
}
else if (count_o == dim - 1 && index != -1) {
  if (player == 'X') {
      grid[index] = 'X';
    }
    else {
      grid[index] = 'O';
    }
  return false;
}
return getRandChoiceAndUpdateGrid(grid, dim, player);
}


// Complete...Do not alter
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player)
{
  int start = rand()%(dim*dim);
  // look for an open location to play based on random starting location.
  // If that location is occupied, move on sequentially until wrapping and
  // trying all locations
  for(int i=0; i < dim*dim; i++) {
    int loc = (start + i) % (dim*dim);
    if(grid[ loc ] == '?') {
      grid[ loc ] = player;
      return false;
    }
  }
  // No viable location
  return true;
}

/**********************************************************
 *  Complete the indicated parts of main(), below.
 **********************************************************/
int main()
{
  // This array holds the actual board/grid of X and Os. It is sized
  // for the biggest possible case (11x11), but you should only
  // use dim^2 entries (i.e. if dim=3, only use 9 entries: 0 to 8)
  char tttdata[121];

  // dim stands for dimension and is the side length of the
  // tic-tac-toe board i.e. dim x dim (3x3 or 5x5).
  int dim;
  int seed;
  // Get the dimension from the user
  cin >> dim >> seed;
  srand(seed);

  int dim_sq = dim*dim;

  for(int i=0; i < dim_sq; i++) {
      tttdata[i] = '?';
  }

  // Print one of these messages when the game is over
  // and before you quit
  const char xwins_msg[] = "X player wins!";
  const char owins_msg[] = "O player wins!";
  const char draw_msg[] =  "Draw...game over!";

  // Declare variables, initialize userInput and index
  bool done = false;
  int userInput = 0;
  int index = dim*dim -1;
  char player = 'X';
  int duplicate = 0;
  // Show the initial starting board
  printTTT(tttdata, dim);

  while(!done) {

    //**********************************************************
    // Get the current player's input (i.e. the location they want to
    // choose to place their mark [X or O]) or choice of AI or Random
    // location and update the tttdata array.
    // Be sure to follow the requirements defined in the guide/writeup
    // for quitting immediately if the user input is out-of-bounds
    // (i.e. not in the range 0 to dim_sq-1 nor -1 nor -2) as well as
    // continuing to prompt for an input if the user chooses locations
    // that have already been chosen (already marked with an X or O).
    //**********************************************************
    
    // Add your code here for getting input
    // output the messages and also prompt the user
    // The if statements are for the inputs, depending on the user and outputting the move
    duplicate = 0;
    cout << "Player " << player << " enter your square choice [0-" << index << "], -1 (AI), or -2 (Random):" << endl;
    cin >> userInput;

    if (userInput == -2) {
      getRandChoiceAndUpdateGrid(tttdata, dim, player);
    }
    else if (userInput == -1) {
      getAiChoiceAndUpdateGrid(tttdata, dim, player);
    }
    else if ((userInput >= 0) && (userInput <= index)) {
      if (getEntryAtRC(tttdata, dim, idxToRow(userInput, dim), idxToCol(userInput, dim)) == '?') {
        tttdata[userInput] = player;
      }
      else {
        duplicate = 1;
      }
    }
    else {
      break;
    }

    // Show the updated board if the user eventually chose a valid location
    // (i.e. you should have quit the loop and program by now without any
    //  other output message if the user chosen an out-of-bounds input).
    // printTTT(tttdata, dim);
    if (duplicate == 0) {
      printTTT(tttdata, dim);
      if (player == 'X') {
        player = 'O';
      }
      else if (player == 'O') {
        player = 'X';
      }
    }
    //**********************************************************
    // Complete the body of the while loop to process the input that was just
    //  received to check for a winner or draw and update other status, as
    //  needed.
    //
    // To match our automated checkers' expected output, you must output
    // one of the messages defined above using *one* of the cout commands
    // (under the appropriate condition) below:
    //   cout << owins_msg << endl;  OR
    //   cout << draw_msg << endl;
    //
    // Note: Our automated checkers will examine a specific number of lines
    //  at the end of the program's output and expect to see the updated board
    //  and game status message.  You may certainly add some debug print
    //  statements during development but they will need to be removed to
    //  pass the automated checks.
    //**********************************************************
    // Check if the winner is true, or if the other player wins and if it's a draw
    if (checkForWinner(tttdata, dim) == 1) {
      cout << xwins_msg << endl;
      done = true;
    }
    else if (checkForWinner(tttdata, dim) == 2) {
      cout << owins_msg << endl;
      done = true;
    }
    else if (checkForDraw(tttdata, dim) == true) {
      cout << draw_msg << endl;
      done = true;
    }
  }// end while
  return 0;
}