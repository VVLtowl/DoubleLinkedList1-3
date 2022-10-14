/*********************************************************
* @brief		イテレータ単体テストのテスト
* @date			2022/10/11
********************************************************/
#include "gtest/gtest.h"
#include "../DoubleLinkedList/DoubleLinkedList.h"
#include "../DoubleLinkedList/ScoreData.h"
#include "TestTool.h"

//イテレータの単体テスト
#define GT_AUTO_TEST_ITERATOR

namespace ex02_ConstIterator
{
#if defined GT_AUTO_TEST_ITERATOR

#pragma region ========== イテレータの指す要素を取得 ==========

	using IteratorGetDataTest_F = ListFixture;

	/*********************************************************
	* @brief		リストの参照がない状態で呼び出した際の挙動
	* @details		ID:1-0
	* 				リストの参照がない状態で呼び出した際に、
	*				assert発生するかを確認します。
	********************************************************/
	TEST(IteratorGetDataTest, WhenNoReference)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData>::Iterator iter;//リストの参照がないイテレータを作成

		EXPECT_DEATH((*iter), "iterator: no reference");
#else
		SUCCEED();
#endif
	}

	/*********************************************************
	* @brief		Iteratorから取得した要素に対して、値の代入が行えるかをチェック
	* @details		ID:1-1
	*				Iteratorから取得した要素に対して、
	*				値の代入が行えるかをチェックします。
	********************************************************/
	TEST_F(IteratorGetDataTest_F, AfterAssignData)
	{
		InputOneData();

		//初期値を取得
		int initScore = (*headIter).score;
		std::string initName = (*headIter).name;

		//変更前は初期値と同じ
		EXPECT_EQ(10, (*headIter).score);
		EXPECT_EQ("head", (*headIter).name);

		//Iteratorから取得した要素に対して、値を代入
		auto iter = list.Begin();
		(*iter).score = initScore + 10;
		(*iter).name = initName + "Change";

		//変更後は初期値と異なる
		EXPECT_NE(10, (*headIter).score);
		EXPECT_NE("head", (*headIter).name);
		EXPECT_EQ(20, (*headIter).score);
		EXPECT_EQ("headChange", (*headIter).name);
	}

	/*********************************************************
	* @brief		リストが空の際の、先頭イテレータに対して呼び出した際の挙動
	* @details		ID:1-3
	*				リストが空の際の、先頭イテレータに対して呼び出した際に、
	* 				assert発生するかを確認します。
	********************************************************/
	TEST(IteratorGetDataTest, ByConstIterator)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData> list;
		EXPECT_EQ(0, list.Count());//リストが空であるかをチェック

		auto iter = list.Begin();
		EXPECT_DEATH((*iter), "iterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		末尾イテレータに対して呼び出した際の挙動
	* @details		ID:1-4
	*				末尾イテレータに対して呼び出した際に、
	* 				assert発生するかを確認します。
	********************************************************/
	TEST(IteratorGetDataTest, GetFromEnd)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData> list;
		auto iter = list.End();
		EXPECT_DEATH((*iter), "iterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}
#pragma endregion

#pragma region ========== イテレータをリストの末尾に向かって一つ進める ==========

	using IteratorIncrementTest_F = ListFixture;

	/*********************************************************
	* @brief		リストの参照がない状態で呼び出した際の挙動
	* @details		ID:1-5
	* 				リストの参照がない状態で呼び出した際に、
	*				assert発生するかを確認します。
	********************************************************/
	TEST(IteratorIncrementTest, WhenNoReference)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData>::Iterator iter;
		EXPECT_DEATH((++iter), "pre increment: no reference");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		リストが空の際の、先頭イテレータに対して呼び出した際の挙動
	* @details		ID:1-6
	* 				リストが空の際の、先頭イテレータに対して呼び出した際に、
	*				assert発生するかを確認します。
	********************************************************/
	TEST(IteratorIncrementTest, WhenEmptyList_IncrementBegin)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData> list;//空リストを作成
		auto iter = list.Begin();
		EXPECT_DEATH((++iter), "pre increment: dummy cant increment");
#else
		SUCCEED();
#endif // DEBUG
	}

	/*********************************************************
	* @brief		末尾イテレータに対して呼び出した際の挙動
	* @details		ID:1-7
	* 				末尾イテレータに対して呼び出した際に、
	*				assert発生するかを確認します。
	********************************************************/
	TEST(IteratorIncrementTest, IncrementEnd)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData> list;
		auto iter = list.End();
		EXPECT_DEATH((++iter), "pre increment: dummy cant increment");
#else
		SUCCEED();
#endif // DEBUG
	}

	/*********************************************************
	* @brief		リストに二つ以上の要素がある場合に呼び出した際の挙動
	* @details		ID:1-8
	* 				リストに二つ以上の要素がある場合に呼び出した際に、
	*				次の要素を指すのかを確認します。
	********************************************************/
	TEST_F(IteratorIncrementTest_F, WhenManyElements)
	{
		//二つ以上の要素があるリストを作成
		InputThreeData();//list: {10,"head"} {11,"middle"} {12,"tail"}

		//リストの先頭から末尾まで呼び出しを行い、
		//期待されている要素が格納されているかを確認
		auto iter = list.Begin();
		EXPECT_EQ(10, (*iter).score);
		EXPECT_EQ("head", (*iter).name);
		++iter;
		EXPECT_EQ(11, (*iter).score);
		EXPECT_EQ("middle", (*iter).name);
		++iter;
		EXPECT_EQ(12, (*iter).score);
		EXPECT_EQ("tail", (*iter).name);
	}

	/*********************************************************
	* @brief		前置インクリメントを行った際の挙動
	* @details		ID:1-9
	* 				前置インクリメントを行った際に、
	*				次の要素を指すのかを確認します。
	********************************************************/
	TEST_F(IteratorIncrementTest_F, PreIncrement)
	{
		//二つ以上の要素があるリストを作成
		InputThreeData();//list: {10,"head"} {11,"middle"} {12,"tail"}
		auto iter = list.Begin();

		//指している要素はhead、次はmiddleのはず
		EXPECT_EQ(10, (*iter).score);
		EXPECT_EQ("head", (*iter).name);

		//移動した後、middleであるかを確認
		++iter;
		EXPECT_EQ(11, (*iter).score);
		EXPECT_EQ("middle", (*iter).name);
	}

	/*********************************************************
	* @brief		後置インクリメントを行った際の挙動
	* @details		ID:1-10
	* 				後置インクリメントを行った際に、
	*				次の要素を指すのかを確認します。
	********************************************************/
	TEST_F(IteratorIncrementTest_F, PostIncrement)
	{
		//二つ以上の要素があるリストを作成
		InputThreeData();//list: {10,"head"} {11,"middle"} {12,"tail"}
		auto iter = list.Begin();

		//指している要素はhead、次はmiddleのはず
		EXPECT_EQ(10, (*iter).score);
		EXPECT_EQ("head", (*iter).name);

		//移動した後、middleであるかを確認
		iter++;
		EXPECT_EQ(11, (*iter).score);
		EXPECT_EQ("middle", (*iter).name);
	}
