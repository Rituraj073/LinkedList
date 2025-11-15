#pragma once
#include "SingleNode.h"

template <class T>
class SingleLL
{
private:
	SingleNode<T> *head;

public:
	SingleLL() : head(nullptr) {}
	SingleLL(const T& value) : head(new SingleNode<T>(value, nullptr)) {}
	~SingleLL() { clear(); }

	// Deepcopy and Assignment ------------------
	SingleLL(const SingleLL& other)
	{
		if (!other.head)
		{
			head = nullptr;
			return;
		}
		head = new SingleNode<T>(other.head->val, nullptr);
		SingleNode<T>* tail = head;
		SingleNode<T>* cur = other.head->next;
		while (cur)
		{
			SingleNode<T>* newNode = new SingleNode<T>(cur->val, nullptr);
			tail->next = newNode;
			tail = newNode;
			cur = cur->next;
		}
	}
	SingleLL& operator=(const SingleLL& other)
	{
		if (this == &other) return *this;
		clear();
		if (!other.head)
		{
			head = nullptr;
			return *this;
		}
		head = new SingleNode<T>(other.head->val, nullptr);
		SingleNode<T>* tail = head;
		SingleNode<T>* cur = other.head->next;
		while (cur)
		{
			SingleNode<T>* newNode = new SingleNode<T>(cur->val, nullptr);
			tail->next = newNode;
			tail = newNode;
			cur = cur->next;
		}
		return *this;
	}

	// Move Deepcopy and Assignment ------------------
	SingleLL(SingleLL&& other) noexcept
	{
		head = other.head;
		other.head = nullptr;
	}
	SingleLL& operator=(SingleLL&& other) noexcept
	{
		if (this == &other) return *this;
		clear();
		head = other.head;
		other.head = nullptr;
		return *this;
	}

	// clear all node
	void clear()
	{
		SingleNode<T>* cur = head;
		while (cur)
		{
			SingleNode<T>* nextnode = cur->next;
			delete cur;
			cur = nextnode;
		}
		head = nullptr;
	}

	// Implementaion
	void push_front(const T& value);
	void push_back(const T& value);
	void pop_front();
	void pop_back();
	void insert_at(int index, const T& value);
	void remove_at(int index);
	int size() const;
	bool search(const T& value) const;
	void remove_value(const T& value);

	// Advance feature
	void reverse();
	T middle_element();
	T nth_from_begin(int n);
	T nth_from_end(int n);
	bool detect_cycle(); // Floyd algorithm
	void sort();
	
	template <class U>
	friend std::ostream& operator<<(std::ostream& out, const SingleLL<U>& sll);

	class Iterator
	{
		SingleNode<T>* ptr;
	public:
		Iterator(SingleNode<T>* p = nullptr) : ptr(p) {}

		T& operator*() { return ptr->val; }
		T* operator->() { return &(ptr->val); }

		Iterator& operator++() {
			if (ptr) ptr = ptr->next;
			return *this;
		}

		bool operator!=(const Iterator& other) const {
			return ptr != other.ptr;
		}
	};
	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(nullptr); }


private:
	// Needed for sort LinkedList
	SingleNode<T>* split_list(SingleNode<T>* head);
	SingleNode<T>* merge_sorted_lists(SingleNode<T>* a, SingleNode<T>* b);
	SingleNode<T>* merge_sort(SingleNode<T>* head);
};

template <class T>
std::ostream& operator<<(std::ostream& out, const SingleLL<T>& sll)
{
	if (!sll.head)
	{
		out << "No data present";
		return out;
	}
	SingleNode<T>* cur = sll.head;
	while (cur)
	{
		out << cur->val << " ";
		cur = cur->next;
	}
	return out;
}

template <class T>
void SingleLL<T>::push_front(const T& value)
{
	SingleNode<T>* newNode = new SingleNode<T>(value, nullptr);
	newNode->next = head;
	head = newNode;
}

template <class T>
void SingleLL<T>::push_back(const T& value)
{
	SingleNode<T>* newNode = new SingleNode<T>(value, nullptr);
	if (!head)
	{
		head = newNode;
		return;
	}
	SingleNode<T>* tail = head;
	while (tail->next) tail = tail->next;
	tail->next = newNode;
}

template <class T>
void SingleLL<T>::pop_front()
{
	if (!head) return;
	SingleNode<T>* cur = head;
	head = head->next;
	delete cur;
}

template <class T>
void SingleLL<T>::pop_back()
{
	if (!head) return;
	else if (!head->next)
	{
		delete head;
		head = nullptr;
		return;
	}
	SingleNode<T>* tail = head;
	while (tail->next->next) tail = tail->next;
	delete tail->next;
	tail->next = nullptr;
}

