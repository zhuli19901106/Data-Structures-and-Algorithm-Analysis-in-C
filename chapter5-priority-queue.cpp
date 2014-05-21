// My implementation for priority queue using binary heap.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class T>
class PriorityQueue {
public:
	PriorityQueue() {
		m_data.push_back(0);
	}
	
	PriorityQueue(const vector<T> &data) {
		m_data.push_back(0);
		for (size_t i = 0; i < data.size(); ++i) {
			m_data.push_back(data[i]);
		}
		_makeHeap();
	}
	
	bool empty() {
		return m_data.size() == 1;
	}
	
	size_t size() {
		return m_data.size() - 1;
	}
	
	T top() {
		return m_data[1];
	}
	
	void push(const T &val) {
		m_data.push_back(val);
		
		int n = size();
		int i = n;
		
		while (i > 1) {
			if (m_data[i / 2] < m_data[i]) {
				_swap(m_data[i / 2], m_data[i]);
				i /= 2;
			} else {
				break;
			}
		}
	}
	
	void pop() {
		int n = size();
		m_data[1] = m_data[n];
		m_data.pop_back();
		--n;
		
		int i = 1;
		T max_val;
		while (i * 2 <= n) {
			max_val = i * 2 == n ? m_data[i * 2] : _max(m_data[i * 2], m_data[i * 2 + 1]);
			if (m_data[i] < max_val) {
				if (max_val == m_data[i * 2] || i * 2 == n) {
					_swap(m_data[i], m_data[i * 2]);
					i = i * 2;
				} else {
					_swap(m_data[i], m_data[i * 2 + 1]);
					i = i * 2 + 1;
				}
			} else {
				break;
			}
		}
	}
	
	void clear() {
		m_data.resize(1);
	}

	~PriorityQueue() {
		m_data.clear();
	}
private:
	vector<T> m_data;
	
	T _max(const T &x, const T &y) {
		return x > y ? x : y;
	}
	
	void _swap(T &x, T &y) {
		T tmp;
		
		tmp = x;
		x = y;
		y = tmp;
	}
	
	void _makeHeap() {
		int n = size();
		int i, j;
		T max_val;
		
		for (j = n / 2; j >= 1; --j) {
			i = j;
			while (i * 2 <= n) {
				max_val = i * 2 == n ? m_data[i * 2] : _max(m_data[i * 2], m_data[i * 2 + 1]);
				if (m_data[i] < max_val) {
					if (max_val == m_data[i * 2] || i * 2 == n) {
						_swap(m_data[i], m_data[i * 2]);
						i = i * 2;
					} else {
						_swap(m_data[i], m_data[i * 2 + 1]);
						i = i * 2 + 1;
					}
				} else {
					break;
				}
			}
		}

		n = size();
		cout << '[';
		for (int i = 1; i <= n; ++i) {
			cout << m_data[i] << ' ';
		}
		cout << ']' << endl;
	}
};

int main()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	PriorityQueue<int> pq(v);
	string s;
	int n;
	
	while (cin >> s) {
		if (s == "push") {
			cin >> n;
			pq.push(n);
		} else if (s == "pop") {
			pq.pop();
		} else if (s == "top") {
			cout << pq.top() << endl;
		} else if (s == "end") {
			while (!pq.empty()) {
				pq.pop();
			}
			break;
		}
	}
	
	return 0;
}