#pragma endregion

#pragma region ========== イテレータをリストの先頭に向かって一つ進める ==========

	using IteratorDecrementTest_F = ListFixture;

	/*********************************************************
	* @brief		リストの参照がない状態で呼び出した際の挙動
	* @details		ID:1-11
	* 				リストの参照がない状態で呼び出した際に、
	*				assert発生するかを確認します。
	********************************************************/
	TEST(IteratorDecrementTest, WhenNoReference)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData>::Iterator iter;
		EXPECT_DEATH((--iter), "pre decrement: no reference");
#else
		SUCCEED();
#endif // DEBUG
	}

	/*********************************************************
	* @brief		リストが空の際の、末尾イテレータに対して呼び出した際の挙動
	* @details		ID:1-12
	* 				リストが空の際の、末尾イテレータに対して呼び出した際に、
	*				assert発生するかを確認します。
	********************************************************/
	TEST(IteratorDecrementTest, WhenEmptyList_DecrementEnd)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData> list;//空であるリストを作成
		auto iter = list.End();
		EXPECT_DEATH((--iter), "pre decrement: list is empty");
#else
		SUCCEED();
#endif // DEBUG
	}

	/*********************************************************
	* @brief		先頭イテレータに対して呼び出した際の挙動
	* @details		ID:1-13
	* 				先頭イテレータに対して呼び出した際に、
	*				assert発生するかを確認します。
	********************************************************/
	TEST_F(IteratorDecrementTest_F, DecrementBegin)
	{
#ifdef _DEBUG
		//要素のあるリストを作成
		InputOneData();

		//ダミーではない先頭イテレータを取得
		auto iter = list.Begin();

		EXPECT_DEATH((--iter), "pre decrement: begin cant decrement");
#else
		SUCCEED();
#endif // DEBUG
	}

	/*********************************************************
	* @brief		リストに二つ以上の要素がある場合に呼び出した際の挙動
	* @details		ID:1-14
	* 				リストに二つ以上の要素がある場合に呼び出した際に、
	*				前の要素を指すのかを確認します。
	********************************************************/
	TEST_F(IteratorDecrementTest_F, WhenManyElements)
	{
		//二つ以上の要素があるリストを作成
		InputThreeData();//list: {10,"head"} {11,"middle"} {12,"tail"}

		//リストの末尾から先頭まで呼び出しを行い、
		//期待されている要素が格納されているかを確認
		auto iter = list.End();
		--iter;//最後の要素から
		EXPECT_EQ(12, (*iter).score);
		EXPECT_EQ("tail", (*iter).name);
		--iter;
		EXPECT_EQ(11, (*iter).score);
		EXPECT_EQ("middle", (*iter).name);
		--iter;
		EXPECT_EQ(10, (*iter).score);
		EXPECT_EQ("head", (*iter).name);
	}

	/*********************************************************
	* @brief		前置デクリメントを行った際の挙動
	* @details		ID:1-15
	* 				前置デクリメントを行った際に、
	*				前の要素を指すのかを確認します。
	********************************************************/
	TEST_F(IteratorDecrementTest_F, PreDecrement)
	{
		//二つ以上の要素があるリストを作成
		InputThreeData();//list: {10,"head"} {11,"middle"} {12,"tail"}
		auto iter = list.End();
		--iter;//最後の要素から

		//指している要素はtail、前はmiddleのはず
		EXPECT_EQ(12, (*iter).score);
		EXPECT_EQ("tail", (*iter).name);

		//移動した後、middleであるかを確認
		--iter;
		EXPECT_EQ(11, (*iter).score);
		EXPECT_EQ("middle", (*iter).name);
	}

	/*********************************************************
	* @brief		後置デクリメントを行った際の挙動
	* @details		ID:1-15
	* 				後置デクリメントを行った際に、
	*				前の要素を指すのかを確認します。
	********************************************************/
	TEST_F(IteratorDecrementTest_F, PostDecrement)
	{
		//二つ以上の要素があるリストを作成
		InputThreeData();//list: {10,"head"} {11,"middle"} {12,"tail"}
		auto iter = list.End();
		iter--;//最後の要素から

		//指している要素はtail、前はmiddleのはず
		EXPECT_EQ(12, (*iter).score);
		EXPECT_EQ("tail", (*iter).name);

		//移動した後、middleであるかを確認
		iter--;
		EXPECT_EQ(11, (*iter).score);
		EXPECT_EQ("middle", (*iter).name);
	}
