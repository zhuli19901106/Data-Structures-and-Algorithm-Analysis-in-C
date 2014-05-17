// My implementation of queue with two stacks.
#include <stack>
using namespace std;

class Queue {
public:
	Queue() {}
	
	void push(int val) {
		s1.push(val);
	}
	
	void pop() {
		if (s2.empty()) {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		}
		s2.pop();
	}
	
	int size() {
		return s1.size() + s2.size();
	}
	
	bool empty() {
		return size() == 0;
	}
	
	int front() {
		if (s2.empty()) {
			while (!s1.empty()) {
				s2.push(s1.top());
				s1.pop();
			}
		}
		
		return s2.top();
	}
	
	int back() {
		if (s1.empty()) {
			while (!s2.empty()) {
				s1.push(s2.top());
				s2.pop();
			}
		}
		
		return s1.top();
	}
	
	~Queue() {
		while (!s1.empty()) {
			s1.pop();
		}
		while (!s2.empty()) {
			s2.pop();
		}
	}
private:
	stack<int> s1, s2;
};

int main()
{
	return 0;
}