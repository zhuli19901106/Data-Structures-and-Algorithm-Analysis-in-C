// My implementation for avl tree.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TreeNode {
	int val;
	int height;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	TreeNode(int _val): val(_val), height(1), left(nullptr), right(nullptr), parent(nullptr) {};
};

class AVLTree {
public:
	AVLTree() {
		m_root = nullptr;
	}
	
	bool empty() {
		return m_root == nullptr;
	}
	
	void clear() {
		_deleteTree(m_root);
	}
	
	void insertNode(const int &val) {
		if (m_root == nullptr) {
			m_root = new TreeNode(val);
			return;
		}

		TreeNode *ptr = _findNode(val);
		
		if (val == ptr->val) {
			return;
		}
		
		if (val < ptr->val) {
			ptr->left = new TreeNode(val);
			ptr->left->parent = ptr;
		} else if (val > ptr->val) {
			ptr->right = new TreeNode(val);
			ptr->right->parent = ptr;
		}
		
		int hl, hr;
		TreeNode *ptr2;
		while (ptr != nullptr) {
			ptr2 = ptr->parent;
			_getHeight(ptr);
			hl = _height(ptr->left);
			hr = _height(ptr->right);
			switch(hl - hr) {
			case -2:
				switch (_height(ptr->right->left) - _height(ptr->right->right)) {
				case -1:
					_singleRotationRight(ptr);
					break;
				case +1:
					_doubleRotationRightLeft(ptr);
					break;
				}
				break;
			case +2:
				switch (_height(ptr->left->left) - _height(ptr->left->right)) {
				case -1:
					_doubleRotationLeftRight(ptr);
					break;
				case +1:
					_singleRotationLeft(ptr);
					break;
				}
				break;
			}
			ptr = ptr2;
		}
	}
	
	void deleteNode(const int &val) {
		if (m_root == nullptr) {
			return;
		}
		
		TreeNode *par, *cur;
		
		cur = _findNode(val);
		if (cur == nullptr || cur->val != val) {
			return;
		}
		par = cur->parent;
		
		TreeNode *ptr;
		do {
			if (cur->left != nullptr) {
				ptr = _shiftLeft(cur);
				break;
			}
		
			if (cur->right != nullptr) {
				ptr = _shiftRight(cur);
				break;
			}
		
			if (par == nullptr) {
				delete cur;
				m_root = nullptr;
			} else if (val < par->val) {
				delete cur;
				par->left = nullptr;
			} else {
				delete cur;
				par->right = nullptr;
			}
			ptr = par;
		} while (0);

		int hl, hr;
		TreeNode *ptr2;
		while (ptr != nullptr) {
			ptr2 = ptr->parent;
			_getHeight(ptr);
			hl = _height(ptr->left);
			hr = _height(ptr->right);
			switch(hl - hr) {
			case -2:
				switch (_height(ptr->right->left) - _height(ptr->right->right)) {
				case -1:
					_singleRotationRight(ptr);
					break;
				case +1:
					_doubleRotationRightLeft(ptr);
					break;
				}
				break;
			case +2:
				switch (_height(ptr->left->left) - _height(ptr->left->right)) {
				case -1:
					_doubleRotationLeftRight(ptr);
					break;
				case +1:
					_singleRotationLeft(ptr);
					break;
				}
				break;
			}
			ptr = ptr2;
		}
	}
	
	void updateNode(const int &old_val, const int &new_val) {
		deleteNode(old_val);
		insertNode(new_val);
	}
	
	bool contains(const int &val) {
		TreeNode *ptr = _findNode(val);
		return ptr == nullptr ? false : ptr->val == val ? true : false;
	}
	
	string preorderTraversal() {
		string result;
		_preorderTraversalRecursive(m_root, result);
		return result;
	}
	
	string inorderTraversal() {
		string result;
		_inorderTraversalRecursive(m_root, result);
		return result;
	}
	
	string postorderTraversal() {
		string result;
		_postorderTraversalRecursive(m_root, result);
		return result;
	}
	
	~AVLTree() {
		clear();
	}
private:
	TreeNode *m_root;
	
	void _deleteTree(TreeNode *&root) {
		if (root == nullptr) {
			return;
		}
		_deleteTree(root->left);
		_deleteTree(root->right);
		delete root;
		root = nullptr;
	}
	
