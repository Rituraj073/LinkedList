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
	
	template <class U>
	friend std::ostream& operator<<(std::ostream& out, const SingleLL<U>& sll);
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