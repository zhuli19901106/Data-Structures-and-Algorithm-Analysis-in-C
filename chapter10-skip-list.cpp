// My implementation for skip list.
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

template <class TKey>
struct ListNode {
	TKey *key;
	ListNode *down;
	ListNode *next;
	
	ListNode(): key(nullptr), down(nullptr), next(nullptr) {}
};

template <class TKey>
class SkipList {
public:
	SkipList() {
		m_root = new ListNode<TKey>();
		m_size = 0;
		m_level = 0;
	}
	
	bool contains(const TKey &key) {
		if (m_size == 0) {
			return false;
		}
		
		ListNode<TKey> *ptr = m_root;
		while (true) {
			if (ptr->next != nullptr) {
				if (key < *(ptr->next->key)) {
					if (ptr->down != nullptr) {
						ptr = ptr->down;
					} else {
						return false;
					}
				} else if (key > *(ptr->next->key)) {
					ptr = ptr->next;
				} else {
					return true;
				}
			} else {
				if (ptr->down != nullptr) {
					ptr = ptr->down;
				} else {
					return false;
				}
			}
		}
	}
	
	void insert(const TKey &key) {
		if (contains(key)) {
			return;
		}
		
		ListNode<TKey> *ptr;
		int new_level = _randomLevel();
		
		if (new_level > m_level) {
			// Extra levels need to be added.
			for (int i = m_level; i < new_level; ++i) {
				ptr = new ListNode<TKey>();
				ptr->down = m_root;
				m_root = ptr;
			}
			m_level = new_level;
		}
		
		int lvl = m_level;
		ListNode<TKey> *last, *cur;
		
		ptr = m_root;
		last = cur = nullptr;
		while (true) {
			if (ptr->next != nullptr) {
				if (key < *(ptr->next->key)) {
					if (lvl <= new_level) {
						cur = new ListNode<TKey>();
						if (last == nullptr) {
							cur->key = new TKey(key);
						} else {
							cur->key = last->key;
							last->down = cur;
						}
						last = cur;
						cur->next = ptr->next;
						ptr->next = cur;
					}
					
					if (ptr->down != nullptr) {
						ptr = ptr->down;
						--lvl;
					} else {
						break;
					}
				} else if (key > *(ptr->next->key)) {
					ptr = ptr->next;
				} else {
					break;
				}
			} else {
				if (lvl <= new_level) {
					cur = new ListNode<TKey>();
					if (last == nullptr) {
						cur->key = new TKey(key);
					} else {
						cur->key = last->key;
						last->down = cur;
					}
					last = cur;
					cur->next = ptr->next;
					ptr->next = cur;
				}
				
				if (ptr->down != nullptr) {
					ptr = ptr->down;
					--lvl;
				} else {
					break;
				}
			}
		}
		++m_size;
	}
	
	void erase(const TKey &key) {
		if (!contains(key)) {
			return;
		}
		
		ListNode<TKey> *ptr = m_root;
		ListNode<TKey> *cur;
		while (true) {
			if (ptr->next != nullptr) {
				if (key < *(ptr->next->key)) {
					if (ptr->down != nullptr) {
						ptr = ptr->down;
					} else {
						break;
					}
				} else if (key > *(ptr->next->key)) {
					ptr = ptr->next;
				} else {
					cur = ptr->next;
					ptr->next = cur->next;
					if (ptr->down != nullptr) {
						delete cur;
						ptr = ptr->down;
					} else {
						delete cur->key;
						delete cur;
						break;
					}
				}
			} else {
				if (ptr->down != nullptr) {
					ptr = ptr->down;
				} else {
					break;
				}
			}
		}
		--m_size;

		ptr = m_root;
		while (ptr->next == nullptr) {
			// Empty levels are removed.
			if (ptr->down == nullptr) {
				break;
			} else {
				m_root = m_root->down;
				delete ptr;
				ptr = m_root;
				--m_level;
			}
		}
	}
	
	size_t size() {
		return m_size;
	}
	
	void clear() {
		_clearUp();
		
		m_root = new ListNode<TKey>();
		m_size = 0;
		m_level = 0;
	}

	void debugPrint() {
		ListNode<TKey> *p1, *p2;

		cout << '{' << endl;
		p1 = m_root;
		while (p1 != nullptr) {
			p2 = p1->next;
			cout << "    ";
			while (p2 != nullptr) {
				cout << *(p2->key) << ' ';
				p2 = p2->next;
			}
			cout << endl;
			p1 = p1->down;
		}
		cout << '}' << endl;
	}

	~SkipList() {
		_clearUp();
	}
private:
	int m_level;
	int m_size;
	ListNode<TKey> *m_root;
	
	void _clearUp() {
		ListNode<TKey> *head = m_root;
		ListNode<TKey> *p1, *p2;
		
		while (head != nullptr) {
			p1 = head;
			head = head->down;
			while (p1 != nullptr) {
				p2 = p1->next;
				if (p1->key != nullptr && p1->down == nullptr) {
					delete p1->key;
				}
				delete p1;
				p1 = p2;
			}
		}
	}
	
	int _randomLevel() {
		int level = 0;
		
		while (rand() & 1) {
			++level;
		}
		
		return level;
	}
};

int main()
{
	srand((unsigned int)time(nullptr));
	string s;
	SkipList<int> sl;
	int key;
	
	while (cin >> s) {
		if (s == "i") {
			cin >> key;
			sl.insert(key);
		}  else if (s == "c") {
			cin >> key;
			cout << (sl.contains(key) ? "Yes" : "No") << endl;
		} else if (s == "e") {
			cin >> key;
			sl.erase(key);
		} else if (s == "cl") {
			sl.clear();
		}
		sl.debugPrint();
	}
	sl.clear();
	
	return 0;
}