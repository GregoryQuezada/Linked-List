#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
//#include "leaker.h"
using namespace std;

template <typename T>
class LinkedList
{

public: 
	struct Node
	{
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
	};

	Node* head;
	Node* tail;
	unsigned int count;

	// Behaviors
	void PrintForward() const;
	void PrintReverse() const;
	void PrintForwardRecursive(const Node *node) const;
	void PrintReverseRecursive(const Node* node) const;
	
	// Accessors 
	unsigned int NodeCount() const;
	void FindAll(vector<Node*>& outData, const T& value) const;
	const Node* Find(const T& data) const;
	Node* Find(const T& data);
	const Node* GetNode(unsigned int index) const;
	Node* GetNode(unsigned int index);
	Node* Head();
	const Node* Head() const;
	Node* Tail();
	const Node* Tail() const;

	// Insertion
	void AddHead(const T& data);
	void AddTail(const T& data);
	void AddNodesHead(const T* data, unsigned int count);
	void AddNodesTail(const T* data, unsigned int count);
	void InsertAfter(Node* node, const T& data);
	void InsertBefore(Node* node, const T& data);
	void InsertAt(const T& data, unsigned int index);

	// Removal
	bool RemoveHead();
	bool RemoveTail();
	unsigned int Remove(const T& data);
	bool RemoveAt(int index);
	void Clear();

	// Operators
	const T& operator[](unsigned int index) const;
	T& operator[](unsigned int index);
	bool operator==(const LinkedList<T>& rhs) const;
	LinkedList<T>& operator=(const LinkedList<T>& rhs);

	// Construction / Destruction
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();

};

// Behaviors
template <typename T>
void LinkedList<T>::PrintForward() const
{

	for (unsigned int i = 0; i < count; i++)
	{
		cout << GetNode(i)->data << "\n";
	}

	/*for (unsigned int i = 0; i < count; i++)
	{
		cout << this[i] << endl;
	}*/
}

template <typename T>
void LinkedList<T>::PrintReverse() const
{

	for (unsigned int i = 1; i <= count; i++)
	{
		cout << GetNode(count - i)->data << "\n";
	}
}

template <typename T>
void LinkedList<T>::PrintForwardRecursive(const Node* node) const
{
	if (node == nullptr)
	{
		cout << "\n";
		return;
	}
	cout << node->data << "\n";
	PrintForwardRecursive(node->next);
}

template <typename T>
void LinkedList<T>::PrintReverseRecursive(const Node* node) const
{
	if (node == nullptr)
	{
		cout << "\n";
		return;
	}
	cout << node->data << "\n";
	PrintReverseRecursive(node->prev);
}

// Accessors
template <typename T>
unsigned int LinkedList<T>::NodeCount() const
{
	return count;
}

template <typename T>
void LinkedList<T>::FindAll(vector<Node*>& outData, const T& value) const
{

	for (unsigned int i = 0; i < count; i++)
	{
		if (GetNode(i)->data == value)
			outData.push_back((Node*)GetNode(i));
	}
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data) const
{
	for (unsigned int i = 0; i < count; i++)
	{
		if (GetNode(i)->data == data)
			return GetNode(i);
	}
	return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& data)
{
	for (unsigned int i = 0; i < count; i++)
	{
		if (GetNode(i)->data == data)
			return GetNode(i);
	}
	return nullptr;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
	Node* temp = head;

	if (index >= count || head == nullptr)
	{
		throw runtime_error("Index out of range.");
		return nullptr;
	}


	for (unsigned int i = 0; i <= index; i++)
	{
		if (i == index)
			return temp;

		temp = temp->next;
	}
	return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
	Node* temp = head;

	if (index >= count || head == nullptr)
	{
		throw runtime_error("Index out of range.");
		return nullptr;
	}


	for (unsigned int i = 0; i <= index; i++)
	{
		if (i == index)
			return temp;

		temp = temp->next;
	}
	return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
	return head;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Head() const
{
	return head;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
	return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const
{
	return tail;
}

// Insertion
template <typename T>
void LinkedList<T>::AddHead(const T& data)
{
	Node* temp = new Node;
	temp->data = data;
	temp->next = head;

	if (head != nullptr)
		temp->next->prev = temp;

	head = temp;
	count++;
	tail = GetNode(count - 1);
}

template <typename T>
void LinkedList<T>::AddTail(const T& data)
{
	Node* temp = new Node;
	temp->data = data;
	temp->prev = tail;
	
	if (tail != nullptr)
		temp->prev->next = temp;

	tail = temp;
	count++;
	if (head == nullptr)
		head = temp;
	else
		head = GetNode(0);
}

template <typename T>
void LinkedList<T>::AddNodesHead(const T* data, unsigned int count)
{
	for (unsigned int i = count; i > 0; i--)
	{
		AddHead(data[i-1]);
	}
}

template <typename T>
void LinkedList<T>::AddNodesTail(const T* data, unsigned int count)
{
	for (unsigned int i = 0; i < count; i++)
	{
		AddTail(data[i]);
	}
}

template <typename T>
void LinkedList<T>::InsertAfter(Node *node, const T &data)
{
	if (node == nullptr)
	{
		cout << "Given node is null.\n\n";
		return;
	}

	Node* temp = new Node;
	Node* move;
	unsigned int num = count;

	for (unsigned int i = 0; i < num; i++)
	{
		if (GetNode(i) == node)
		{
			move = GetNode(i);
			temp->data = data;
			temp->next = move->next;
			temp->prev = move;
			move->next = temp;

			if (temp->next == nullptr)
				head = temp;
			count++;
			return;
		}
	}
	

}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data)
{
	if (node == nullptr)
	{
		cout << "Given node is null.\n\n";
		return;
	}

	Node* temp = new Node;
	Node* move;
	unsigned int num = count;

	for (unsigned int i = 0; i < num; i++)
	{
		if (GetNode(i) == node)
		{
			move = GetNode(i);
			temp->data = data;
			temp->next = move;
			temp->prev = move->prev;
			move->prev = temp;

			if (temp->prev == nullptr)
				tail = temp;
			else
				temp->prev->next = temp;
			count++;
			return;
		}
	}
}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index)
{

	if (index > count)
	{
		throw runtime_error("Invalid index");
	}
	else if (index == 0)
	{
		AddHead(data);
	}
	else if (index < count)
	{
		InsertBefore(GetNode(index), data);
	}
	else if (index == count)
		AddTail(data);
}