	TreeNode* _findNode(const int &val) {
		TreeNode *ptr;
		
		ptr = m_root;
		while (ptr != nullptr) {
			if (val == ptr->val) {
				return ptr;
			}
			if (val < ptr->val) {
				if (ptr->left != nullptr) {
					ptr = ptr->left;
				} else {
					return ptr;
				}
			} else {
				if (ptr->right != nullptr) {
					ptr = ptr->right;
				} else {
					return ptr;
				}
			}
		}
		return ptr;
	}
	
	void _preorderTraversalRecursive(const TreeNode  *root, string &result) {
		result.push_back('{');
		if (root == nullptr) {
			// '#' represents NULL.
			result.push_back('#');
		} else {
			result.append(to_string(root->val));
			_preorderTraversalRecursive(root->left, result);
			_preorderTraversalRecursive(root->right, result);
		}
		result.push_back('}');
	}
	
	void _inorderTraversalRecursive(const TreeNode  *root, string &result) {
		result.push_back('{');
		if (root == nullptr) {
			// '#' represents NULL.
			result.push_back('#');
		} else {
			_inorderTraversalRecursive(root->left, result);
			result.append(to_string(root->val));
			_inorderTraversalRecursive(root->right, result);
		}
		result.push_back('}');
	}
	
	void _postorderTraversalRecursive(const TreeNode  *root, string &result) {
		result.push_back('{');
		if (root == nullptr) {
			// '#' represents NULL.
			result.push_back('#');
		} else {
			_postorderTraversalRecursive(root->left, result);
			_postorderTraversalRecursive(root->right, result);
			result.append(to_string(root->val));
		}
		result.push_back('}');
	}
	
	TreeNode *_shiftLeft(TreeNode *root) {
		TreeNode *cur, *par;
		
		// root and root->left is guaranteed to be non-empty.
		par = root;
		cur = par->left;
		
		while (cur->right != nullptr) {
			par = cur;
			cur = cur->right;
		}
		root->val = cur->val;
		
		if (cur->left != nullptr) {
			return _shiftLeft(cur);
		}
		
		if (cur->right != nullptr) {
			return _shiftRight(cur);
		}
		
		if (cur == par->left) {
			delete par->left;
			par->left = nullptr;
		} else {
			delete par->right;
			par->right = nullptr;
		}

		return par;
	}

	TreeNode *_shiftRight(TreeNode *root) {
		TreeNode *cur, *par;
		
		// root and root->right is guaranteed to be non-empty.
		par = root;
		cur = par->right;
		
		while (cur->left != nullptr) {
			par = cur;
			cur = cur->left;
		}
		root->val = cur->val;
		
		if (cur->left != nullptr) {
			return _shiftLeft(cur);
		}
		
		if (cur->right != nullptr) {
			return _shiftRight(cur);
		}
		
		if (cur == par->left) {
			delete par->left;
			par->left = nullptr;
		} else {
			delete par->right;
			par->right = nullptr;
		}
		
		return par;
	}
	
	int _max(const int &x, const int &y) {
		return x > y ? x : y;
	}
	
	int _height(const TreeNode *ptr) {
		return ptr == nullptr ? 0 : ptr->height;
	}
	
	void _getHeight(TreeNode *ptr) {
		if (ptr == nullptr) {
			return;
		}
		ptr->height = _max(_height(ptr->left), _height(ptr->right)) + 1;
	}
	
	void _singleRotationLeft(TreeNode *cur) {
		// Subtree A is deeper than subtree B.
		// Before rotation:
		//     X
		//    / \
		//   Y   C
		//  / \
		// A   B
		// ----------
		// After rotation:
		//   Y
		//  / \
		// A   X
		//    / \
		//   B   C
		TreeNode *par = cur->parent;
		TreeNode *B;
		TreeNode *X, *Y;
		
		X = cur;
		Y = cur->left;
		B = Y->right;
		
		Y->right = X;
		X->parent = Y;
		X->left = B;
		if (B != nullptr) {
			B->parent = Y;
		}
		
		if (par == nullptr) {
			m_root = Y;
		} else if (par->left == cur) {
			par->left = Y;
		} else {
			par->right = Y;
		}
		Y->parent = par;
		
		_getHeight(X);
		_getHeight(Y);
		_getHeight(par);
	}
	
