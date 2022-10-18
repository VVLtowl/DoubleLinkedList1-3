/*********************************************************
* @brief	�o�������X�g�̏ڍג�`
* @date		2022/10/11
********************************************************/
#include <assert.h>
#include "DoubleLinkedList.h"


//==========  �R���X�g�C�e���[�^ ==========

template <typename DataType>
bool DoubleLinkedList<DataType>::ConstIterator::IsVaild(const DoubleLinkedList* const list)
{
	bool hasReference = (m_pNode != nullptr && m_pList != nullptr);//���X�g�̎Q�Ƃ����邩
	bool sameList = (m_pList == list);//�������X�g�ł��邩

	return hasReference && sameList;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator& DoubleLinkedList<DataType>::ConstIterator::operator--()
{
	assert(m_pNode && m_pList && "pre decrement: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pList->Count() > 0 && "pre decrement: list is empty");//���X�g����ł͂Ȃ����̊m�F
	assert(m_pNode->pPrev != m_pList->m_pDummy && "pre decrement: begin cant decrement");// �擪�m�[�h�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pPrev;

	return (*this);
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator& DoubleLinkedList<DataType>::ConstIterator::operator++()
{
	assert(m_pNode && m_pList && "pre increment: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode != m_pList->m_pDummy && "pre increment: dummy cant increment");// �_�~�[�ł͂Ȃ����̊m�F

	m_pNode = m_pNode->pNext;

	return (*this);
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::ConstIterator::operator--(int i)
{
	assert(m_pNode && m_pList && "post decrement: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pList->Count() > 0 && "post decrement: list is empty");//���X�g����ł͂Ȃ����̊m�F
	assert(m_pNode->pPrev != m_pList->m_pDummy && "post decrement: begin cant decrement");// �擪�m�[�h�ł͂Ȃ����̊m�F

	ConstIterator iter(*this);//�^�Z�O�̃C�e���[�^���R�s�[
	m_pNode = m_pNode->pPrev;

	return iter;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::ConstIterator::operator++(int i)
{
	assert(m_pNode && m_pList && "post increment: no reference");// ���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode != m_pList->m_pDummy && "post increment: dummy cant increment");// �_�~�[�ł͂Ȃ����̊m�F

	ConstIterator iter(*this);//�^�Z�O�̃C�e���[�^���R�s�[
	m_pNode = m_pNode->pNext;

	return iter;
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
	assert(m_pNode && m_pList && "constIterator: no reference");//���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode != m_pList->m_pDummy && "constIterator: is dummy");//�_�~�[�ł͂Ȃ����̊m�F

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


//==========  �C�e���[�^ ==========

template <typename DataType>
DataType& DoubleLinkedList<DataType>::Iterator::operator*()
{
	assert(m_pNode && m_pList && "iterator: no reference");//���X�g�̎Q�Ƃ����邩�̊m�F
	assert(m_pNode != m_pList->m_pDummy && "iterator: is dummy");//�_�~�[�ł͂Ȃ����̊m�F

	return (*m_pNode).data;
}


//==========  �o�������X�g ==========

template <typename DataType>
DoubleLinkedList<DataType>::~DoubleLinkedList()
{
	//��̏ꍇ�������Ȃ�
	if (m_Count == 0)return;

	//�擪����A�����܂Ńm�[�h���폜
	Node* del = m_pDummy->pNext;//�擪�m�[�h�擾
	Node* next = del->pNext;//���̃m�[�h���Ɏ擾
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

	//�_�~�[���폜
	delete m_pDummy;
}

template <typename DataType>
DoubleLinkedList<DataType>::DoubleLinkedList()
{
	m_Count = 0;
	m_pDummy = new Node;
	m_pDummy->pPrev = m_pDummy;
	m_pDummy->pNext = m_pDummy;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::Insert(ConstIterator& positionIter, const DataType& data)
{
	//�V�v�f�̃m�[�h���쐬
	Node* newNode = new Node();
	newNode->data = data;

	//�C�e���[�^�L���ł��邩�̊m�F
	if (positionIter.IsVaild(this) == false)
	{
		return false;
	}

	//�}�����s��
	Node* prev = positionIter.m_pNode->pPrev;
	Node* next = positionIter.m_pNode;
	prev->pNext = newNode;
	newNode->pPrev = prev;
	newNode->pNext = next;
	next->pPrev = newNode;
	m_Count++;
	return true;
}

template <typename DataType>
bool DoubleLinkedList<DataType>::Remove(ConstIterator& positionIter)
{
	//���X�g����̏ꍇ�A�폜���s
	if (Count() == 0)
	{
		return false;
	}

	//�C�e���[�^�L���ł͂Ȃ��ꍇ�A�폜���s
	if (positionIter.IsVaild(this) == false)
	{
		return false;
	}

	//�_�~�[�m�[�h���w���ꍇ�A�폜���s
	if (positionIter.m_pNode == m_pDummy)
	{
		return false;
	}

	//�폜���s��
	Node* prev = positionIter.m_pNode->pPrev;
	Node* next = positionIter.m_pNode->pNext;
	prev->pNext = next;
	next->pPrev = prev;

	delete positionIter.m_pNode;
	m_Count--;
	return true;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::Iterator DoubleLinkedList<DataType>::Begin()
{
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
	return m_Count;
}

template <typename DataType>
typename DoubleLinkedList<DataType>::ConstIterator DoubleLinkedList<DataType>::CBegin() const
{
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
