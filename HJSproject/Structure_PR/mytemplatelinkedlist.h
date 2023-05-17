#pragma once
#include <assert.h>

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
		DataT getData() const;

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
	inline DataT Node<DataT>::getData() const
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
		//기본 변수
		Node<DataT>*		header;
		Node<DataT>*		tail;
		int					length;

	public:

		//기본 기능
		DoublelyLinkedList();
		~DoublelyLinkedList();

		//노드를 삽입한다. [ (pivot->prev) -> (newE) -> (pivot) ]
		void insertElement(DataT input, Node<DataT>* pivot = nullptr);
		//노드를 삽입한다. [ (pivot) -> (newE) -> (pivot->next) ]
		void insertElementBack(DataT input, Node<DataT>* pivot = nullptr);
		//지정 노드를 삭제한다.
		void deleteElement(Node<DataT>* target);
		//전위 또는 후위 삭제한다.(전위 : false, 후위 : true)
		void deleteElement(bool flag);
		//길이를 반환한다.
		int getLength();
		//비어있는지 확인한다.
		bool isEmpty();
		//리스트를 초기화한다.
		void clearList();
		//인덱스에 해당하는 노드를 반환한다.
		Node<DataT>* findINode(int idx);
		//인덱스의 유효성을 검사한다.
		bool isValidIdx(int idx);
	};

	template<typename DataT>
	DoublelyLinkedList<DataT>::DoublelyLinkedList()
	{
		header = nullptr;
		tail = nullptr;
		length = 0;
	}

	template<typename DataT>
	DoublelyLinkedList<DataT>::~DoublelyLinkedList()
	{
		clearList();
	}

	//전위 삽입 [ (pivot->prev) -> (newE) -> (pivot) ]
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
	}

	//후위 삽입 [ (pivot) -> (newE) -> (pivot->next) ]
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