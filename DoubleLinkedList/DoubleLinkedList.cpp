//export module DoubleLinkedList;
//
//export void MyFunc();

/*********************************************************
* @brief	双方向リストの詳細定義
* @date		2022/10/11
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "DoubleLinkedList.h"


//==========  ノード構造体 ==========


/*********************************************************
* @brief	デストラクタ
********************************************************/
template<typename Type>
DoubleLinkedList<Type>::Node::~Node()
{
	pPrev = nullptr;
	pNext = nullptr;
	pData = nullptr;
	isDummy = false;
}
/*********************************************************
* @brief	コンストラクタ　
* @param	データへのポインタ　
********************************************************/
template<typename Type>
DoubleLinkedList<Type>::Node::Node(Type* data) :
	pPrev(nullptr),
	pNext(nullptr),
	isDummy(false),
	pData(data)
{
}


//==========  コンストイテレータ ==========


/*********************************************************
* @brief	有効なイテレータであるか
* @detail	リストの参照がある、
*			同じリストであることを確認する。
* @return	全条件足した場合trueを返す、ほかの場合falseを返す
********************************************************/
template<typename Type>
template<typename TypeCI>
bool DoubleLinkedList<Type>::ConstIterator<TypeCI>::IsVaild(const DoubleLinkedList<TypeCI>* const list)
{
	bool hasReference = (m_pNode != nullptr && m_pList != nullptr);//リストの参照があるか
	bool sameList = (m_pList == list);//同じリストであるか

	return hasReference && sameList;
}

