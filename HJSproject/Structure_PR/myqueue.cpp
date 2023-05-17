#include "myqueue.h"

CircularQueue::CircularQueue()
{
	size = 10;
	arr = new int[10];
	head = tail = 0;
}

CircularQueue::CircularQueue(int c)
{
	size = c;
	arr = new int[c];
	head = tail = 0;
}

CircularQueue::~CircularQueue()
{
	delete[] arr;
}

void CircularQueue::enqueue(int num)
{
	if (isFull()) { cout << "Queue is full. enqueue op dismissed\n"; }
	else
	{
		arr[tail] = num;
		tail = (tail + 1) % size;
	}
}

int CircularQueue::dequeue()
{
	if (isEmpty()) { cout << "Queue is empty. dequeue op dismissed\n"; return -1; }
	else
	{
		int ret = arr[head];
		head = (head + 1) % size;
		return ret;
	}
}

int CircularQueue::getHead()
{
	return arr[head];
}

int CircularQueue::getTail()
{
	return arr[tail];
}

bool CircularQueue::isEmpty()
{
	return head == tail;
}

int CircularQueue::length()
{
	if (tail < head) { return tail + size - head; }
	else { return tail - head; }
}

bool CircularQueue::isFull()
{
	return (tail + 1) % size == head;
}

void CircularQueue::printQueue()
{
	int cur = head;

	while (cur % size != tail)
	{
		cout << arr[cur++] << ' ';
	}
}

LinkedListQueue::LinkedListQueue()
{
	header = tail = nullptr;
	length = 0;
}

LinkedListQueue::~LinkedListQueue()
{
	clearQueue();
}

void LinkedListQueue::enqueue(int data)
{
	Node_S* newE = new Node_S(data);

	if (!header) { header = tail = newE; }
	else
	{
		newE->nNode = header;
		header->pNode = newE;
		header = newE;
	}

	length++;
}

int LinkedListQueue::dequeue()
{
	if (isEmpty()) { cout << "Queue is empty. dequeue op dismissed\n"; return -1; }
	else
	{
		int ret = tail->data;
		Node_S* temp = tail;
		if (tail->pNode)
		{
			tail->pNode->nNode = nullptr;
			tail = tail->pNode;
		}
		else { header = tail = nullptr; }

		delete temp;
		temp = nullptr;

		length--;

		return ret;
	}
}

int LinkedListQueue::getHead()
{
	if (isEmpty()) { cout << "Queue is empty. getHead op dismissed\n"; }
	else { return header->data; }
}

int LinkedListQueue::getTail()
{
	if (isEmpty()) { cout << "Queue is empty. getTail op dismissed\n"; }
	else { return tail->data; }
}

int LinkedListQueue::getLength()
{
	return length;
}

bool LinkedListQueue::isEmpty()
{
	return !length;
}

void LinkedListQueue::printQueue()
{
	Node_S* cur = header;

	while (cur)
	{
		cout << cur->data << ' ';
		cur = cur->nNode;
	}

	cout << '\n';
}

void LinkedListQueue::clearQueue()
{
	Node_S* cur = header;
	Node_S* temp;

	while (cur)
	{
		temp = cur;
		cur = cur->nNode;
		delete temp;
		temp = nullptr;
	}
}
