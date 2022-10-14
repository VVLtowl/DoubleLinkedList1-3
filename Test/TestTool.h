/*********************************************************
* @brief		テスト補助のクラスと関数
* @date			2022/10/12
********************************************************/
#pragma once

#include "gtest/gtest.h"
#include "../DoubleLinkedList/DoubleLinkedList.h"
#include "../DoubleLinkedList/ScoreData.h"
#include <string>


//========== 指定要素数のリストのフィクスチャ ==========
class ListFixture : public ::testing::Test
{
protected:
	/*********************************************************
	* @brief		テスト用リスト
	********************************************************/
	DoubleLinkedList<ScoreData> list;

	/*********************************************************
	* @brief		先頭要素を指すイテレータ
	********************************************************/
	DoubleLinkedList<ScoreData>::Iterator headIter;

	/*********************************************************
	* @brief		中間要素を指すイテレータ
	********************************************************/
	DoubleLinkedList<ScoreData>::Iterator middleIter;

	/*********************************************************
	* @brief		最後の要素を指すイテレータ
	********************************************************/
	DoubleLinkedList<ScoreData>::Iterator tailIter;

	/*********************************************************
	* @brief		末尾要素を指すイテレータ
	********************************************************/
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
	* @brief		要素を1つだけ入れる
	********************************************************/
	void InputOneData()
	{
		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;

		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		//テスト用イテレータの準備
		headIter = list.Begin();
		middleIter = list.Begin(); ++middleIter;
		tailIter = list.End();--tailIter;
		endIter = list.End();

		UpdateIterator();
	}

	/*********************************************************
	* @brief		要素を2つ入れる
	********************************************************/
	void InputTwoData()
	{
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

		UpdateIterator();
	}

	/*********************************************************
	* @brief		要素を3つ入れる
	********************************************************/
	void InputThreeData()
	{
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
	* @brief		2つ以上、指定要素数で入れる
	* @param		count: 要素数[2,5]
	********************************************************/
	void InputDatas(int count)
	{
		ScoreData data;
		DoubleLinkedList<ScoreData>::Iterator end;
		int dataNum = count;

		//作成数を制限
		if (dataNum < 2)dataNum = 2;
		if (dataNum > 5)dataNum = 5;

		//先頭を作成し、リストに入れる
		data.score = 10;
		data.name = "head";
		end = list.End();
		list.Insert(end, data);

		//中間を作成し、リストに入れる
		for (int i = 1; i < dataNum-1; i++)
		{
			data.score = 10 + i;
			data.name = "middle" + std::to_string(i - 1);//名前で区別させる
			end = list.End();
			list.Insert(end, data);
		}

		//最後の要素を作成し、リストに入れる
		data.score = 10 + dataNum - 1;
		data.name = "tail";
		end = list.End();
		list.Insert(end, data);

		UpdateIterator();
	}

	/*********************************************************
	* @brief		テスト用の先頭、中間、最後の要素、末尾イテレータの準備
	********************************************************/
	void UpdateIterator()
	{
		//リストが空である場合、設置しない
		if (list.Count() == 0)
			return;

		//テスト用イテレータの準備
		headIter = list.Begin();
		middleIter = list.Begin(); ++middleIter;//中間要素を取得
		tailIter = list.End(); --tailIter;//最後の要素を取得
		endIter = list.End();
	}
};
