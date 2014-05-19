// My implementation for binary tree.
#include <string>
#include <vector>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int _val): val(_val), left(nullptr), right(nullptr) {};
};

// One of the (de)serialization method I wrote.
// Here is a serialization sample for this piece of code: {3,1,#,#,10,6,#,#,11,#,14,#,#}
//   3
//  / \
// 1  10
//   /  \
//  6   11
//        \
//        14
class BinaryTreeSerializer {
public:
	string serialize(TreeNode *root) {
		string res = "{";
		
		// preorder traversal
		serializeTraversal(root, res);
		res[res.length() - 1] = '}';
		
		return res;
	};
	
	TreeNode *deserialize(string s) {
		vector<string> data;
		int i, j, len;
		
		len = (int)s.length();
		i = 1;
		while (true) {
			j = i + 1;
			while (s[j] != ',' && s[j] != '}') {
				++j;
			}
			data.push_back(s.substr(i, j - i));
			i = j + 1;
			if (i >= len) {
				break;
			}
		}
		
		int iter = 0;
		TreeNode *root = nullptr;
		
		// preorder traversal
		deserializeTraversal(data, root, iter);
		
		return root;
	};
private:
	static char ss[10];
	
	void serializeTraversal(TreeNode *root, string &res) {
		if (root == nullptr) {
			res += "#,";
		} else {
			sprintf(ss, "%d", root->val);
			res += string(ss);
			res.push_back(',');
			serializeTraversal(root->left, res);
			serializeTraversal(root->right, res);
		}
	};
	
	void deserializeTraversal(vector<string> &data, TreeNode *&root, int &iter) {
		++iter;
		if (data[iter - 1] == "#") {
			root = nullptr;
		} else {
			int val;
			
			sscanf(data[iter - 1].c_str(), "%d", &val);
			root = new TreeNode(val);
			deserializeTraversal(data, root->left, iter);
			deserializeTraversal(data, root->right, iter);
		}
	};
};

int main()
{
	return 0;
}