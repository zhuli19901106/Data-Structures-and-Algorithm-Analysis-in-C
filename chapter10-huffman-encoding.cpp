// A simple illustration for 
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// The character statistics type
typedef unordered_map<char, int> StatType;
// The character encoding type
typedef unordered_map<char, string> EncodeType;

struct TreeNode {
	char ch;
	int weight;
	TreeNode *left;
	TreeNode *right;
	
	TreeNode(char _ch, int _weight): ch(_ch), weight(_weight), 
		left(nullptr), right(nullptr) {}
};

struct GreaterFunctor {
	bool operator () (const TreeNode *x, const TreeNode *y) {
		return x->weight > y->weight;
	}
};

void deleteTree(TreeNode *&root)
{
	if (root == nullptr) {
		return;
	} else {
		deleteTree(root->left);
		deleteTree(root->right);
		delete root;
		root = nullptr;
	}
}

void calculateEncoding(const TreeNode *root, EncodeType &encoding, string &path)
{
	if (root == nullptr) {
		return;
	}
	
	if (root->ch != '\0') {
		encoding[root->ch] = path;
		return;
	}
	
	path.push_back('0');
	calculateEncoding(root->left, encoding, path);
	path.pop_back();
	
	path.push_back('1');
	calculateEncoding(root->right, encoding, path);
	path.pop_back();
}

void huffmanEncoding(const StatType &statistics, EncodeType &encoding)
{
	priority_queue<TreeNode *, vector<TreeNode *>, GreaterFunctor> pq;
	
	int n;
	
	n = 0;
	for (StatType::const_iterator sta_it = statistics.begin(); 
		sta_it != statistics.end(); ++sta_it) {
		pq.push(new TreeNode(sta_it->first, sta_it->second));
		++n;
	}
	
	TreeNode *p1, *p2, *p3;
	int i;
	for (i = 0; i < n - 1; ++i) {
		p1 = pq.top();
		pq.pop();
		p2 = pq.top();
		pq.pop();
		
		p3 = new TreeNode('\0', p1->weight + p2->weight);
		p3->left = p1;
		p3->right = p2;
		pq.push(p3);
	}
	
	TreeNode *root = pq.top();
	pq.pop();
	
	string code = "";
	calculateEncoding(root, encoding, code);
	deleteTree(root);
}

int main()
{
	int i, n;
	string s;
	int weight;
	StatType statistics;
	EncodeType encoding;
	
	while (cin >> n && n > 0) {
		for (i = 0; i < n; ++i) {
			cin >> s >> weight;
			statistics[s[0]] = weight;
		}
		huffmanEncoding(statistics, encoding);
		
		for (EncodeType::const_iterator enc_it = encoding.begin(); 
			enc_it != encoding.end(); ++enc_it) {
			cout << enc_it->first << ':' << enc_it->second << endl;
		}
		cout << endl;

		statistics.clear();
		encoding.clear();
	}
	
	return 0;
}