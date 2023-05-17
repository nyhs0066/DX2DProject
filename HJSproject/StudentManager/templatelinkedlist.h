#pragma once
#include <assert.h>

namespace nsp_MySTM
{
	template <typename DataT>
	class Node
	{
	public:
		DataT			data;

		Node<DataT>*	pNext;
		Node<DataT>*	pPrev;

		Node();
		Node(DataT& input);

		void setData(DataT& input);
		const DataT getData() const;

		bool operator> (const Node& opd) const;
		bool operator== (const Node& opd) const;
		bool operator< (const Node& opd) const;
	};


	template<typename DataT>
	inline Node<DataT>::Node()
	{
		this->pNext = nullptr;
		this->pPrev = nullptr;
	}

	template<typename DataT>
	inline Node<DataT>::Node(DataT& input) : Node()
	{
		data = input;
	}

	template<typename DataT>
	inline void Node<DataT>::setData(DataT& input)
	{
		data = input;
	}

	template<typename DataT>
	inline const DataT Node<DataT>::getData() const
	{
		return this->data;
	}

	template<typename DataT>
	inline bool Node<DataT>::operator>(const Node& opd) const
	{
		return this->data > opd.data;
	}

	template<typename DataT>
	inline bool Node<DataT>::operator==(const Node& opd) const
	{
		return this->data == opd.data;
	}

	template<typename DataT>
	inline bool Node<DataT>::operator<(const Node& opd) const
	{
		return this->data < opd.data;
	}

	template<typename DataT>
	class DoublelyLinkedList
	{
	private:
		//�⺻ ����
		Node<DataT>*		header;
		Node<DataT>*		tail;
		int					length;

		//Ȯ�� ��� ����

			//���İ� �˻��� ���� �ӽ� �迭
		Node<DataT>**		tTable;
		int					tLen;

		//�˻��� ���� ����
		int					st_idx;
		int					ed_idx;
		bool				searchFlag;

	public:

		//�⺻ ���
		DoublelyLinkedList();
		~DoublelyLinkedList();

		//��带 �����Ѵ�. [ (pivot->prev) -> (newE) -> (pivot) ]
		void insertElement(DataT input, Node<DataT>* pivot = nullptr);
		//��带 �����Ѵ�. [ (pivot) -> (newE) -> (pivot->next) ]
		void insertElementBack(DataT input, Node<DataT>* pivot = nullptr);
		//���� ��带 �����Ѵ�.
		void deleteElement(Node<DataT>* target);
		//���� �Ǵ� ���� �����Ѵ�.(���� : false, ���� : true)
		void deleteElement(bool flag);
		//���̸� ��ȯ�Ѵ�.
		int getLength();
		//����ִ��� Ȯ���Ѵ�.
		bool isEmpty();
		//����Ʈ�� �ʱ�ȭ�Ѵ�.
		void clearList();
		//�ε����� �ش��ϴ� ��带 ��ȯ�Ѵ�.
		Node<DataT>* findINode(int idx);
		//�ε����� ��ȿ���� �˻��Ѵ�.
		bool isValidIdx(int idx);

		//Ȯ�� ���
			//���Ḯ��Ʈ�� ���ĵ� ���·� �籸���Ѵ�.
		void sortList(bool AnD_flag);

		//�ӽ� �迭�� �����.
		void create_tTable();
		//�ӽ� �迭�� �����Ѵ�.
		void delete_tTable();

		//= ���� =
			//�ӽ� �迭�� �����Ѵ�. (�������� �� ����)
		void sortingTable();
		//�� ���� �ΰ����
		void heapify(int idx, int len);
		void buildHeap(int len);
		void heap_sort();

		//= �˻� & �۾� =
			//�ӽ� �迭���� �˻��Ѵ�.
		void searchNode(DataT key);
		void searchSub(Node<DataT>* key);

