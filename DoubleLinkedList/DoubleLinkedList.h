/*********************************************************
* @brief	�o�������X�g�̃w�b�_�[�t�@�C��
* @date		2022/10/11
********************************************************/
#pragma once

//========== �o�������X�g ==========
template <typename DataType>
class DoubleLinkedList
{
private:
	//========== �m�[�h�\���� ==========
	struct Node
	{
		/*********************************************************
		* @brief	�O�̃m�[�h�ւ̃|�C���^
		********************************************************/
		Node* pPrev = nullptr;

		/*********************************************************
		* @brief	���̃m�[�h�ւ̃|�C���^
		********************************************************/
		Node* pNext = nullptr;

		/*********************************************************
		* @brief	�f�[�^
		********************************************************/
		DataType data;
	};

public:
	//==========  �R���X�g�C�e���[�^ ==========
	class ConstIterator
	{
	protected:
		/*********************************************************
		* @brief	�m�[�h�ւ̃|�C���^
		********************************************************/
		Node* m_pNode;

		/*********************************************************
		* @brief	���X�g�ւ̃|�C���^
		********************************************************/
		const DoubleLinkedList* m_pList;

	protected:
		/*********************************************************
		* @brief	�L���ȃC�e���[�^�ł��邩
		* @detail	���X�g�̎Q�Ƃ�����A
		*			�������X�g�ł��邱�Ƃ��m�F����B
		* @param	list: �������X�g�ł��邩�̔��f�p���X�g�ւ̃|�C���^
		* @return	�S�����������ꍇtrue��Ԃ��A�ق��̏ꍇfalse��Ԃ�
		********************************************************/
		bool IsVaild(const DoubleLinkedList* const list);

		/*********************************************************
		* @brief	�w�����m�[�h�̓_�~�[�m�[�h�ł��邩
		* @detail	�Q�Ƃ��Ȃ��Ƃ��_�~�[�ł͂Ȃ��Ɣ��f�B
		*			���X�g�̎Q�Ƃł��̃��X�g�̃_�~�[�m�[�h�ł��邩���m�F�B
		* @return	�_�~�[�m�[�h�̏ꍇtrue��Ԃ��A�ق��̏ꍇfalse��Ԃ�
		********************************************************/
		bool IsDummy();

		/*********************************************************
		* @brief	�w�����X�g�ւ̃|�C���^���擾����(const��)
		* @return	�w�����X�g�̃|�C���^��Ԃ�
		********************************************************/
		const DoubleLinkedList* GetList()const { return m_pList; };

		/*********************************************************
		* @brief	�w���m�[�h�ւ̃|�C���^���擾����(const��)
		* @return	�w���m�[�h�̃|�C���^��Ԃ�
		********************************************************/
		Node* GetNode() const { return m_pNode; };

	public:
		/*********************************************************
		* @brief	�R���X�g���N�^�@
		********************************************************/
		ConstIterator() :
			m_pNode(nullptr),
			m_pList(nullptr) {};

		/*********************************************************
		* @brief	���X�g�̐擪�Ɍ������Ĉ�i�߂�i�O�u�f�N�������g�j
		* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
		*			���X�g����ł���ꍇ���s�ɂȂ�B
		*			���O�m�[�h�͐擪�m�[�h�̏ꍇ���s�ɂȂ�B
		* @return	���Z���ꂽ��̃C�e���[�^��Ԃ�
		********************************************************/
		ConstIterator& operator--();

		/*********************************************************
		* @brief	���X�g�̖����Ɍ������Ĉ�i�߂�i�O�u�C���N�������g�j
		* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
		*			�m�[�h�̓_�~�[�̏ꍇ���s�ɂȂ�B
		* @return	���Z���ꂽ��̃C�e���[�^��Ԃ�
		********************************************************/
		ConstIterator& operator++();

		/*********************************************************
		* @brief	���X�g�̖����Ɍ������Ĉ�i�߂�i��u�C���N�������g�j
		* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
		*			���X�g����ł���ꍇ���s�ɂȂ�B
		*			�m�[�h�͐擪�m�[�h�̏ꍇ���s�ɂȂ�B
		* @return	���Z���ꂽ��̃C�e���[�^��Ԃ�
		********************************************************/
		ConstIterator operator--(int i);

		/*********************************************************
		* @brief	���X�g�̖����Ɍ������Ĉ�i�߂�i��u�C���N�������g�j
		* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
		*			����m�[�h�̓_�~�[�̏ꍇ���s�ɂȂ�B
		* @return	���Z���ꂽ��̃C�e���[�^��Ԃ�
		********************************************************/
		ConstIterator operator++(int i);

		/*********************************************************
		* @brief	�R�s�[���s���i�R�s�[�R���X�g���N�^�j
		* @detail	�錾���A�����A�߂�l��3�̓���ŃR�s�[���Ƃ�ꂽ���Ɏ��s�����B
		********************************************************/
		ConstIterator(const ConstIterator& constIter);

		/*********************************************************
		* @brief	������s��
		* @return	������s�����̃C�e���[�^��Ԃ�
		********************************************************/
		ConstIterator& operator=(const ConstIterator& constIter);