/*********************************************************
* @brief	リストの先頭に向かって一つ進める（前置デクリメント）
* @detail	リストの参照がない場合失敗になる。
*			リストが空である場合失敗になる。
*			直前ノードは先頭ノードの場合失敗になる。
* @return	演算された後のイテレータを返す
********************************************************/
template<typename Type>
template<typename TypeCI>
DoubleLinkedList<Type>::ConstIterator<TypeCI>& 
DoubleLinkedList<Type>::ConstIterator<TypeCI>::operator--()
{
	assert(m_pNode && m_pList && "pre decrement: no reference");// リストの参照があるかの確認
	assert(m_pList->Count() > 0 && "pre decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev->isDummy == false && "pre decrement: begin cant decrement");// 先頭ノードではないかの確認

	m_pNode = m_pNode->pPrev;

	return (*this);
}

/*********************************************************
* @brief	リストの末尾に向かって一つ進める（前置インクリメント）
* @detail	リストの参照がない場合失敗になる。
*			ノードはダミーの場合失敗になる。
* @return	演算された後のイテレータを返す
********************************************************/
template<typename Type>
template<typename TypeCI>
DoubleLinkedList<Type>::ConstIterator<TypeCI>& 
DoubleLinkedList<Type>::ConstIterator<TypeCI>::operator++()
{
	assert(m_pNode && m_pList && "pre increment: no reference");// リストの参照があるかの確認
	assert(m_pNode->isDummy == false && "pre increment: dummy cant increment");// ダミーではないかの確認

	m_pNode = m_pNode->pNext;

	return (*this);
}

/*********************************************************
* @brief	リストの末尾に向かって一つ進める（後置インクリメント）
* @detail	リストの参照がない場合失敗になる。
*			リストが空である場合失敗になる。
*			ノードは先頭ノードの場合失敗になる。
* @return	演算された後のイテレータを返す
********************************************************/
template<typename Type>
template<typename TypeCI>
DoubleLinkedList<Type>::ConstIterator<TypeCI>& 
DoubleLinkedList<Type>::ConstIterator<TypeCI>::operator--(int i)
{
	assert(m_pNode && m_pList && "post decrement: no reference");// リストの参照があるかの確認
	assert(m_pList->Count() > 0 && "post decrement: list is empty");//リストが空ではないかの確認
	assert(m_pNode->pPrev->isDummy == false && "post decrement: begin cant decrement");// 先頭ノードではないかの確認

	m_pNode = m_pNode->pPrev;

	return (*this);
}

/*********************************************************
* @brief	リストの末尾に向かって一つ進める（後置インクリメント）
* @detail	リストの参照がない場合失敗になる。
*			直後ノードはダミーの場合失敗になる。
* @return	演算された後のイテレータを返す
********************************************************/
template<typename Type>
template<typename TypeCI>
DoubleLinkedList<Type>::ConstIterator<TypeCI>& 
DoubleLinkedList<Type>::ConstIterator<TypeCI>::operator++(int i)
{
	assert(m_pNode && m_pList && "post increment: no reference");// リストの参照があるかの確認
	assert(m_pNode->isDummy == false && "post increment: dummy cant increment");// ダミーではないかの確認

	m_pNode = m_pNode->pNext;

	return (*this);
}


/*********************************************************
* @brief	イテレータの指す要素を取得する(const版)
* @detail	リストの参照がない場合失敗になる。
* 			ノードはダミーの場合失敗になる。
* @return	指した要素を返す
********************************************************/
template<typename Type>
template<typename TypeCI>
typename const DoubleLinkedList<Type>::Node&
DoubleLinkedList<Type>::ConstIterator<TypeCI>::operator*() const
{
	assert(m_pNode && m_pList && "constIterator: no reference");// リストの参照があるかの確認
	assert(m_pNode->isDummy == false && "constIterator: is dummy");

	return (*m_pNode);
}

/*********************************************************
* @brief	指す要素へのポインタを取得する(const版)
* @detail	(*ConstIterator)の場合、ダミーの方がassertを起こすため、
*			ポインタを用意する。
* @return	要素へのポインタを返す
********************************************************/
template<typename Type>
template<typename TypeCI>
typename const DoubleLinkedList<Type>::Node*
DoubleLinkedList<Type>::ConstIterator<TypeCI>::operator&() const
{
	return m_pNode;
}

/*********************************************************
* @brief	コピーを行う（コピーコンストラクタ）
* @detail	宣言時、引数、戻り値の3つの動作でコピーがとられた時に実行される。
********************************************************/
template<typename Type>
template<typename TypeCI>
DoubleLinkedList<Type>::ConstIterator<TypeCI>::ConstIterator(const ConstIterator<TypeCI>& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;
}

/*********************************************************
* @brief	代入を行う
* @return	代入を行ったのイテレータを返す
********************************************************/
template<typename Type>
template<typename TypeCI>
DoubleLinkedList<Type>::ConstIterator<TypeCI>& 
DoubleLinkedList<Type>::ConstIterator<TypeCI>::operator=(const ConstIterator<TypeCI>& constIter)
{
	m_pNode = constIter.m_pNode;
	m_pList = constIter.m_pList;

	return *this;
}

/*********************************************************
* @brief	同一か比較する
* @return	同一の場合trueを返す、異なる場合falseを返す
********************************************************/
template<typename Type>
template<typename TypeCI>
bool DoubleLinkedList<Type>::ConstIterator<TypeCI>::operator==(const ConstIterator<TypeCI>& iter)
{
	return m_pNode == iter.m_pNode;
}

/*********************************************************
* @brief	異なるか比較する
* @return	異なる場合trueを返す、同一の場合falseを返す
********************************************************/
template<typename Type>
template<typename TypeCI>
bool DoubleLinkedList<Type>::ConstIterator<TypeCI>::operator!=(const ConstIterator<TypeCI>& iter)
{
	return m_pNode != iter.m_pNode;
}


//==========  イテレータ ==========


/*********************************************************
* @brief	イテレータの指す要素を取得する(非const版)
* @detail	リストの参照がない場合失敗になる。
* 			ノードはダミーの場合失敗になる。
* @return	指した要素を返す
********************************************************/
template<typename Type>
template<typename TypeIter>
typename DoubleLinkedList<Type>::Node& 
DoubleLinkedList<Type>::Iterator<TypeIter>::operator*()
{
	assert(Iterator<TypeIter>::m_pNode && m_pList && "iterator: no reference");// リストの参照があるかの確認
	assert(m_pNode->isDummy == false && "iterator: is dummy");

	return *m_pNode;
}


//==========  双方向リスト ==========


/*********************************************************
* @brief	デストラクタ定義
* @detail	動的作成したノードを全部解放
********************************************************/
template<typename Type>
DoubleLinkedList<Type>::~DoubleLinkedList()
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

/*********************************************************
* @brief	コンストラクタ定義
* @detail	ダミーを作成
********************************************************/
template<typename Type>
DoubleLinkedList<Type>::DoubleLinkedList()
{								
	m_pDummy = new Node(nullptr);//?????????? nullptrでもダミー判断できるかも
	m_pDummy->isDummy = true;
}

/*********************************************************
* @brief	データを末尾後に追加
* @detail	ダミーノードが指すところに新しい要素を追加し、
*			ダミーノードを末尾へ一つ移動。
*			（ダミーノードは先頭へさす場合、ダミーの次を先頭の位置を代入）
* @param	データへのポインタ
* @return	追加成功の場合trueを返す
*			追加失敗の場合falseを返す
********************************************************/
template<typename Type>
bool DoubleLinkedList<Type>::PushBack(Type* data)
{
	ConstIterator iter = CEnd();
	return Insert(iter, data);
}

///*********************************************************
//* @brief	データ数を取得する
//* @detail	ループで加算して、データ数を計算する。
//*			constメソッドである。
//* @return	データ数を返す
//********************************************************/
//int DoubleLinkedList::Count() const
//{
//	//要素がない場合、0を返す
//	if (HeadNode() == nullptr)
//		return 0;
//
//	//データ数計算
//	int count = 0;
//	Node* node = HeadNode();
//	while (node != m_pDummy)
//	{
//		count++;
//		node = node->pNext;
//	}
//	return count;
//}
//
/*********************************************************
* @brief	データの挿入
* @detail	リストが空の場合末尾へ挿入、
*			空ではない場合イテレータが有効であるかを確認、
*			有効ではない場合、挿入失敗。
* @param	挿入位置のイテレータ、挿入したいデータへのポインタ
* @return	挿入成功の場合trueを返す
*			挿入失敗の場合falseを返す
********************************************************/
template<typename Type>
bool DoubleLinkedList<Type>::Insert(ConstIterator<Type>& positionIter, Type* data)
{
	//要素がない場合、挿入失敗
	if (data == nullptr)
		return false;

	//新要素のノードを作成
	Node* newNode = new Node(data);

	//リストが空の場合末尾へ挿入
	if (Count() == 0)
	{
		m_pDummy->pNext = newNode;
		newNode->pPrev = m_pDummy;
		newNode->pNext = m_pDummy;
		m_pDummy->pPrev = newNode;

		return true;
	}

	//イテレータ有効であるかの確認
	if (positionIter.IsVaild(this) == false)
		return false;

	//挿入を行う
	Node* prev = (&positionIter)->pPrev;//positionはダミーを指すイテレータの可能性がある
	Node* next = prev->pNext;

	prev->pNext = newNode;
	newNode->pPrev = prev;
	newNode->pNext = next;
	next->pPrev = newNode;

	return true;
}

///*********************************************************
//* @brief	データの削除
//* @detail	リストが空ではないかの確認、
//*			空ではない場合イテレータが有効であるかの確認、
//*			有効の場合ダミーではないかの確認。
//* @return	削除成功の場合trueを返す
//*			削除失敗の場合falseを返す
//********************************************************/
//bool DoubleLinkedList::Remove(ConstIterator& positionIter)
//{
//	//リストが空の場合、削除失敗
//	if (Count() == 0)
//		return false;
//
//	//イテレータ有効ではない場合、削除失デクリメント敗インクリメント
//	if (positionIter.IsVaild(this) == false)
//		return false;
//
//	//ダミーノードを指す場合、削除失敗
//	if ((&positionIter)->isDummy == true)//(*positionIter)の場合、ダミーの方がassertを起こす
//		return false;
//
//	//削除を行う
//	Node* prev = (&positionIter)->pPrev;//(*positionIter)の場合、ダミーの方がassertを起こす
//	Node* next = (&positionIter)->pNext;//(*positionIter)の場合、ダミーの方がassertを起こす
//
//	prev->pNext = next;
//	next->pPrev = prev;
//
//	return true;
//}
//
//
/*********************************************************
* @brief	先頭イテレータ取得する
* @detail	リストが空である場合、ダミーノードを指すイテレータを返す、
*			空ではない場合、先頭ノードを指すイテレータを返す。
* @return	先頭イテレータを返す
********************************************************/
template<typename Type>
DoubleLinkedList<Type>::Iterator<Type>
DoubleLinkedList<Type>::Begin()
{
	//リストが空である場合
	if (Count() == 0)
		return Iterator(m_pDummy, this);

	return Iterator(m_pDummy->pNext, this);
}

///*********************************************************
//* @brief	先頭コンストイテレータ取得する
//* @detail	リストが空である場合、ダミーノードを指すコンストイテレータを返す
//*			空ではない場合、先頭ノードを指すコンストイテレータを返す。
//* @return	先頭コンストイテレータを返す
//********************************************************/
//DoubleLinkedList::ConstIterator DoubleLinkedList::CBegin() const
//{
//	//リストが空である場合
//	if (Count() == 0)
//		return ConstIterator(m_pDummy, this);
//
//	return ConstIterator(HeadNode(), this);
//}
//
/*********************************************************
* @brief	末尾イテレータ取得する
* @detail	ダミーノードを指すイテレータを返す。
* @return	末尾イテレータを返す
********************************************************/
template<typename Type>
DoubleLinkedList<Type>::Iterator<Type>
DoubleLinkedList<Type>::End()
{
	return Iterator(m_pDummy, this);
}

///*********************************************************
//* @brief	末尾イテレータ取得する
//* @detail	ダミーノードを指すコンストイテレータを返す。
//* @return	末尾コンストイテレータを返す
//********************************************************/
//DoubleLinkedList::ConstIterator DoubleLinkedList::CEnd() const
//{
//	return ConstIterator(m_pDummy, this);
//}