		//�ӽ� �迭���� �۾��� ��带 �ҷ��´�.
		//�˻��� �Ǿ�߸� ��밡���ϰ� �ǹ��ִ� ���� �����ϴ� ���� �ƴϸ� nullptr�� ��ȯ�Ѵ�.
		Node<DataT>* getINode(int tTableidx);

		//���� �˻� ���� �÷���:�˻��� �Ǿ��ٸ� true
		bool getS_Flag();
		//���� Ű���� ���� ������ ������� �Ѵ�. �˻��� �Ǿ�߸� �ǹ̰� �ִ�.
		int getS_StIdx();	//���� �ε���
		int getS_EdIdx();	//�� �ε���
	};

	template<typename DataT>
	DoublelyLinkedList<DataT>::DoublelyLinkedList()
	{
		header = nullptr;
		tail = nullptr;
		length = 0;

		tTable = nullptr;
		tLen = 0;

		st_idx = ed_idx = -1;
		searchFlag = false;
	}

	template<typename DataT>
	DoublelyLinkedList<DataT>::~DoublelyLinkedList()
	{
		clearList();
	}

	//���� ���� [ (pivot->prev) -> (newE) -> (pivot) ]
	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::insertElement(DataT input, Node<DataT>* pivot)
	{
		Node<DataT>* newE = new Node<DataT>(input);
		assert(newE);

		if (!pivot) { pivot = header; }

		if (pivot)
		{
			if (!pivot->pPrev) { header = newE; }
			else
			{
				newE->pPrev = pivot->pPrev;
				pivot->pPrev->pNext = newE;
			}
			pivot->pPrev = newE;
			newE->pNext = pivot;
		}
		else { header = tail = newE; }

		length++;
		create_tTable();
	}

