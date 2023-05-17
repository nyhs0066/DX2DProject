#pragma once

#include "myST.h"

class CircularQueue
{
private:
	int* arr;
	int size;
	int head, tail;

public:
	CircularQueue();
	CircularQueue(int c);
	~CircularQueue();

	void enqueue(int num);
	int dequeue();
	int getHead();
	int getTail();
	bool isEmpty();
	int length();
	bool isFull();
	void printQueue();
};

class LinkedListQueue
{
private:
	Node_S* header;
	Node_S* tail;
	int length;

public:
	LinkedListQueue();
	~LinkedListQueue();

	void enqueue(int data);
	int dequeue();
	int getHead();
	int getTail();

	int getLength();
	bool isEmpty();

	void printQueue();

private:
	void clearQueue();
};