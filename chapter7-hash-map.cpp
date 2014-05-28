// 8.10 Design a hash table. Handle conflicts with chaining(linked lists).
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HashMap {
public:
	HashMap() {
		_buckets.resize(_bucket_num);
		int i;
		
		for (i = 0; i < _bucket_num; ++i) {
			_buckets[i] = nullptr;
		}
	};
	
	bool contains(int key) {
		key = (key > 0) ? key : -key;
		key = key % _bucket_num;
		LinkedList *ptr = _buckets[key];
		
		while (ptr != nullptr) {
			if (ptr->key == key) {
				return true;
			}
		}
		
		return false;
	};
	
	int& operator [] (int key) {
		key = (key > 0) ? key : -key;
		key = key % _bucket_num;
		LinkedList *ptr = _buckets[key];
		
		if (ptr == nullptr) {
			_buckets[key] = new LinkedList(key);
			return _buckets[key]->val;
		}
		
		LinkedList *ptr2 = ptr->next;
		if (ptr->key == key) {
			return ptr->val;
		}
		
		while (ptr2 != nullptr) {
			if (ptr2->key == key) {
				return ptr2->val;
			} else {
				ptr = ptr->next;
				ptr2 = ptr2->next;
			}
		}
		ptr->next = new LinkedList(key);
		ptr = ptr->next;
		return ptr->val;
	}
	
	void erase(int key) {
		key = (key > 0) ? key : -key;
		key = key % _bucket_num;
		LinkedList *ptr = _buckets[key];
		
		if (ptr == nullptr) {
			return;
		} else if (ptr->next == nullptr) {
			if (ptr->key == key) {
				delete _buckets[key];
				_buckets[key] = nullptr;
			}
			return;
		}
		
		if (ptr->key == key) {
			_buckets[key] = ptr->next;
			delete ptr;
			return;
		}
		
		LinkedList *ptr2;
		ptr2 = ptr->next;
		
		while (ptr2 != nullptr) {
			if (ptr2->key == key) {
				ptr->next = ptr2->next;
				delete ptr2;
				return;
			} else {
				ptr = ptr->next;
				ptr2 = ptr2->next;
			}
		}
	}
	
	~HashMap() {
		int i;
		LinkedList *ptr;
		
		for (i = 0; i < _bucket_num; ++i) {
			ptr = _buckets[i];
			while (ptr != nullptr) {
				ptr = ptr->next;
				delete _buckets[i];
				_buckets[i] = ptr;
			}
		}
		_buckets.clear();
	}
private:
	struct LinkedList {
		int key;
		int val;
		LinkedList *next;
		LinkedList(int _key = 0, int _val = 0): key(_key), val(_val), next(nullptr) {};
	};

	static const int _bucket_num = 10000;
	vector<LinkedList *> _buckets;
};

int main()
{
	HashMap hm;
	string cmd;
	int op1, op2;
	
	while (cin >> cmd) {
		if (cmd == "set") {
			cin >> op1 >> op2;
			hm[op1] = op2;
		} else if (cmd == "get") {
			cin >> op1;
			cout << hm[op1] << endl;
		} else if (cmd == "find") {
			cin >> op1;
			cout << (hm.contains(op1) ? "true" : "false") << endl;
		}
	}
	
	return 0;
}