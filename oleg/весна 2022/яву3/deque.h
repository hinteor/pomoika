#pragma once
#include <iostream>
#include <functional>
using namespace std;
template <typename T>
class deque {

public:
	struct Node {
		Node() {
			next = nullptr;
			prev = nullptr;
		}
		~Node() = default;
		T data;
		Node* next;
		Node* prev;
	};
	void init(const T& data) {
		m_start = new Node();
		m_start->data = data;
		m_end = m_start;
	}
	void remove_node(Node* node) {
		Node* prev = node->prev;
		Node* next = node->next;
		if (prev != nullptr) prev->next = next;
		if (next != nullptr) next->prev = prev;
		if (node == m_start) m_start = next;
		if (node == m_end) m_end = prev;
		delete node;
		m_size--;
	}
	Node* m_start;
	Node* m_end;
	size_t m_size;
	void print(T elem, ostream out) {
		out << elem << ' ';
	}
	T getData() {
		return m_end->data;
	}
	deque() {
		m_start = m_end = nullptr;
		m_size = 0;
	}
	~deque() { clear(); }

	T pop_front() {
		T tmp;
		if (!m_start) return 0;
		if (m_start->next) {
			Node* next = m_start->next;
			next->prev = nullptr;
			tmp = m_start->data;
			delete m_start;
			m_start = next;
		}
		else {
			tmp = m_start->data;
			delete m_start;
			m_start = m_end = nullptr;
		}
		m_size--;
		return tmp;
	}
	void push_back(const T data) {
		if (m_end) {
			Node* new_node = new Node();
			new_node->data = data;
			new_node->prev = m_end;
			m_end->next = new_node;
			m_end = new_node;
		}
		else {
			init(data);
		}
		m_size++;
	}
	T pop_back() {
		T tmp;
		if (!m_end) return 0;
		if (m_end->prev) {
			Node* prev = m_end->prev;
			prev->next = nullptr;
			tmp = m_end->data;
			delete m_end;
			m_end = prev;
		}
		else {
			tmp = m_end->data;
			delete m_end;
			m_start = m_end = nullptr;
		}
		m_size--;
		return tmp;
	}

	void sort() {
		if (!m_start) return;
		Node* tmp = m_start;
		T min = tmp->data;
		while (tmp) {
			if (tmp->data < min)
			{
				min = tmp->data;
			}
			tmp = tmp->next;
		}
		tmp = m_start;
		while (tmp) {
			tmp->data = tmp->data - min;
			tmp = tmp->next;
		}

	}

	void remove_one(std::function<bool(const T&)> cnd) {
		Node* tmp = m_start;
		while (tmp) {
			if (cnd(tmp->data)) {
				remove_node(tmp);
				return;
			}
			tmp = tmp->next;
		}
	}
	void remove_all(std::function<bool(const T&)> cnd) {
		Node* tmp = m_start;
		while (tmp) {
			if (cnd(tmp->data)) {
				Node* bck = nullptr;
				if (tmp->prev)
					bck = tmp->prev;
				else if (tmp->next)
					bck = tmp->next;
				remove_node(tmp);
				if (!bck) return;
				tmp = bck;
			}
			else {
				tmp = tmp->next;
			}
		}
	}

	void clear() {
		if (!m_start) return;
		if (m_start == m_end) {
			delete m_start;
		}
		else {
			Node* tmp = m_start;
			while (tmp != m_end) {
				Node* next = tmp->next;
				delete tmp;
				tmp = next;
			}
		}
		m_size = 0;
		m_start = m_end = nullptr;
	}

	void for_each(std::function<void(T&)> fun) {
		Node* tmp = m_start;
		while (tmp) {
			fun(tmp->data);
			tmp = tmp->next;
		}
	}

	inline size_t size() const noexcept { return m_size; }

	bool IsEmpty() {
		if (m_size = 0) {
			return true;
		}
		else
		{
			return false;
		}
	}

	deque& operator=(deque<T>& other) noexcept {
		clear();
		Node* tmp = other.m_start;
		while (tmp) {
			push_back(tmp->data);
			tmp = tmp->next;
		}
		return *this;
	}

	friend ostream& operator << (ostream& out, deque& other)
	{//------

		Node* tmp = other.m_start;
		while (tmp) {
			out << "----------------" << endl;
			out << tmp->data << endl;
			tmp = tmp->next;
		}
		return out;
	}
	friend istream& operator >> (istream& in, deque& other) {
		system("CLS");
		cout << "Введите кол-во элементов в очереди : ";
		size_t newSize;
		in >> newSize;
		T p;
		for (int i = 0; i < newSize; i++)
		{
			cout << "Введите " << i + 1 << " элемент : ";
			in >> p;
			other.push_back(p);
			cout << endl;
		}
		return in;
	}


};
