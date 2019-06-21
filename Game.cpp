#include "Game.h"
#include <utility>
#include <iostream>
#include <stdlib.h>
#include <conio.h>
using namespace std;

Game::Game(int size)
{
	m_board = vector<vector<int>>(size, vector<int>(size,0));
	m_size = size;
	m_score = 0;
	rand_num_generate();
}

void Game::rand_num_generate()
{
	//determine the number
	int number = rand()%11 <= 9 ? 2 : 4;
	
	//determine its position

	int row, col;
	do {
		row = rand() % m_size;
		col = rand() % m_size;
	} while (m_board[row][col] != 0);
	
	m_board[row][col] = number;
}

bool Game::combine(int row1, int col1, int row2, int col2)
{
	//if they are not the same value
	if (m_board[row1][col1] != m_board[row2][col2]) {
		return false;
	}

	//if they are in the same row
	if (row1 == row2) {
		//if they are the same grid
		if (col1 == col2) {
			return false;
		}
		//increment the score
		m_score += m_board[row1][col1];

		//combine
		m_board[row1][col1] = 0;
		m_board[row2][col2] *= 2;
		return true;
	}
	
	//if they are in the same column
	else if (col1 == col2) {
		//increment the score
		m_score += m_board[row1][col1];

		//combine
		m_board[row1][col1] = 0;
		m_board[row2][col2] *= 2;
		return true;
	}


	else {
		return false;
	}
}

bool Game::nearest_non_zero_int(int row, int col, int & row_f, int & col_f)
{

	if (m_action == m_up) {
		row++;
		for (; row < m_size; row++) {
			if (m_board[row][col] != 0) {
				row_f = row;
				col_f = col;
				return true;
			}
		}
	}

	if (m_action == m_down) {
		row--;
		for (; row >= 0; row--) {
			if (m_board[row][col] != 0) {
				row_f = row;
				col_f = col;
				return true;
			}
		}
	}

	if (m_action == m_left) {
		col++;
		for (; col < m_size; col++) {
			if (m_board[row][col] != 0) {
				row_f = row;
				col_f = col;
				return true;
			}
		}
	}

	if (m_action == m_right) {
		col--;
		for (; col >= 0; col--) {
			if (m_board[row][col] != 0) {
				row_f = row;
				col_f = col;
				return true;
			}
		}
	}

	return false;
}


void Game::formalize()
{
	
	//if the user types "up"
	if(m_action== m_up){
		//for each column
		for (int col = 0; col < m_size; col++) {

			//kind of bubble sort to sort the the column
			bool unarranged = true;
			while (unarranged) {
				unarranged = false;
				for (int row = 0; row < m_size - 1; row++) {
					if (m_board[row][col] == 0 && m_board[row + 1][col] != 0) {
						swap(m_board[row][col], m_board[row + 1][col]);
						unarranged = true;
					}
				}
			}
		}
	}


	//if the user types "down"
	else if (m_action == m_down) {
		//for each column
		for (int col = 0; col < m_size; col++) {
			//kind of bubble sort to sort the the column
			bool unarranged = true;
			while (unarranged) {
				unarranged = false;
				for (int row = m_size - 1; row > 0; row--) {
					if (m_board[row][col] == 0 && m_board[row - 1][col] != 0) {
						swap(m_board[row][col], m_board[row - 1][col]);
						unarranged = true;
					}
				}
			}
		}
	}

	else if (m_action == m_left) {
		//for each row
		for (int row = 0; row < m_size; row++) {
			//kind of bubble sort to sort the the column
			bool unarranged = true;
			while (unarranged) {
				unarranged = false;
				for (int col = 0; col < m_size-1; col++) {
					if (m_board[row][col] == 0 && m_board[row][col + 1] != 0) {
						swap(m_board[row][col], m_board[row][col + 1]);
						unarranged = true;
					}
				}
			}
		}
	}


	//if the user types "right"
	else{
		//for each row
		for (int row = 0; row < m_size; row++) {
			//kind of bubble sort to sort the the column
			bool unarranged = true;
			while (unarranged) {
				unarranged = false;
				for (int col = m_size - 1; col > 0; col--) {
					if (m_board[row][col] == 0 && m_board[row][col - 1] != 0) {
						swap(m_board[row][col], m_board[row][col - 1]);
						unarranged = true;
					}
				}
			}
		}
	}	
}

