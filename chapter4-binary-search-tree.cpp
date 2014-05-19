// My implementation for binary search tree.
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int _val): val(_val), left(nullptr), right(nullptr) {};
};

class BinarySearchTree {
public:
	BinarySearchTree() {
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
		if (val < ptr->val) {
			ptr->left = new TreeNode(val);
		} else if (val > ptr->val) {
			ptr->right = new TreeNode(val);
		}
	}
	
	void deleteNode(const int &val) {
		if (m_root == nullptr) {
			return;
		}
		
		TreeNode *par, *cur;
		
		par = nullptr;
		cur = m_root;
		while (cur != nullptr) {
			if (val < cur->val) {
				par = cur;
				cur = cur->left;
			} else if (val > cur->val) {
				par = cur;
				cur = cur->right;
			} else {
				break;
			}
		}
		
		if (cur == nullptr) {
			return;
		}
		
		if (cur->left != nullptr) {
			_shiftLeft(cur);
			return;
		}
		
		if (cur->right != nullptr) {
			_shiftRight(cur);
			return;
		}
		
		if (val < par->val) {
			delete par->left;
			par->left = nullptr;
		} else {
			delete par->right;
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
	
	~BinarySearchTree() {
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
			if (val < ptr->val) {
				if (ptr->left != nullptr) {
					ptr = ptr->left;
				} else {
					return ptr;
				}
			} else if (val > ptr->val) {
				if (ptr->right != nullptr) {
					ptr = ptr->right;
				} else {
					return ptr;
				}
			} else {
				return ptr;
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
	
	void _shiftLeft(TreeNode *root) {
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
			_shiftLeft(cur);
			return;
		}
		
		if (cur->right != nullptr) {
			_shiftRight(cur);
			return;
		}
		
		if (cur->val < par->val) {
			delete par->left;
			par->left = nullptr;
		} else {
			delete par->right;
			par->right = nullptr;
		}
	}

	void _shiftRight(TreeNode *root) {
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
			_shiftLeft(cur);
			return;
		}
		
		if (cur->right != nullptr) {
			_shiftRight(cur);
			return;
		}
		
		if (cur->val < par->val) {
			delete par->left;
			par->left = nullptr;
		} else {
			delete par->right;
			par->right = nullptr;
		}
	}
};

int main()
{
	BinarySearchTree bst;
	
	bst.insertNode(5);
	bst.insertNode(3);
	bst.insertNode(14);
	bst.insertNode(2);
	bst.insertNode(4);
	bst.insertNode(9);
	bst.insertNode(15);
	bst.insertNode(7);
	bst.insertNode(8);
	cout << bst.preorderTraversal() << endl;
	bst.deleteNode(14);
	cout << bst.preorderTraversal() << endl;
	bst.deleteNode(5);
	cout << bst.preorderTraversal() << endl;
	
	return 0;
}