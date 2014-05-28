// My implementation for hash set.
#include <iostream>
#include <string>
#include <vector>
using namespace std;

template <class KeyType>
struct HashFunctor {
	size_t operator () (const KeyType &key) {
		const char *ptr = (const char *)&key;
		size_t size = sizeof(key);
		size_t result;
		
		result = 0;
		for (size_t i = 0; i < size; ++i) {
			result = (result << 1) ^ *(ptr + i);
		}
		
		return result;
	}
};

template<>
struct HashFunctor<string> {
	size_t operator() (const string &key) {
		size_t size = key.length();
		size_t result;
		
		result = 0;
		for (size_t i = 0; i < size; ++i) {
			result = (result << 1) ^ key[i];
		}
		
		return result;
	}
};

template <class KeyType>
class HashSet {
public:
	HashSet() {
		m_size = 0;
		m_capacity = MIN_BUCKET_NUM;
		m_data.resize(m_capacity);
		m_occupied.resize(m_capacity);
		
		for (size_t i = 0; i < m_capacity; ++i) {
			m_occupied[i] = false;
		}
	}
	
	void insert(const KeyType& key) {
		size_t h = _findKey(key);
		
		if (m_occupied[h]) {
			// value already inserted
			return;
		}
		
		m_data[h] = key;
		m_occupied[h] = true;
		++m_size;
		
		if (load_factor() >= 0.5) {
			_rehash(m_capacity * 2 + 1);
		}
	}
	
	void remove(const KeyType& key) {
		size_t h = _findKey(key);
		
		if (!m_occupied[h]) {
			// value not found
			return;
		}
		
		m_occupied[h] = false;
		--m_size;
		
		if (m_capacity > MIN_BUCKET_NUM && load_factor() <= 0.05) {
			_rehash(m_capacity / 2);
		}
	}
	
	void update(const KeyType& old_key, const KeyType& new_key) {
		remove(old_key);
		insert(new_key);
	}
	
	bool find(const KeyType& key) {
		size_t h = _findKey(key);
		
		return m_occupied[h];
	}
	
	size_t size() {
		return m_size;
	}
	
	void clear() {
		m_size = 0;
		for (size_t i = 0; i < m_capacity; ++i) {
			m_occupied[i] = false;
		}
	}
	
	double load_factor() {
		return (double)m_size / (double)m_capacity;
	}
	
	~HashSet() {
		m_data.clear();
		m_occupied.clear();
	}
private:
	static const size_t MIN_BUCKET_NUM = 5;
	size_t m_size;
	size_t m_capacity;
	vector<KeyType> m_data;
	vector<bool> m_occupied;
	HashFunctor<KeyType> m_hasher;
	
	size_t _findKey(const KeyType& key) {
		size_t hash_value = m_hasher(key);
		size_t h;
		size_t i;
		
		i = 0;
		while (i < m_capacity) {
			// only works for linear probing
			// if applied to quadratic probing, the number of buckets must be carefully chosen.
			h = (hash_value + _probeFunction(i)) % m_capacity;
			if (!m_occupied[h] || key == m_data[h]) {
				return h;
			} else {
				++i;
			}
		}
		
		return m_capacity;
	}

	size_t _probeFunction(int i) {
		return i;
	}
	
	void _rehash(size_t new_capacity) {
		vector<KeyType> old_data;
		vector<bool> old_occupied;
		
		old_data = m_data;
		old_occupied = m_occupied;
		
		m_data.resize(new_capacity);
		m_occupied.resize(new_capacity);
		
		size_t i;
		size_t old_capacity;
		
		m_size = 0;
		old_capacity = m_capacity;
		m_capacity = new_capacity;
		for (i = 0; i < m_capacity; ++i) {
			m_occupied[i] = false;
		}

		for (i = 0; i < old_capacity; ++i) {
			if (old_occupied[i]) {
				insert(old_data[i]);
			}
		}
		
		old_data.clear();
		old_occupied.clear();
	}
};

int main()
{
	typedef long long KeyType;
	HashSet<KeyType> hash;
	string cmd;
	KeyType data;
	
	while (cin >> cmd) {
		if (cmd == "insert") {
			cin >> data;
			hash.insert(data);
		} else if (cmd == "remove") {
			cin >> data;
			hash.remove(data);
		} else if (cmd == "find") {
			cin >> data;
			cout <<  (hash.find(data) ? "true" : "false") << endl;
		} else if (cmd == "clear") {
			hash.clear();
		} else if (cmd == "size") {
			cout << hash.size() << endl;
		} else if (cmd == "lambda") {
			cout << hash.load_factor() << endl;
		} else if (cmd == "end") {
			break;
		}
	}
	hash.clear();

	return 0;
}