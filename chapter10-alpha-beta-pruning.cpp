// Optimization for Minimax game strategy, using Alpha-Beta Pruning.
// You can watch over the 'function_call_count' variable.
#include <iostream>
#include <vector>
using namespace std;

int function_call_count;

bool computerWin(const vector<int> &board)
{
	int i, j;
	
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (board[i * 3 + j] != -1) {
				break;
			}
		}
		if (j == 3) {
			return true;
		}
	}
	
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (board[j * 3 + i] != -1) {
				break;
			}
		}
		if (j == 3) {
			return true;
		}
	}
	
	if (board[0] == board[4] && board[4] == board[8] && board[8] == -1) {
		return true;
	}
	
	if (board[2] == board[4] && board[4] == board[6] && board[6] == -1) {
		return true;
	}
	
	return false;
}

bool humanWin(const vector<int> &board)
{
	int i, j;
	
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (board[i * 3 + j] != 1) {
				break;
			}
		}
		if (j == 3) {
			return true;
		}
	}
	
	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			if (board[j * 3 + i] != 1) {
				break;
			}
		}
		if (j == 3) {
			return true;
		}
	}
	
	if (board[0] == board[4] && board[4] == board[8] && board[8] == 1) {
		return true;
	}
	
	if (board[2] == board[4] && board[4] == board[6] && board[6] == 1) {
		return true;
	}
	
	return false;
}

bool fullBoard(const vector<int> &board)
{
	for (int i = 0; i < 9; ++i) {
		if (board[i] == 0) {
			return false;
		}
	}
	
	return true;
}

void findComputerMove(vector<int> &board, int &best_move, int &result, 
	int alpha, int beta)
{
	void findHumanMove(vector<int> &, int &, int &, int, int);
	int dc, i, response;
	
	++function_call_count;
	best_move = -1;

	if (fullBoard(board)) {
		result = 0;
		return;
	}
	
	if (computerWin(board)) {
		result = -1;
		return;
	}
	
	result = alpha;
	for (i = 0; i < 9 && result > beta; ++i) {
		if (board[i] != 0) {
			continue;
		}
		board[i] = -1;
		findHumanMove(board, dc, response, result, beta);
		board[i] = 0;
		
		if (best_move == -1 || response < result) {
			result = response;
			best_move = i;
		}
	}
}

void findHumanMove(vector<int> &board, int &best_move, int &result, int alpha, 
	int beta)
{
	void findComputerMove(vector<int> &, int &, int &, int, int);
	int dc, i, response;
	
	++function_call_count;
	best_move = -1;

	if (fullBoard(board)) {
		result = 0;
		return;
	}
	
	if (humanWin(board)) {
		result = 1;
		return;
	}
	
	result = beta;
	for (i = 0; i < 9 && result < alpha; ++i) {
		if (board[i] != 0) {
			continue;
		}
		board[i] = 1;
		findComputerMove(board, dc, response, alpha, result);
		board[i] = 0;
		
		if (best_move == -1 || response > result) {
			result = response;
			best_move = i;
		}
	}
}

void printBoard(const vector<int> &board)
{
	cout << "  1 2 3" << endl;
	int i, j;
	
	for (i = 0; i < 3; ++i) {
		cout << i + 1;
		for (j = 0; j < 3; ++j) {
			cout << ' ';
			switch(board[i * 3 + j]) {
			case -1:
				cout << 'X';
				break;
			case 0:
				cout << '.';
				break;
			case 1:
				cout << 'O';
				break;
			}
		}
		cout << endl;
	}
}

int main()
{
	vector<int> board;
	int n;
	int result;
	
	board.resize(9, 0);
	while (cin >> n) {
		if (n < 0 || n >= 9 || board[n]) {
			cout << "Invalid move" << endl;
			continue;
		}

		board[n] = 1;
		printBoard(board);
		if (humanWin(board)) {
			cout << "You win." << endl;
			break;
		}
		
		if (fullBoard(board)) {
			cout << "Draw." << endl;
			break;
		}
		
		result = 1;
		function_call_count = 0;
		findComputerMove(board, n, result, 1, -1);
		cout << "Number of function calls: " << function_call_count << endl;
		board[n] = -1;
		printBoard(board);
		if (computerWin(board)) {
			cout << "Computer win." << endl;
			break;
		}
		
		if (fullBoard(board)) {
			cout << "Draw." << endl;
			break;
		}
	}
	
	return 0;
}