#pragma endregion

#pragma region ========== イテレータのコピーを行う ==========

	using IteratorCopyTest_F = ListFixture;

	/*********************************************************
	* @brief		コピーコンストラクト後の値がコピー元と等しいことをチェック
	* @details		ID:1-18
	* 				コピーコンストラクト後の値がコピー元と等しいことをチェックします。
	********************************************************/
	TEST_F(IteratorCopyTest_F, AfterCopy_CheckDataEqual)
	{
		InputOneData();//list: {10,"head"}

		//コピーコンストラクト
		auto iter(list.Begin());

		//コピーとコピー元の値を比較
		EXPECT_EQ(
			(*list.Begin()).score,
			(*iter).score);
		EXPECT_EQ(
			(*list.Begin()).name,
			(*iter).name);
	}
#pragma endregion

#pragma region ========== イテレータの代入を行うテスト ==========

	using IteratorAssignTest_F = ListFixture;

	/*********************************************************
	* @brief		代入後の値がコピー元と等しいことをチェック
	* @details		ID:1-20
	* 				代入後の値がコピー元と等しいことをチェックします。
	********************************************************/
	TEST_F(IteratorAssignTest_F, AfterAssign_CheckDataEqual)
	{
		InputOneData();//list: {10,"head"}

		//代入
		auto iter = list.Begin();

		//代入後の値とコピー元の値を比較
		EXPECT_EQ(
			(*list.Begin()).score,
			(*iter).score);
		EXPECT_EQ(
			(*list.Begin()).name,
			(*iter).name);
	}
