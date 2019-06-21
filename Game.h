#include <vector>
#include <iomanip>

#ifndef GAME
#define GAME

class Game {
public:
	Game(int size);
	
	//generate a 2 or 4 on the board
	void rand_num_generate();

	//combine the value of two grids if they have the same value
	//set board[row1][col1] to 0 and double the value of board[row2][col2] 
	bool combine(int row1, int col1, int row2, int col2);

	//find the nearest non-zero integer
	//if find, record its row and column, return true
	//if not, return false;
	bool nearest_non_zero_int(int row, int col, int & row_f, int & col_f);
	//formalize the board after the combination
	//e.g.
	//    2 0 4 0           0 0 2 4
	//    0 0 0 0    ->     0 0 0 0
	//    0 0 0 0           0 0 0 0
	//    0 0 0 0           0 0 0 0
	void formalize();

	//move one step
	void move();

	//check the status of the game
	//if 2048 is achieved, win
	//if the board is full, lose
	void CheckStatus(bool & ended, bool & win);

	//display the board
	void display();

	//play the game
	void play();

	//return true if no consecutive identical elements
	bool no_consecutive_identical_elements();

	//return the number of non-empty grid
	int filledspace();

	//auxciliary function to check whether the program is correct
	//never called
	void set(int row, int col, int val);

	//let the user choose the preferred key
	void chooseKey();

private:
	std::vector<std::vector<int>> m_board;
	int m_size;
	int m_score;
	char m_action;

	char m_up;
	char m_down;
	char m_left;
	char m_right;
};

#endif // !GAME

