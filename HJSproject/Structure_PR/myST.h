#pragma once
#include <iostream>
#include <stack>
#include <queue>
#include <list>
#include <vector>
#include <string>
#include <map>

#define maximum(a, b) (((a) > (b)) ? (a) : (b))
#define minimum(a, b) (((a) < (b)) ? (a) : (b))
#define swaping(a, b) ((a)^=(b), (b)^=(a), (a)^=(b))

using namespace std;

struct Node_S
{
	int data;
	Node_S* pNode, * nNode;

	Node_S() : Node_S(nullptr, nullptr, 0) {}
	Node_S(Node_S* p, Node_S* n, int d) { pNode = p; nNode = n; data = d; }
	Node_S(int d) : Node_S(nullptr, nullptr, d) {}
};