	//���� ���� [ (pivot) -> (newE) -> (pivot->next) ]
	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::insertElementBack(DataT input, Node<DataT>* pivot)
	{
		Node<DataT>* newE = new Node<DataT>(input);
		assert(newE);

		if (!pivot) { pivot = tail; }

		if (pivot)
		{
			if (!pivot->pNext) { tail = newE; }
			else
			{
				newE->pNext = pivot->pNext;
				pivot->pNext->pPrev = newE;
			}
			pivot->pNext = newE;
			newE->pPrev = pivot;
		}
		else { header = tail = newE; }

		length++;
		create_tTable();
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::deleteElement(Node<DataT>* target)
	{
		assert(target);
		Node<DataT>* tpP = target->pPrev, * tpN = target->pNext;

		if (!tpP) { header = header->pNext; }
		else { tpP->pNext = tpN; }

		if (!tpN) { tail = tail->pPrev; }
		else { tpN->pPrev = tpP; }

		delete target;
		target = nullptr;

		length--;
		create_tTable();
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::deleteElement(bool flag)
	{
		if (flag) { deleteElement(tail); }
		else { deleteElement(header); }
	}

	template<typename DataT>
	inline int DoublelyLinkedList<DataT>::getLength() { return length; }

	template<typename DataT>
	inline bool DoublelyLinkedList<DataT>::isEmpty() { return !length; }

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::clearList()
	{
		Node<DataT>* cur = header;
		Node<DataT>* temp = nullptr;

		while (cur)
		{
			temp = cur;
			cur = cur->pNext;

			delete temp;
			temp = nullptr;
		}

		header = tail = nullptr;
		length = 0;
	}

	template<typename DataT>
	inline Node<DataT>* DoublelyLinkedList<DataT>::findINode(int idx)
	{
		Node<DataT>* cur = nullptr;
		if (idx >= 0 && idx < length)
		{
			cur = header;
			for (int i = 0; i < idx; i++) { cur = cur->pNext; }
		}
		return cur;
	}

	template<typename DataT>
	inline bool DoublelyLinkedList<DataT>::isValidIdx(int idx)
	{
		return ((idx >= 0) && (idx < length)) ? true : false;
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::sortList(bool AnD_flag)
	{
		Node<DataT>* cur = header, * temp = nullptr, * pos = nullptr;
		bool flag = false;

		while (cur)
		{
			temp = cur;
			cur = cur->pNext;
			temp->pNext = temp->pPrev = nullptr;

			if (!flag) { header = tail = temp; flag = true; continue; }
			else { pos = tail; }

			while (pos && ((AnD_flag) ? (*pos < *temp) : (*pos > *temp))) 
			{ pos = pos->pPrev; }

			if (pos) 
			{ 
				if (!pos->pNext) { tail = temp; }
				else
				{
					temp->pNext = pos->pNext;
					pos->pNext->pPrev = temp;
				}
				pos->pNext = temp;
				temp->pPrev = pos;
			}
			else 
			{ 
				header->pPrev = temp;
				temp->pNext = header;
				header = temp;
			}
		}
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::create_tTable()
	{
		if (tTable) { delete_tTable(); }

		tTable = new Node<DataT>*[length + 1];
		tTable[0] = nullptr;	//�� Ư���� �̿��ϱ� ���� ��ó��

		assert(tTable);

		int idx = 0;
		Node<DataT>* cur = header;

		while (cur)
		{
			tTable[++idx] = cur;
			cur = cur->pNext;
		}

		tLen = length;
		searchFlag = false;
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::delete_tTable()
	{
		if (tTable)
		{
			for (int i = 1; i < tLen; i++) { tTable[i] = nullptr; }
			delete[] tTable;
			tLen = 0;
		}
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::sortingTable()
	{
		heap_sort();
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::heapify(int idx, int len)
	{
		int left = idx * 2;
		int right = idx * 2 + 1;
		int max = idx;
		Node<DataT>* temp = nullptr;

		if (right <= len && (*tTable[right] > *tTable[max])) { max = right; }
		if (left <= len && (*tTable[left] > *tTable[max])) { max = left; }

		if (idx != max)
		{
			temp = tTable[max];
			tTable[max] = tTable[idx];
			tTable[idx] = temp;

			heapify(max, len);
		}
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::buildHeap(int len)
	{
		for (int i = len / 2; i > 0; i--) { heapify(i, len); }
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::heap_sort()
	{
		buildHeap(tLen);

		Node<DataT>* temp = nullptr;

		for (int i = tLen; i > 1; i--)
		{
			temp = tTable[i];
			tTable[i] = tTable[1];
			tTable[1] = temp;

			heapify(1, i - 1);
		}
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::searchNode(DataT key)
	{
		if (isEmpty())
		{
			searchFlag = false;
			return;
		}
		else
		{
			Node<DataT>* keyNode = new Node<DataT>(key);
			searchSub(keyNode);
			delete keyNode;
			return;
		}
	}

	template<typename DataT>
	inline void DoublelyLinkedList<DataT>::searchSub(Node<DataT>* key)
	{
		sortingTable();

		int st = 1, ed = tLen;
		int mid = (st + ed) / 2;
		int cur;

		while (st < ed)
		{
			mid = (st + ed) / 2;
			if (*key > *tTable[mid]) { st = mid + 1; }
			else { ed = mid; }
		}

		cur = st;
		st_idx = st;
		searchFlag = false;

		if (cur <= tLen && (*key == *tTable[cur]))
		{
			searchFlag = true;
			while (cur <= tLen && (*key == *tTable[cur])) { ed_idx = cur++; }
		}
	}

	template<typename DataT>
	inline Node<DataT>* DoublelyLinkedList<DataT>::getINode(int tTableIdx)
	{
		if (searchFlag)
		{
			if (st_idx <= tTableIdx && tTableIdx <= ed_idx) { return tTable[tTableIdx]; }
			else { return nullptr; }
		}
		else { return nullptr; }
	}

	template<typename DataT>
	inline bool DoublelyLinkedList<DataT>::getS_Flag()
	{
		return searchFlag;
	}

	template<typename DataT>
	inline int DoublelyLinkedList<DataT>::getS_StIdx()
	{
		return st_idx;
	}

	template<typename DataT>
	inline int DoublelyLinkedList<DataT>::getS_EdIdx()
	{
		return ed_idx;
	}

}