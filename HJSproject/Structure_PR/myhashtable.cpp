#include "myhashtable.h"

Bucket::Bucket(string key, string data)
{
	this->key = key;
	this->data = data;
}

Bucket::~Bucket() {}

unsigned int Bucket::hash(string& key)
{
	unsigned int result = 0;
	unsigned int hashValue = 0x78924371;

	for (auto ch : key) { result += ch * hashValue; }

	return result;
}

HashTable::HashTable() : HashTable(50)
{
}

HashTable::HashTable(int createTableNum)
{
	numberOfTable = createTableNum;
	table = new list<Bucket*>[createTableNum];
}

HashTable::~HashTable()
{
	Bucket* cur;
	for (int i = 0; i < numberOfTable; i++)
	{
		for (auto it : table[i])
		{
			cur = it;
			delete cur;
		}
		table[i].clear();
	}

	delete[] table;
}

void HashTable::insert(Bucket* input)
{
	unsigned int pos = input->hash(input->key) % numberOfTable;
	table[pos].push_back(input);
}

Bucket* HashTable::search(string key)
{
	Bucket* pFind = nullptr;

	list<Bucket*>* targetTable = &table[Bucket::hash(key) % numberOfTable];

	for (auto it : *targetTable)
	{
		if (it->key == key) { pFind = it; }
	}

	return pFind;
}

void HashTable::deleteBucket(string key)
{
	Bucket* target = nullptr;
	list<Bucket*>* targetTable = &table[Bucket::hash(key) % numberOfTable];
	list<Bucket*>::iterator it;

	for (it = targetTable->begin(); it != targetTable->end(); it++)
	{
		target = *it;
		if (target->key == key)
		{
			targetTable->erase(it);
			break;
		}
	}

	delete target;
}
