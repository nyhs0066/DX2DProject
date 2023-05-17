#pragma once

#include "myST.h"

class Stack
{
private:
	int* arr;
	int size, cap;

public:
	Stack();
	Stack(int c);
	~Stack();

	void push(int num);
	int pop();
	int top();
	bool isEmpty();
	int length();
	bool isFull();
	void printStack();

private:
	bool recap();
};

class LinkedListStack
{
private:
	Node_S* header;
	Node_S* tail;
	int length;

public:
	LinkedListStack();
	~LinkedListStack();

	void push(int data);
	int pop();
	int top();

	int getLength();

	bool isEmpty();

	void printStack();

private:
	void clearStack();
};