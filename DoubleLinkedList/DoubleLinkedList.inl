/*********************************************************
* @brief	双方向リストの詳細定義
* @date		2022/10/11
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "DoubleLinkedList.h"


//==========  コンストイテレータ ==========

template <typename DataType>
bool DoubleLinkedList<DataType>::ConstIterator::IsVaild(const DoubleLinkedList* const list)
{
	bool hasReference = (m_pNode != nullptr && m_pList != nullptr);//リストの参照があるか
	bool sameList = (m_pList == list);//同じリストであるか

	return hasReference && sameList;
}

template<typename DataType>
inline bool DoubleLinkedList<DataType>::ConstIterator::IsDummy()
{
	//リスト参照がない場合、ダミーではないと判断
	if (m_pNode == nullptr || m_pList == nullptr)
	{
		return false;
	}

	//指しているノードはダミーであるかと判断
	return m_pList->m_pDummy == m_pNode;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator& DoubleLinkedList<DataType>::ConstIterator::operator--()
{
	assert(m_pNode && m_pList && "pre decrement: no reference");// リストの参照があるかの確認
	assert(m_pList->Count() > 0 && "pre decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev != m_pList->m_pDummy && "pre decrement: begin cant decrement");// 先頭ノードではないかの確認

	m_pNode = m_pNode->pPrev;

	return (*this);
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator& DoubleLinkedList<DataType>::ConstIterator::operator++()
{
	assert(m_pNode && m_pList && "pre increment: no reference");// リストの参照があるかの確認
	assert(m_pNode != m_pList->m_pDummy && "pre increment: dummy cant increment");// ダミーではないかの確認

	m_pNode = m_pNode->pNext;

	return (*this);
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::ConstIterator::operator--(int i)
{
	assert(m_pNode && m_pList && "post decrement: no reference");// リストの参照があるかの確認
	assert(m_pList->Count() > 0 && "post decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev != m_pList->m_pDummy && "post decrement: begin cant decrement");// 先頭ノードではないかの確認

	m_pNode = m_pNode->pPrev;

	return (*this);
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::ConstIterator::operator++(int i)
{
	assert(m_pNode && m_pList && "post increment: no reference");// リストの参照があるかの確認
	assert(m_pNode != m_pList->m_pDummy && "post increment: dummy cant increment");// ダミーではないかの確認

	m_pNode = m_pNode->pNext;

	return (*this);
}

template <typename DataType>
DoubleLinkedList<DataType>::ConstIterator::ConstIterator(const ConstIterator& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator& DoubleLinkedList<DataType>::ConstIterator::operator=(const ConstIterator& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;

	return *this;
}

template <typename DataType>
typename const DataType& DoubleLinkedList<DataType>::ConstIterator::operator*() const
{
	assert(m_pNode && m_pList && "constIterator: no reference");//リストの参照があるかの確認
	assert(m_pNode != m_pList->m_pDummy && "constIterator: is dummy");//ダミーではないかの確認

	return (*m_pNode).data;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::ConstIterator::operator==(const ConstIterator& iter)const
{
	return m_pNode == iter.m_pNode;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::ConstIterator::operator!=(const ConstIterator& iter)const
{
	return m_pNode != iter.m_pNode;
}


//==========  イテレータ ==========

template <typename DataType>
DataType& DoubleLinkedList<DataType>::Iterator::operator*()
{
	assert(m_pNode && m_pList && "iterator: no reference");//リストの参照があるかの確認
	assert(m_pNode != m_pList->m_pDummy && "iterator: is dummy");//ダミーではないかの確認

	return (*m_pNode).data;
}


//==========  双方向リスト ==========

template <typename DataType>
DoubleLinkedList<DataType>::~DoubleLinkedList()
{
	//空の場合何もしない
	if (Count() == 0)return;

	//先頭から、末尾までノードを削除
	Node* del = m_pDummy->pNext;//先頭ノード取得
	Node* next = del->pNext;//次のノードを先に取得
	while (true)
	{
		delete del;
		del = nullptr;
		if (next == m_pDummy)
		{
			break;
		}
		else
		{
			del = next;
			next = next->pNext;
		}
	}

	//ダミーを削除
	delete m_pDummy;
}

template <typename DataType>
DoubleLinkedList<DataType>::DoubleLinkedList()
{
	m_pDummy = new Node;
	m_pDummy->pPrev = m_pDummy;
	m_pDummy->pNext = m_pDummy;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::Insert(ConstIterator& positionIter, const DataType& data)
{
	//新要素のノードを作成
	Node* newNode = new Node();
	newNode->data = data;

	//イテレータ有効であるかの確認
	if (positionIter.IsVaild(this) == false)
		return false;

	//挿入を行う
	Node* prev = positionIter.GetNode()->pPrev;
	Node* next = positionIter.GetNode();
	prev->pNext = newNode;
	newNode->pPrev = prev;
	newNode->pNext = next;
	next->pPrev = newNode;
	return true;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::Remove(ConstIterator& positionIter)
{
	//リストが空の場合、削除失敗
	if (Count() == 0)
	{
		return false;
	}

	//イテレータ有効ではない場合、削除失敗
	if (positionIter.IsVaild(this) == false)
	{
		return false;
	}

	//ダミーノードを指す場合、削除失敗
	if (positionIter.IsDummy() == true)
	{
		return false;
	}

	//削除を行う
	Node* prev = positionIter.GetNode()->pPrev;
	Node* next = positionIter.GetNode()->pNext;
	prev->pNext = next;
	next->pPrev = prev;
	return true;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::Iterator DoubleLinkedList<DataType>::Begin()
{
	//リストが空である場合
	if (Count() == 0)
	{
		Iterator iter;
		iter.m_pNode = m_pDummy;
		iter.m_pList = this;
		return iter;
	}

	Iterator iter;
	iter.m_pNode = m_pDummy->pNext;
	iter.m_pList = this;
	return iter;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::Iterator DoubleLinkedList<DataType>::End()
{
	Iterator iter;
	iter.m_pNode = m_pDummy;
	iter.m_pList = this;
	return iter;
}

template <typename DataType>
int DoubleLinkedList<DataType>::Count() const
{
	//先頭要素がない場合、0を返す
	if (m_pDummy->pNext == nullptr)
	{
		return 0;
	}

	//データ数計算
	int count = 0;
	Node* node = m_pDummy->pNext;//先頭要素へのポインタを取得
	while (node != m_pDummy)
	{
		count++;
		node = node->pNext;
	}
	return count;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::CBegin() const
{
	//リストが空である場合、ダミーイテレータを返す
	if (Count() == 0)
	{
		ConstIterator constIter;
		constIter.m_pNode = m_pDummy;
		constIter.m_pList = this;
		return constIter;
	}

	ConstIterator constIter;
	constIter.m_pNode = m_pDummy->pNext;
	constIter.m_pList = this;
	return constIter;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::CEnd() const
{
	ConstIterator constIter;
	constIter.m_pNode = m_pDummy;
	constIter.m_pList = this;
	return constIter;
}
