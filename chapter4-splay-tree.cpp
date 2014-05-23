// My implementation for splay tree, modified from my avl tree.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	TreeNode(int _val): val(_val), left(nullptr), right(nullptr), parent(nullptr) {};
};

class SplayTree {
public:
	SplayTree() {
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
			ptr = ptr->left;
		} else {
			ptr->right = new TreeNode(val);
			ptr->right->parent = ptr;
			ptr = ptr->right;
		}
		_splayNode(ptr);
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
		// the node is splayed to the root, cur must be m_root.
		par = cur->parent;
		
		TreeNode *ptr;
		
		if (cur->left != nullptr) {
			ptr = _shiftLeft(cur);
			return;
		}
	
		if (cur->right != nullptr) {
			ptr = _shiftRight(cur);
			return;
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
	
	~SplayTree() {
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
		if (ptr->val == val) {
			_splayNode(ptr);
			return m_root;
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
	}
	
	void _singleRotationRight(TreeNode *cur) {
		// Subtree A is deeper than subtree B.
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
	}
	
	void _doubleRotationLeftLeft(TreeNode *cur) {
		// This is only for splay tree, not AVL.
		// Before rotation:
		//       X
		//      / \
		//     Y   D
		//    / \
		//   Z   C
		//  / \
		// A   B
		// ----------
		// After rotation:
		//   Z
		//  / \
		// A   Y
		//    / \
		//   B   X
		//      / \
		//     C   D
		TreeNode *par = cur->parent;
		TreeNode *B, *C;
		TreeNode *X, *Y, *Z;
		
		X = cur;
		Y = X->left;
		Z = Y->left;
		B = Z->right;
		C = Y->right;
		
		Z->right = Y;
		Y->parent = Z;
		Y->right = X;
		X->parent = Y;
		Y->left = B;
		if (B != nullptr) {
			B->parent = Y;
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
	}
	
	void _doubleRotationRightRight(TreeNode *cur) {
		// This is only for splay tree, not AVL.
		// Before rotation:
		//   X
		//  / \
		// A   Y
		//    / \
		//   B   Z
		//      / \
		//     C   D
		// ----------
		// After rotation:
		//       Z
		//      / \
		//     Y   D
		//    / \
		//   X   C
		//  / \
		// A   B
		TreeNode *par = cur->parent;
		TreeNode *B, *C;
		TreeNode *X, *Y, *Z;
		
		X = cur;
		Y = X->right;
		Z = Y->right;
		B = Y->left;
		C = Z->left;
		
		Z->left = Y;
		Y->parent = Z;
		Y->left = X;
		X->parent = Y;
		X->right = B;
		if (B != nullptr) {
			B->parent = X;
		}
		Y->right = C;
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
	}
	
	void _splayNode(TreeNode *cur) {
		if (m_root == nullptr || cur == nullptr) {
			return;
		}
		
		TreeNode *par, *grand;
		
		while (cur != nullptr && cur->parent != nullptr) {
			par = cur->parent;
			grand = par->parent;
			if (grand == nullptr) {
				if (par->left == cur) {
					_singleRotationLeft(par);
				} else {
					_singleRotationRight(par);
				}
				return;
			}
			if (grand->left == par) {
				if (par->left == cur) {
					_doubleRotationLeftLeft(grand);
				} else {
					_doubleRotationLeftRight(grand);
				}
			} else {
				if (par->left == cur) {
					_doubleRotationRightLeft(grand);
				} else {
					_doubleRotationRightRight(grand);
				}
			}
		}
	}
};

int main()
{
	SplayTree tree;
	
	tree.clear();
	tree.insertNode(1);
	cout << tree.preorderTraversal() << endl;
	tree.insertNode(2);
	cout << tree.preorderTraversal() << endl;
	tree.insertNode(3);
	cout << tree.preorderTraversal() << endl;
	tree.insertNode(4);
	cout << tree.preorderTraversal() << endl;
	tree.insertNode(5);
	cout << tree.preorderTraversal() << endl;
	tree.insertNode(6);
	cout << tree.preorderTraversal() << endl;
	// until now the tree is skewed.
	// look at this step.
	tree.insertNode(-1);
	cout << tree.preorderTraversal() << endl;
	tree.deleteNode(6);
	cout << tree.preorderTraversal() << endl;
	tree.deleteNode(5);
	cout << tree.preorderTraversal() << endl;
	tree.deleteNode(4);
	cout << tree.preorderTraversal() << endl;
	tree.deleteNode(3);
	cout << tree.preorderTraversal() << endl;
	tree.deleteNode(2);
	cout << tree.preorderTraversal() << endl;
	tree.deleteNode(1);
	cout << tree.preorderTraversal() << endl;

	return 0;
}