template <class T>
int SingleLL<T>::size() const
{
	if (!head) return 0;
	int count = 0;
	SingleNode<T>* cur = head;
	while (cur)
	{
		cur = cur->next;
		count++;
	}
	return count;
}

template <class T>
bool SingleLL<T>::search(const T& value) const
{
	if (!head) return false;
	SingleNode<T>* cur = head;
	while (cur)
	{
		if (cur->val == value) return true;
		cur = cur->next;
	}
	return false;
}

template <class T>
void SingleLL<T>::insert_at(int index, const T& value)
{
	int n = size();
	if (index<0 || index>n) return;
	if (index == 0)
	{
		push_front(value);
		return;
	}
	else if (index == n)
	{
		push_back(value);
		return;
	}
	SingleNode<T>* pos = head;
	int i = 0;
	while (i < index - 1)
	{
		pos = pos->next;
		i++;
	}
	SingleNode<T>* newNode = new SingleNode<T>(value, nullptr);
	newNode->next = pos->next;
	pos->next = newNode;
}

template <class T>
void SingleLL<T>::remove_at(int index)
{
	if (index<0 || index>size()) return;
	if (index == 0)
	{
		pop_front();
		return;
	}
	SingleNode<T>* pos = head;
	int i = 0;
	while (i < index - 1)
	{
		pos = pos->next;
		i++;
	}
	SingleNode<T>* temp = pos->next;
	pos->next = temp->next;
	delete temp;
}

template <class T>
void SingleLL<T>::remove_value(const T& value)
{
	if (!head) return;
	if (head->val == value)
	{
		pop_front();
		return;
	}
	SingleNode<T>* prev = head;
	SingleNode<T>* cur = head->next;
	while (cur && cur->val != value)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur) return;
	prev->next = cur->next;
	delete cur;
}

template <class T>
void SingleLL<T>::reverse()
{
	if (!head || !head->next) return;
	SingleNode<T>* prev = nullptr;
	SingleNode<T>* cur = head;
	while (cur)
	{
		SingleNode<T>* next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	head = prev;
}

template <class T>
T SingleLL<T>::middle_element()
{
	if (!head) return T{};
	if (!head->next) return head->val;
	SingleNode<T>* slow = head;
	SingleNode<T>* fast = head;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow->val;
}

template <class T>
T SingleLL<T>::nth_from_begin(int n)
{
	if (!head) return T{};
	int s = size();
	if (n<0 || n>=s) return T{};
	SingleNode<T>* cur = head;
	for (int i = 0; i < n; i++)
	{
		cur = cur->next;
	}
	return cur->val;
}

template <class T>
T SingleLL<T>::nth_from_end(int n)
{
	if (!head) return T{};
	int s = size();
	if (n<0 || n>=s) return T{};
	SingleNode<T>* slow = head;
	SingleNode<T>* fast = head;
	for (int i = 0; i < n; i++)
	{
		fast = fast->next;
	}
	while (fast)
	{
		slow = slow->next;
		fast = fast->next;
	}
	return slow->val;
}

template <class T>
bool SingleLL<T>::detect_cycle()
{
	if (!head || !head->next) return false;
	SingleNode<T>* slow = head;
	SingleNode<T>* fast = head;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) return true;
	}
	return false;
}

template <class T>
SingleNode<T>* SingleLL<T>::split_list(SingleNode<T>* head)
{
	if (!head || !head->next) return nullptr;

	SingleNode<T>* slow = head;
	SingleNode<T>* fast = head->next;

	// Move: slow = middle, fast = end
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	SingleNode<T>* second = slow->next;
	slow->next = nullptr;  // break the list
	return second;
}

template <class T>
SingleNode<T>* SingleLL<T>::merge_sorted_lists(SingleNode<T>* a, SingleNode<T>* b)
{
	if (!a) return b;
	if (!b) return a;

	SingleNode<T>* result = nullptr;
	if (a->val <= b->val)
	{
		result = a;
		result->next = merge_sorted_lists(a->next, b);
	}
	else
	{
		result = b;
		result->next = merge_sorted_lists(a, b->next);
	}
	return result;
}

template <class T>
SingleNode<T>* SingleLL<T>::merge_sort(SingleNode<T>* node)
{
	if (!node || !node->next) return node;  // already sorted

	SingleNode<T>* second = split_list(node);

	// Sort both halves
	SingleNode<T>* left = merge_sort(node);
	SingleNode<T>* right = merge_sort(second);

	// Merge sorted halves
	return merge_sorted_lists(left, right);
}

template <class T>
void SingleLL<T>::sort()
{
	head = merge_sort(head);
}