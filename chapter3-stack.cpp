// My implementation of stack.
class Stack {
public:
	Stack() {
		m_capacity = 1;
		m_size = 0;
		m_data = new int[m_capacity];
	}
	
	void push(int val) {
		if (m_size + 1 >= m_capacity) {
			resize(2 * m_capacity);
		}
		m_data[m_size++] = val;
	}
	
	void pop() {
		if (m_size > 0) {
			--m_size;
		}
	}
	
	int top() {
		return m_data[m_size - 1];
	}
	
	int size() {
		return m_size;
	}
	
	bool empty() {
		return m_size == 0;
	}
	
	~Stack() {
		delete m_data;
	}
private:
	int *m_data;
	int m_capacity;
	int m_size;
	
	void resize(int new_capacity) {
		if (new_capacity <= m_capacity) {
			return;
		}
		int *new_data = new int[new_capacity];
		
		for (int i = 0; i < m_size; ++i) {
			new_data[i] = m_data[i];
		}
		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
	}
};

int main()
{
	return 0;
}