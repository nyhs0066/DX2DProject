#pragma once
#include "myST.h"

class Bucket
{
public:
	string key;
	string data;

	Bucket(string key, string data);
	~Bucket();

	static unsigned int hash(string& key);
};


class HashTable
{
private:
	list<Bucket*>* table;
	int numberOfTable;

public:
	HashTable();
	HashTable(int createTableNum);
	~HashTable();

	void insert(Bucket* input);
	Bucket* search(string key);
	void deleteBucket(string key);
};

class SimpleUniformHashTable
{
private:
	HashTable* table;
	int numberOfHashtable;

public:
	SimpleUniformHashTable();
	~SimpleUniformHashTable();

	void insert(Bucket* input);
	Bucket* search(string key);
	void deleteBucket(string key);
};