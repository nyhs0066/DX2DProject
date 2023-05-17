#include "mystack.h"

Stack::Stack() : size(0), cap(10)
{
	arr = new int[10];
}

Stack::Stack(int c) : size(0), cap(c)
{
	arr = new int[c];
}

Stack::~Stack()
{
	delete[] arr;
}

void Stack::push(int num)
{
	if (isFull()) { recap(); }
	arr[size++] = num;
}

int Stack::pop()
{
	if (isEmpty()) { std::cout << "stack is empty, op dismissed \n"; return -1; }
	else
	{
		int temp = arr[--size];
		return temp;
	}
}

int Stack::top()
{
	if (isEmpty()) { std::cout << "stack is empty, op dismissed \n"; }
	return arr[size - 1];
}

bool Stack::isEmpty()
{
	return (size ? false : true);
}

int Stack::length()
{
	return size;
}

bool Stack::isFull()
{
	return (size == cap ? true : false);
}

void Stack::printStack()
{
	if (isEmpty()) { std::cout << "stack is empty. print dismissed \n"; }

	for (int i = 0; i < size; i++) { std::cout << arr[i] << ' '; }
	cout << '\n';
}

bool Stack::recap()
{
	int* temp = new int[cap + 10];
	if (!temp) { return false; }

	for (int i = 0; i < size; i++) { temp[i] = arr[i]; }
	delete[] arr;

	arr = temp;
	cap += 10;
	return true;
}

LinkedListStack::LinkedListStack()
{
	header = new Node_S;
	tail = new Node_S;
	length = 0;
}

LinkedListStack::~LinkedListStack()
{
	clearStack();
	delete header;
	delete tail;
}

void LinkedListStack::push(int data)
{
	Node_S* newNode = new Node_S(data);

	if (isEmpty())
	{
		header->nNode = newNode;
		tail->pNode = newNode;
	}
	else
	{
		newNode->pNode = tail->pNode;
		tail->pNode = newNode;
	}

	length++;
}

int LinkedListStack::pop()
{
	if (isEmpty()) { cout << "stack is empty. pop op dismissed. \n"; return -1; }
	else
	{
		Node_S* temp = tail->pNode;
		int ret = temp->data;

		if (!temp->pNode)
		{
			header->nNode = tail->pNode = nullptr;
		}
		else
		{
			tail->pNode = temp->pNode;
			tail->pNode->nNode = nullptr;
		}

		length--;
		delete temp;
		return ret;
	}

	return 0;
}

int LinkedListStack::top()
{
	if (isEmpty()) { cout << "stack is empty. top op dismissed \n"; return -1; }
	else
	{
		return tail->pNode->data;
	}
}

int LinkedListStack::getLength()
{
	return length;
}

bool LinkedListStack::isEmpty()
{
	return (tail->pNode) ? false : true;
}

void LinkedListStack::printStack()
{
	if (isEmpty()) { cout << "stack is empty. printStack op dismissed \n"; return; }
	else
	{
		Node_S* cur = header->nNode;

		while (cur->nNode)
		{
			std::cout << cur->data << ' ';
		}
		std::cout << '\n';
	}
}

void LinkedListStack::clearStack()
{
	Node_S* cur = header->nNode;
	Node_S* temp;

	while (cur && cur->nNode)
	{
		temp = cur;
		cur = cur->nNode;

		delete temp;
	}

	header->nNode = nullptr;
	tail->pNode = nullptr;
}

