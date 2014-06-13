// This is said to be an interview question about game.
// This solution is by dynamic programming.
// Description:
//	If there're 50 stones at the beginning, you and your component take turns to take away 1, 2, 4 or 8 stones.
//	Whoever takes away the last stone loses the game.
//	Does this game has a winning strategy for any side?
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void game(const int n, const vector<int> &move, vector<int> &dp)
{
	int i;
	// dp[i] means the game result when the total number of stones is i.
	// 1 for offensive win, -1 for defensive win, 0 for uncertain(fair play).
	dp.resize(n + 1, 0);
	
	int n_move = (int)move.size();
	int n_win;
	dp[move[0]] = -1;
	
	int j;
	for (i = move[0] + 1; i <= n; ++i) {
		n_win = 0;
		for (j = 0; j < n_move; ++j) {
			if (i - move[j] <= 0) {
				++n_win;
				continue;
			}
			if (dp[i - move[j]] == -1) {
				// one of the parent node in the game tree is lose, 
				// then you win.
				dp[i] = 1;
				break;
			} else if (dp[i - move[j]] == 1) {
				++n_win;
			}
		}
		if (j == n_move && n_win == n_move) {
			// all parent nodes in the game tree are wins, then you lose
			dp[i] = -1;
		}
	}
}

int main()
{
	vector<int> dp;
	vector<int> move;
	int n;
	int i;
	int tmp;
	
	while (cin >> n && n > 0) {
		while (cin >> tmp && tmp > 0) {
			move.push_back(tmp);
		}
		game(n, move, dp);
		sort(move.begin(), move.end());
		for (i = 1; i <= n; ++i) {
			cout << i << ':';
			switch(dp[i]) {
			case -1:
				cout << "Defensive win." << endl;
				break;
			case 0:
				cout << "Fair play." << endl;
				break;
			case 1:
				cout << "Offensive win." << endl;
				break;
			}
		}
		
		dp.clear();
		move.clear();
	}
	
	return 0;
}