	void _singleRotationRight(TreeNode *cur) {
		// Subtree C is deeper than subtree B.
		// Before rotation:
		//   X
		//  / \
		// A   Y
		//    / \
		//   B   C
		// ----------
		// After rotation:
		//     Y
		//    / \
		//   X   C
		//  / \
		// A   B
		TreeNode *par = cur->parent;
		TreeNode *B;
		TreeNode *X, *Y;
		
		X = cur;
		Y = cur->right;
		B = Y->left;
		
		Y->left = X;
		X->parent = Y;
		X->right = B;
		if (B != nullptr) {
			B->parent = X;
		}
		
		if (par == nullptr) {
			m_root = Y;
		} else if (par->left == cur) {
			par->left = Y;
		} else {
			par->right = Y;
		}
		Y->parent = par;
		
		_getHeight(X);
		_getHeight(Y);
		_getHeight(par);
	}
	
	void _doubleRotationLeftRight(TreeNode *cur) {
		// Subtree Z is deeper than subtree A. Single rotation won't work, so let's use this one instead.
		// Before rotation:
		//     X
		//    / \
		//   Y   D
		//  / \
		// A   Z
		//    / \
		//   B   C
		// ----------
		// After rotation:
		//      Z
		//    /   \
		//   Y     X
		//  / \   / \
		// A   B C   D
		TreeNode *par = cur->parent;
		TreeNode *B, *C;
		TreeNode *X, *Y, *Z;
		
		X = cur;
		Y = X->left;
		Z = Y->right;
		B = Z->left;
		C = Z->right;
		
		Z->left = Y;
		Y->parent = Z;
		Z->right = X;
		X->parent = Z;
		Y->right = B;
		if (B != nullptr) {
			B->parent = X;
		}
		X->left = C;
		if (C != nullptr) {
			C->parent = X;
		}
		
		if (par == nullptr) {
			m_root = Z;
		} else if (par->left == cur) {
			par->left = Z;
		} else {
			par->right = Z;
		}
		Z->parent = par;
		
		_getHeight(X);
		_getHeight(Y);
		_getHeight(Z);
		_getHeight(par);
	}
	
	void _doubleRotationRightLeft(TreeNode *cur) {
		// Subtree Z is deeper than subtree D. Single rotation won't work, so let's use this one instead.
		// Before rotation:
		//   X
		//  / \
		// A   Y
		//    / \
		//   Z   D
		//  / \
		// B   C
		// ----------
		// After rotation:
		//      Z
		//    /   \
		//   X     Y
		//  / \   / \
		// A   B C   D
		TreeNode *par = cur->parent;
		TreeNode *B, *C;
		TreeNode *X, *Y, *Z;
		
		X = cur;
		Y = X->right;
		Z = Y->left;
		B = Z->left;
		C = Z->right;
		
		Z->left = X;
		X->parent = Z;
		Z->right = Y;
		Y->parent = Z;
		X->right = B;
		if (B != nullptr) {
			B->parent = X;
		}
		Y->left = C;
		if (C != nullptr) {
			C->parent = Y;
		}
		
		if (par == nullptr) {
			m_root = Z;
		} else if (par->left == cur) {
			par->left = Z;
		} else {
			par->right = Z;
		}
		Z->parent = par;
		
		_getHeight(X);
		_getHeight(Y);
		_getHeight(Z);
		_getHeight(par);
	}
};

int main()
{
	AVLTree avl;
	
	// test for single rotation
	avl.insertNode(1);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(2);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(3);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(4);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(5);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(6);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(7);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(8);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(9);
	cout << avl.preorderTraversal() << endl;
	cout << endl;

	// test for double rotation
	avl.clear();
	avl.insertNode(3);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(1);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(2);
	cout << avl.preorderTraversal() << endl;
	cout << endl;

	// test for deletion, left
	avl.clear();
	avl.insertNode(3);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(2);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(4);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(1);
	cout << avl.preorderTraversal() << endl;
	avl.deleteNode(3);
	cout << avl.preorderTraversal() << endl;
	avl.deleteNode(2);
	cout << avl.preorderTraversal() << endl;
	avl.deleteNode(4);
	cout << avl.preorderTraversal() << endl;
	cout << endl;
	
	// test for deletion, right
	avl.clear();
	avl.insertNode(2);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(1);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(3);
	cout << avl.preorderTraversal() << endl;
	avl.insertNode(4);
	cout << avl.preorderTraversal() << endl;
	avl.deleteNode(2);
	cout << avl.preorderTraversal() << endl;
	avl.deleteNode(1);
	cout << avl.preorderTraversal() << endl;
	avl.deleteNode(3);
	cout << avl.preorderTraversal() << endl;
	cout << endl;

	return 0;
}