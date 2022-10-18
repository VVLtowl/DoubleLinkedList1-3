/*********************************************************
* @brief		�e�X�g�⏕�̃N���X�Ɗ֐�
* @date			2022/10/12
********************************************************/
#pragma once

#include "gtest/gtest.h"
#include "../DoubleLinkedList/DoubleLinkedList.h"
#include "../DoubleLinkedList/ScoreData.h"
#include <string>


/*********************************************************
* @brief		�w��v�f���̃��X�g�̃t�B�N�X�`��
********************************************************/
class ListFixture : public ::testing::Test
{
protected:
	// @brief		�e�X�g�p���X�g
	DoubleLinkedList<ScoreData> list;

	// @brief		�擪�v�f���w���C�e���[�^
	DoubleLinkedList<ScoreData>::Iterator headIter;

	// @brief		���ԗv�f���w���C�e���[�^
	DoubleLinkedList<ScoreData>::Iterator middleIter;

	// @brief		�Ō�̗v�f���w���C�e���[�^
	DoubleLinkedList<ScoreData>::Iterator tailIter;

	// @brief		�����v�f���w���C�e���[�^
	DoubleLinkedList<ScoreData>::Iterator endIter;

protected:
	virtual void SetUp(void)
	{
		//list = new DoubleLinkedList();
	}

	virtual void TearDown(void)
	{
		//delete list;
	}

	/*********************************************************
		* @brief		�v�f��1���������
		********************************************************/
	void InputOneData()
	{
		ClearList();

		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;

		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		//�e�X�g�p�C�e���[�^�̏���
		headIter = list.Begin();
		middleIter = list.Begin(); ++middleIter;
		tailIter = list.End(); --tailIter;
		endIter = list.End();

		UpdateIterator();
	}

	/*********************************************************
	* @brief		�v�f��2�����
	********************************************************/
	void InputTwoData()
	{
		ClearList();

		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;

		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		data.score = 11;
		data.name = "tail";
		end = list.End();
		list.Insert(end, data);

		//�e�X�g�p�C�e���[�^�̏���
		headIter = list.Begin();
		middleIter = list.Begin(); ++middleIter;
		tailIter = list.End(); --tailIter;
		endIter = list.End();

		UpdateIterator();
	}

	/*********************************************************
	* @brief		�v�f��3�����
	********************************************************/
	void InputThreeData()
	{
		ClearList();

		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;

		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		data.score = 11;
		data.name = "middle";
		end = list.End();
		list.Insert(end, data);

		data.score = 12;
		data.name = "tail";
		end = list.End();
		list.Insert(end, data);

		UpdateIterator();
	}

	/*********************************************************
	* @brief		2�ȏ�A�w��v�f���œ����
	* @param		count: �v�f��[2,5]
	********************************************************/
	void InputDatas(int count)
	{
		ClearList();

		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;
		int dataNum = count;

		//�쐬���𐧌�
		if (dataNum < 2)dataNum = 2;
		if (dataNum > 5)dataNum = 5;

		//�擪���쐬���A���X�g�ɓ����
		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		//���Ԃ��쐬���A���X�g�ɓ����
		for (int i = 1; i < dataNum - 1; i++)
		{
			data.score = 10 + i;
			data.name = "middle" + std::to_string(i - 1);//���O�ŋ�ʂ�����
			end = list.End();
			list.Insert(end, data);
		}

		//�Ō�̗v�f���쐬���A���X�g�ɓ����
		data.score = 10 + dataNum - 1;
		data.name = "tail";
		end = list.End();
		list.Insert(end, data);

		UpdateIterator();
	}

	/*********************************************************
	* @brief		�e�X�g�p�̐擪�A���ԁA�Ō�̗v�f�A�����C�e���[�^�̏���
	********************************************************/
	void UpdateIterator()
	{
		//���X�g����ł���ꍇ�A�ݒu���Ȃ�
		if (list.Count() == 0)
			return;

		//�e�X�g�p�C�e���[�^�̏���
		headIter = list.Begin();
		middleIter = list.Begin(); ++middleIter;//���ԗv�f���擾
		tailIter = list.End(); --tailIter;//�Ō�̗v�f���擾
		endIter = list.End();
	}

	/*********************************************************
	* @brief		���X�g���󂭂���
	********************************************************/
	void ClearList()
	{
		//��̏ꍇ�I��
		if (list.Count() == 0)
		{
			return;
		}

		//��������S���폜
		auto iter = list.End();
		iter--;
		auto del = iter;
		while (del != list.Begin())
		{
			iter--;
			list.Remove(del);
			del = iter;
		}
		list.Remove(del);//�擪���폜
	}
};

/*********************************************************
* @brief		�v�f�͊��҂����l�ł��邩�̊m�F
* @details		���҂����l�̔z���n���ă��X�g���̗v�f����v���邩���肷��
* @param		datas: ���҂����l�̔z��
* @param		count: �l�̌�
* @param		list: ��r���郊�X�g
********************************************************/
inline bool CheckListValue(const ScoreData* datas, const int count, const DoubleLinkedList<ScoreData>& list)
{
	auto iter = list.CBegin();

	//���҂����l�ł͂Ȃ��ꍇfalse�ŏI��
	{
		for (int i = 0; i < count; i++, iter++)
		{
			if (datas[i].name != (*iter).name ||
				datas[i].score != (*iter).score)
			{
				return false;
			}
		}
	}

	return true;
}

/*********************************************************
* @brief		�����C�e���[�^�ł��邩���m�F
* @details		��O�̗v�f�������v�f�ł��邱�Ƃ��m�F����
* @param		iter: ���f�������C�e���[�^
* @param		tail: �����v�f�̃f�[�^
********************************************************/
inline bool IsDummy(DoubleLinkedList<ScoreData>::ConstIterator iter, const ScoreData& tail)
{
	iter--;
	return (tail.name == (*iter).name && tail.score == (*iter).score);
}