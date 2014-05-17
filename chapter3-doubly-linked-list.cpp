// My implementation for doubly linked list.
struct ListNode {
	int val;
	ListNode *prev;
	ListNode *next;
	ListNode(int _val = 0): val(_val), next(nullptr), prev(nullptr) {};
};

class DoublyLinkedList {
public:
	DoublyLinkedList() {
		m_size = 0;
		m_head = nullptr;
		m_tail = nullptr;
	}
	
	void insertFront(int val) {
		if (m_size == 0) {
			m_head = m_tail = new ListNode(val);
		} else {
			ListNode *ptr = new ListNode(val);
			ptr->next = m_head;
			m_head->prev = ptr;
			m_head = ptr;
		}
		++m_size;
	}
	
	void insertBack(int val) {
		if (m_size == 0) {
			m_head = m_tail = new ListNode(val);
		} else {
			m_tail->next = new ListNode(val);
			m_tail->next->prev = m_tail;
			m_tail = m_tail->next;
		}
		++m_size;
	}
	
	void insertNode(int pos, int val) {
		int i;
		
		if (i <= 0) {
			insertFront(val);
		} else if (i >= m_size) {
			insertBack(val);
		} else {
			ListNode *ptr1, *ptr2;
			
			ptr1 = m_head;
			for (i = 0; i < pos - 1; ++i) {
				ptr1 = ptr1->next;
			}
			ptr2 = new ListNode(val);
			ptr2->next = ptr1->next;
			ptr1->next->prev = ptr2;
			ptr1->next = ptr2;
			ptr2->prev = ptr1;
			++m_size;
		}
	}
	
	void deleteNode(int pos) {
		if (pos < 0 || pos > m_size - 1) {
			return;
		}
		
		ListNode *ptr1, *ptr2;
		if (pos == 0) {
			ptr1 = m_head;
			if (m_size == 1) {
				m_head = m_tail = nullptr;
			} else {
				m_head = m_head->next;
				m_head->prev = nullptr;
			}
			delete ptr1;
		} else {
			ptr1 = m_head;
			for (int i = 0; i < pos - 1; ++i) {
				ptr1 = ptr1->next;
			}
			ptr2 = ptr1->next;
			ptr1->next = ptr2->next;
			if (ptr2->next == nullptr) {
				m_tail = ptr1;
			} else {
				ptr2->next->prev = ptr1;
			}
			delete ptr2;
		}
		--m_size;
	}
	
	void updateNode(int pos, int val) {
		if (pos < 0 || pos > m_size - 1) {
			return;
		}
		
		ListNode *ptr = m_head;
		for (int i = 0; i < pos; ++i) {
			ptr = ptr->next;
		}
		ptr->val = val;
	}
	
	ListNode *findNode(int val) {
		ListNode *ptr = m_head;
		while (ptr != nullptr) {
			if (ptr->val == val) {
				return ptr;
			}
			ptr = ptr->next;
		}
		
		return nullptr;
	}
	
	~DoublyLinkedList() {
		ListNode *ptr = m_head;
		while (m_head != nullptr) {
			m_head = m_head->next;
			delete ptr;
			ptr = m_head;
		}
		m_head = m_tail = nullptr;
	}
private:
	int m_size;
	ListNode *m_head;
	ListNode *m_tail;
};

int main()
{
	return 0;
}