#pragma endregion

#pragma region ========== 同一もののイテレータであるかの比較 ==========

	using IteratorEqualTest_F = ListFixture;

	/*********************************************************
	* @brief		リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
	* @details		ID:1-21
	* 				リストが空の状態での先頭イテレータと末尾イテレータを比較した際に、
	*				trueが返る場合成功です。
	********************************************************/
	TEST(IteratorEqualTest, WhenEmptyList_CheckBeginAndEnd)
	{
		DoubleLinkedList<ScoreData> list;

		//リストが空の状態で、先頭も末尾もダミーである
		auto begin = list.Begin();
		auto end = list.End();

		EXPECT_TRUE(begin == end);
	}

	/*********************************************************
	* @brief		同一のイテレータを比較した際の挙動
	* @details		ID:1-22
	* 				同一のイテレータを比較した際に、
	*				trueが返る場合成功です。
	********************************************************/
	TEST_F(IteratorEqualTest_F, WhenEmptyList_CheckSame)
	{
		InputOneData();

		//同じ要素を指す二つのイテレータを作成
		auto iter1 = list.Begin();
		auto iter2 = list.Begin();

		EXPECT_TRUE(iter1 == iter2);
	}

	/*********************************************************
	* @brief		異なるイテレータを比較した際の挙動
	* @details		ID:1-23
	* 				異なるイテレータを比較した際に、
	*				falseが返る場合成功です。
	********************************************************/
	TEST_F(IteratorEqualTest_F, WhenEmptyList_CheckDifferent)
	{
		InputTwoData();

		//異なる要素を指す二つのイテレータを作成
		auto iter1 = headIter;
		auto iter2 = middleIter;

		EXPECT_FALSE(iter1 == iter2);
	}
#pragma endregion

#pragma region ========== 異なるイテレータであるかの比較 ==========

	using IteratorNotEqualTest_F = ListFixture;

	/*********************************************************
	* @brief		リストが空の状態での先頭イテレータと末尾イテレータを比較した際の挙動をチェック
	* @details		ID:1-24
	* 				リストが空の状態での先頭イテレータと末尾イテレータを比較した際に、
	*				trueが返る場合成功です。
	********************************************************/
	TEST(IteratorNotEqualTest, WhenEmptyList_CheckBeginAndEnd)
	{
		DoubleLinkedList<ScoreData> list;

		//リストが空の状態で、先頭も末尾もダミーである
		auto begin = list.Begin();
		auto end = list.End();

		EXPECT_FALSE(begin != end);
	}

	/*********************************************************
	* @brief		同一のイテレータを比較した際の挙動
	* @details		ID:1-25
	* 				同一のイテレータを比較した際に、
	*				trueが返る場合成功です。
	********************************************************/
	TEST_F(IteratorNotEqualTest_F, WhenEmptyList_CheckSame)
	{
		InputOneData();

		//同じ要素を指す二つのイテレータを作成
		auto iter1 = headIter;
		auto iter2 = headIter;

		EXPECT_FALSE(iter1 != iter2);
	}

	/*********************************************************
	* @brief		異なるイテレータを比較した際の挙動
	* @details		ID:1-26
	* 				異なるイテレータを比較した際に、
	*				falseが返る場合成功です。
	********************************************************/
	TEST_F(IteratorNotEqualTest_F, WhenEmptyList_CheckDifferent)
	{
		InputTwoData();

		//異なる要素を指す二つのイテレータを作成
		auto iter1 = headIter;
		auto iter2 = middleIter;

		EXPECT_TRUE(iter1 != iter2);
	}
#pragma endregion

#endif
}