		//const���\�b�h

		/*********************************************************
		* @brief	�C�e���[�^�̎w���v�f���擾����(const��)
		* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
		* 			�m�[�h�̓_�~�[�̏ꍇ���s�ɂȂ�B
		* @return	�w�����v�f��Ԃ�
		********************************************************/
		const DataType& operator*()const;

		/*********************************************************
		* @brief	���ꂩ��r����
		* @return	����̏ꍇtrue��Ԃ��A�قȂ�ꍇfalse��Ԃ�
		********************************************************/
		bool operator==(const ConstIterator& constIter)const;

		/*********************************************************
		* @brief	�قȂ邩��r����
		* @return	�قȂ�ꍇtrue��Ԃ��A����̏ꍇfalse��Ԃ�
		********************************************************/
		bool operator!=(const ConstIterator& constIter)const;

		//DoubleLinkedList�̊֐����ŁA�L���C�e���[�^�m�F���邽��
		friend DoubleLinkedList;
	};

	//========== �C�e���[�^ ==========
	class Iterator :public ConstIterator
	{
	private:
		//using ConstIterator::m_pNode;
		//using ConstIterator::m_pList;
	public:
		/*********************************************************
		* @brief	�C�e���[�^�̎w���v�f���擾����(��const��)
		* @detail	���X�g�̎Q�Ƃ��Ȃ��ꍇ���s�ɂȂ�B
		* 			�m�[�h�̓_�~�[�̏ꍇ���s�ɂȂ�B
		* @return	�w�����v�f��Ԃ�
		********************************************************/
		DataType& operator*();

		friend DoubleLinkedList;
	};

private:
	/*********************************************************
	* @brief	�_�~�[�m�[�h�ւ̃|�C���^�@�擪�Ɩ����̔��f�p 
	* @detail	m_pDummy->pPrev�͍Ō�̗v�f���w���Am_pDummy->pNext�͐擪�v�f���w��
	********************************************************/
	Node* m_pDummy;

public:
	/*********************************************************
	* @brief	�f�X�g���N�^
	* @detail	���I�쐬�����m�[�h��S�����
	********************************************************/
	~DoubleLinkedList();

	/*********************************************************
	* @brief	�R���X�g���N�^
	* @detail	�_�~�[�m�[�h���쐬
	********************************************************/
	DoubleLinkedList();

	/*********************************************************
	* @brief	�f�[�^�̑}��
	* @detail	�C�e���[�^���L���ł��邩���m�F�A
	*			�L���ł͂Ȃ������m�F�B
	* @return	�}�������̏ꍇtrue��Ԃ�
	*			�}�����s�̏ꍇfalse��Ԃ�
	********************************************************/
	bool Insert(ConstIterator& position, const DataType& data);

	/*********************************************************
	* @brief	�f�[�^�̍폜
	* @detail	���X�g����ł͂Ȃ����̊m�F�A
	*			��ł͂Ȃ��ꍇ�C�e���[�^���L���ł��邩�̊m�F�A
	*			�L���̏ꍇ�_�~�[�ł͂Ȃ����̊m�F�B
	* @return	�폜�����̏ꍇtrue��Ԃ�
	*			�폜���s�̏ꍇfalse��Ԃ�
	********************************************************/
	bool Remove(ConstIterator& position);

	/*********************************************************
	* @brief	�擪�C�e���[�^�擾����
	* @detail	���X�g����ł���ꍇ�A�_�~�[�m�[�h���w���C�e���[�^��Ԃ��A
	*			��ł͂Ȃ��ꍇ�A�擪�m�[�h���w���C�e���[�^��Ԃ��B
	* @return	�擪�C�e���[�^��Ԃ�
	********************************************************/
	Iterator Begin();

	/*********************************************************
	* @brief	�����C�e���[�^�擾����
	* @detail	�_�~�[�m�[�h���w���C�e���[�^��Ԃ��B
	* @return	�����C�e���[�^��Ԃ�
	********************************************************/
	Iterator End();


	//const���\�b�h

	/*********************************************************
	* @brief	�f�[�^�����擾����
	* @detail	���[�v�ŉ��Z���āA�f�[�^�����v�Z����B
	*			const���\�b�h�ł���B
	* @return	�f�[�^����Ԃ�
	********************************************************/
	int Count()const;

	/*********************************************************
	* @brief	�擪�R���X�g�C�e���[�^�擾����
	* @detail	���X�g����ł���ꍇ�A�_�~�[�m�[�h���w���R���X�g�C�e���[�^��Ԃ�
	*			��ł͂Ȃ��ꍇ�A�擪�m�[�h���w���R���X�g�C�e���[�^��Ԃ��B
	* @return	�擪�R���X�g�C�e���[�^��Ԃ�
	********************************************************/
	ConstIterator CBegin()const;

	/*********************************************************
	* @brief	�����C�e���[�^�擾����
	* @detail	�_�~�[�m�[�h���w���R���X�g�C�e���[�^��Ԃ��B
	* @return	�����R���X�g�C�e���[�^��Ԃ�
	********************************************************/
	ConstIterator CEnd()const;
};

#include "DoubleLinkedList.inl"