// Removal 
template <typename T>
bool LinkedList<T>::RemoveHead()
{
	if (head == nullptr)
		return false;
	else
	{
		Node* temp = head;
		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
			count--;

			delete temp;
			return true;
		}
		temp->next->prev = nullptr;
		head = temp->next;
		count--;

		delete temp;
		return true;
	}
	
	/*else if (head == tail)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
		count--;
		return true;
	}
	else
	{
		head->next->prev = nullptr;
		delete head;
		count--;
		head = GetNode(0);
		return true;
	}*/
}

template <typename T>
bool LinkedList<T>::RemoveTail()
{
	if (tail == nullptr)
		return false;
	else
	{
		Node* temp = tail;
		if (head == tail)
		{
			head = nullptr;
			tail = nullptr;
			count--;

			delete temp;
			return true;
		}
		temp->prev->next = nullptr;
		tail = temp->prev;
		count--;

		delete temp;
		return true;
	}
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data)
{
	unsigned int num = 0;
	Node* temp;
	for (unsigned int i = 0; i < count; i++)
	{
		if (GetNode(i)->data == data)
		{
			temp = GetNode(i);
			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			delete temp;
			temp = nullptr;
			count--;
			num++;
		}

	}
	return num;
}

template <typename T>
bool LinkedList<T>::RemoveAt(int index)
{
	Node* temp;

	if ((unsigned int)index >= count)
	{
		return false;
	}
	else if ((unsigned int)index == count - 1)
		return RemoveTail();
	else if (index == 0)
		return RemoveHead();
	else
	{
		temp = GetNode(index);
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		delete temp;
		count--;
		return true;
	}
	return false;
}

template <typename T>
void LinkedList<T>::Clear()
{
	Node* erase = head;
	Node* temp;

	while (erase != nullptr)
	{
		temp = erase->next;
		delete erase;
		erase = temp;
	}
	count = 0;
	head = nullptr;
	tail = nullptr;
}

// Operators
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
	return GetNode(index)->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
	return GetNode(index)->data;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) const
{
	if (this->NodeCount() == rhs.NodeCount())
	{
		for (unsigned int i = 0; i < count; i++)
		{
			if (this->GetNode(i)->data != rhs.GetNode(i)->data)
				return false;
		}
		return true;
	}
	else
		return false;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
	if (&rhs != this)
	{
		Clear();
			if (rhs.head == nullptr)
			{
				head = nullptr;
				tail = nullptr;
				count = 0;
			}
			else
			{
				for (unsigned int i = 0; i < rhs.count; i++)
				{
					AddTail(rhs.GetNode(i)->data);
				}

			}
	}

	return *this;
}

// Construction / Destruction
template <typename T>
LinkedList<T>::LinkedList()
{
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list)
{
	head = nullptr;
	tail = nullptr;
	count = 0;

	if (&list != this)
	{
		Clear();
		if (list.head == nullptr)
		{
			head = nullptr;
			tail = nullptr;
			count = 0;
		}
		else
		{
			for (unsigned int i = 0; i < list.count; i++)
			{
				AddTail(list.GetNode(i)->data);
			}

		}
	}
	if (this == &list)
		cout << "Lists are the same.";
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	Clear();
}