void Game::move()
{
	cout << "Please choose your move\n";
	cout << m_up << '/' << m_down << '/' << m_left << '/' << m_right << '/' << "(up/down/left/right):";
	//read the action from the user
	m_action = getch();

	int row_f, col_f;

	//if "up"
	if (m_action == m_up) {
		//for each grid
		for (int col = 0; col < m_size; col++) {
			for (int row = 0; row < m_size; row++) {
				//if a nearest non zero integer can be found (if there is something that can be combined)
				if (nearest_non_zero_int(row, col, row_f, col_f)) {
					combine(row_f, col_f, row, col);
				}
			}
		}

		formalize();
	}

	//if "down"
	else if (m_action == m_down) {
		//for each grid
		for (int col = 0; col < m_size; col++) {
			for (int row = m_size - 1; row >= 0; row--) {
				//if a nearest non zero integer can be found (if there is something that can be combined)
				//if a nearest non zero integer can be found (if there is something that can be combined)
				if (nearest_non_zero_int(row, col, row_f, col_f)) {
					combine(row_f, col_f, row, col);
				}
			}
		}
		formalize();
	}

	//if "left"
	else if (m_action == m_left) {
		//for each grid
		for (int row = 0; row < m_size; row++) {
			for (int col = 0; col < m_size; col++) {
				//if a nearest non zero integer can be found (if there is something that can be combined)
				if (nearest_non_zero_int(row, col, row_f, col_f)) {
					combine(row_f, col_f, row, col);
				}
			}
		}

		formalize();
	}


	//if "right"
	else if (m_action == m_right) {
		//for each grid
		for (int row = 0; row < m_size; row++) {
			for (int col = m_size - 1; col >= 0; col--) {
				//if a nearest non zero integer can be found (if there is something that can be combined)
				if (nearest_non_zero_int(row, col, row_f, col_f)) {
					combine(row_f, col_f, row, col);
				}
			}
		}

		formalize();
	}
}

void Game::CheckStatus(bool & ended, bool & win)
{
	//record whether a grid is empty
	bool havezero = false;

	//record the largest number in the board
	int largest = 0;
	for (int row = 0; row < m_size; row++) {
		for (int col = 0; col < m_size; col++) {
			int temp = m_board[row][col];

			if (temp > largest) {
				largest = temp;
			}

			if (temp == 0) {
				havezero = true;
			}	
		}
	}

	if (largest >= 2048) {
		ended = true;
		win = true;
	}
	
	if (!havezero) {
		if (no_consecutive_identical_elements()) {
			ended = true;
			win = false;
		}
	}
}

void Game::display()
{
	cout << "Score: " << m_score << endl<< endl;

	for (int row = 0; row < m_size; row++) {
		for (int col = 0; col < m_size; col++) {
			if (m_board[row][col] == 0) {
				cout << setw(5)<<left<<'.';
			}
			else {
				cout << setw(5)<<left << m_board[row][col];
			}
		}
		cout << endl << endl;
	}
}

void Game::play()
{
	bool ended = false;
	bool win;

	chooseKey();
	display();

	while (true) {
		auto temp = m_board;
		move();

		//if invalid move (movement doesn't make changes to the board),
		//no random number generated
		//only if a valid move or no valid move available, a random number is generated
		if (temp != m_board || 
			filledspace() >= m_size * m_size - 1) {
			rand_num_generate();
		}

		//clear screen
		system("cls");
		//display the board
		display();
		//check the status
		CheckStatus(ended, win);

		if (ended) {
			if (win) {
				cout << "\nCongratuation, you win!\n";
			}
			else {
				cout << "\nYou lose!\n";
			}
			break;
		}
	}

	cout << "Press ENTER to quit...";
	cin.ignore(10000, '\n');
}

bool Game::no_consecutive_identical_elements()
{
	for (int row = 0; row < m_size - 1; row++) {
		for (int col = 0; col < m_size - 1; col++) {
			//if consecutive members have the same value
			if (m_board[row][col] == m_board[row + 1][col]
				|| m_board[row][col] == m_board[row][col + 1]) {
				return false;
			}
		}
	}

	return true;
}

int Game::filledspace()
{
	int sum = 0;
	for (int row = 0; row < m_size - 1; row++) {
		for (int col = 0; col < m_size - 1; col++) {
			//if consecutive members have the same value
			if (m_board[row][col] != 0) {
				sum += 1;
			}
		}
	}
	return sum;
}

void Game::set(int row, int col, int val)
{
	m_board[row][col] = val;
}

void Game::chooseKey()
{
	cout << "Please enter your preferred key:\n";
	cout << "up: ";
	cin >> m_up;

	cout << "down: ";
	cin >> m_down;

	cout << "left: ";
	cin >> m_left;

	cout << "right: ";
	cin >> m_right;

	cin.ignore(10000, '\n');
	cout << '\n';
	cout << "You are all set.\n";
	cout << "Press ENTER to start...";
	cin.ignore(10000, '\n');
	system("cls");
}

