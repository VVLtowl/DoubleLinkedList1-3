/*********************************************************
* @brief		双方向リストの単体テスト
* @date			2022/10/11
********************************************************/
#include "gtest/gtest.h"
#include "../DoubleLinkedList/DoubleLinkedList.h"
#include "../DoubleLinkedList/ScoreData.h"
#include "TestTool.h"

//双方向リストの単体テスト
#define GT_AUTO_TEST_LIST

//双方向リストの手動テスト
//#define GT_MANUAL_TEST_LIST

namespace ex01_DoubleLinkedList
{
#if defined GT_AUTO_TEST_LIST

#pragma region ========== データ数の取得 ==========

	using ListCountTest_F = ListFixture;

	/*********************************************************
	* @brief		リストが空である場合の戻り値
	* @details		ID:0-0
	* 				リストが空である場合、
	*				データ数の取得関数の戻り値を確認します。
	*				戻り値が0の場合成功です。
	********************************************************/
	TEST(ListCountTest, WhenEmptyList)
	{
		DoubleLinkedList<ScoreData> list;
		EXPECT_EQ(0, list.Count());
	}

	/*********************************************************
	* @brief		リスト末尾への挿入を行った際の戻り値
	* @details		ID:0-1
	* 				リスト末尾への挿入を行った際に、
	*				データ数の取得関数の戻り値を確認します。
	*				戻り値が1の場合成功です。
	********************************************************/
	TEST(ListCountTest, WhenInsertToEndSucceed)
	{
		DoubleLinkedList<ScoreData> list;

		//末尾への挿入を成功させる
		auto iter = list.End();
		ScoreData data(10, "element0");
		EXPECT_TRUE(list.Insert(iter, data));

		EXPECT_EQ(1, list.Count());
	}

	/*********************************************************
	* @brief		リスト末尾への挿入が失敗した際の戻り値
	* @details		ID:0-2
	* 				リスト末尾への挿入が失敗した際に、
	*				データ数の取得関数の戻り値を確認します。
	*				戻り値が0の場合成功です。
	********************************************************/
	TEST(ListCountTest, WhenInsertToEndFailed)
	{
		DoubleLinkedList<ScoreData> list;
		DoubleLinkedList<ScoreData> otherList;

		//末尾への挿入を失敗させる
		auto iter = otherList.End();//別リストのイテレータで失敗を起こす
		ScoreData data;
		EXPECT_FALSE(list.Insert(iter, data));

		EXPECT_EQ(0, list.Count());
	}

	/*********************************************************
	* @brief		データの挿入を行った際の戻り値
	* @details		ID:0-3
	* 				データの挿入を行った際に、
	*				データ数の取得関数の戻り値を確認します。
	*				戻り値が1の場合成功です。
	********************************************************/
	TEST(ListCountTest, WhenInsertSucceed)
	{
		DoubleLinkedList<ScoreData> list;

		//挿入を行った
		auto iter = list.Begin();
		ScoreData data(10, "element0");
		EXPECT_TRUE(list.Insert(iter, data));

		EXPECT_EQ(1, list.Count());
	}

	/*********************************************************
	* @brief		データの挿入に失敗した際の戻り値
	* @details		ID:0-4
	* 				データの挿入に失敗した際に、
	*				データ数の取得関数の戻り値を確認します。
	*				戻り値が0の場合成功です。
	********************************************************/
	TEST(ListCountTest, WhenInsertFailed)
	{
		DoubleLinkedList<ScoreData> list;
		DoubleLinkedList<ScoreData> otherList;

		//挿入を失敗させる
		auto iter = otherList.Begin();//別リストのイテレータで失敗を起こす
		ScoreData data;
		EXPECT_FALSE(list.Insert(iter, data));

		EXPECT_EQ(0, list.Count());
	}

	/*********************************************************
	* @brief		データの削除を行った際の戻り値
	* @details		ID:0-5
	* 				データの削除を行った際に、
	*				データ数の取得関数の戻り値を確認します。
	*				戻り値が0の場合成功です。
	********************************************************/
	TEST_F(ListCountTest_F, WhenRemoveSucceed)
	{
		InputOneData();

		//削除を行った
		auto iter = list.Begin();
		EXPECT_TRUE(list.Remove(iter));

		EXPECT_EQ(0, list.Count());
	}

	/*********************************************************
	* @brief		データの削除が失敗した際の戻り値
	* @details		ID:0-6
	* 				データを挿入した後、削除した場合、削除が失敗した際に、
	*				データ数の取得取得関数の戻り値を確認します。
	*				戻り値が1の場合成功です。
	********************************************************/
	TEST_F(ListCountTest_F, WhenRemoveFailed)
	{
		InputOneData();

		//無効なイテレータから、削除を失敗させる
		DoubleLinkedList<ScoreData>::Iterator iter;
		EXPECT_FALSE(list.Remove(iter));

		EXPECT_EQ(1, list.Count());
	}

	/*********************************************************
	* @brief		リストが空である場合に、データの削除を行った際の戻り値
	* @details		ID:0-7
	*				マイナスにならないかを確認するため、
	* 				リストが空である場合に、データの削除を行った際に、
	*				データ数の取得関数の戻り値を確認します。
	*				戻り値が0の場合成功です。
	********************************************************/
	TEST(ListCountTest, WhenEmptyListAndRemove)
	{
		DoubleLinkedList<ScoreData> list;
		auto iter = list.Begin();
		EXPECT_FALSE(list.Remove(iter));

		EXPECT_EQ(0, list.Count());
	}

#pragma endregion

#pragma region ========== データの挿入 ==========

	using ListInsertTest_F = ListFixture;

	/*********************************************************
	* @brief		リストが空である場合に、挿入した際の挙動
	* @details		ID:0-9
	* 				リストが空である場合に、新要素をイテレータの指す位置に挿入します。
	*				先頭イテレータ、末尾イテレータを引数で渡した場合について、個別に挙動をチェックします。
	*				データの挿入関数の戻り値を確認します。
	*				戻り値がtrueの場合成功です。
	********************************************************/
	TEST(ListInsertTest, WhenEmptyList)
	{
		//先頭イテレータの指す位置に挿入
		DoubleLinkedList<ScoreData> list1;
		auto head = list1.Begin();
		ScoreData data1(10, "element0");
		EXPECT_TRUE(list1.Insert(head, data1));

		//末尾イテレータの指す位置に挿入
		DoubleLinkedList<ScoreData> list2;
		auto end = list2.End();
		ScoreData data2(11, "element1");
		EXPECT_TRUE(list2.Insert(end, data2));
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動
	* @details		ID:0-10
	* 				リストに複数の要素がある場合に、先頭イテレータを渡して、挿入します。
	*				先頭に要素が挿入され、元々先頭だった要素が２番目になります。
	*				データの挿入関数の戻り値を確認します。
	*				戻り値がtrueの場合成功です。
	********************************************************/
	TEST_F(ListInsertTest_F, WhenNotEmptyList_InsertToHead)
	{
		//複数要素のあるリストを作成
		InputTwoData();

		//先頭イテレータを渡して、新要素を挿入
		auto head = list.Begin();
		auto headData(*head);//元々先頭だった要素
		ScoreData newData(20, "newElement");
		EXPECT_TRUE(list.Insert(head, newData));

		//元々先頭だった要素が２番目になってるかをチェック
		auto iter = list.Begin();
		++iter;
		EXPECT_EQ(headData.score, (*iter).score);
		EXPECT_EQ(headData.name, (*iter).name);
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動
	* @details		ID:0-11
	* 				リストに複数の要素がある場合に、末尾イテレータを渡して、挿入します。
	*				イテレータの指す位置に要素が挿入されます。
	*				データの挿入関数の戻り値を確認します。
	*				戻り値がtrueの場合成功です。
	********************************************************/
	TEST_F(ListInsertTest_F, WhenNotEmptyList_InsertToTail)
	{
		//複数要素のあるリストを作成
		InputTwoData();

		//末尾イテレータを渡して、新要素を挿入
		auto end = list.End();
		ScoreData data(20, "newElement");
		EXPECT_TRUE(list.Insert(end, data));
	}

	/*********************************************************
	* @brief		リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して挿入した際の挙動
	* @details		ID:0-12
	* 				リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して、挿入します。
	*				イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれます。
	*				データの挿入関数の戻り値を確認します。
	*				戻り値がtrueの場合成功です。
	********************************************************/
	TEST_F(ListInsertTest_F, WhenNotEmptyList_InsertToMiddle)
	{
		//複数要素のあるリストを作成
		InputTwoData();

		//中央イテレータを渡して、新要素を挿入
		auto iter = list.Begin();
		++iter;//中央へ移動
		ScoreData data(20, "newElement");
		EXPECT_TRUE(list.Insert(iter, data));
	}

	/*********************************************************
	* @brief		ConstIteratorを指定して挿入を行った際の挙動
	* @details		ID:0-13
	* 				ConstIteratorを指定して、挿入します。
	*				イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれます。
	*				データの挿入関数の戻り値を確認します。
	*				戻り値がtrueの場合成功です。
	*
	*				格納済みの要素に影響がないか、期待される位置に要素が格納されているか。
	*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
	********************************************************/
	TEST_F(ListInsertTest_F, WhenNotEmptyList_InsertByConstIterator)
	{
		//複数要素のあるリストを作成
		InputTwoData();

		//先頭イテレータを渡して、新要素を挿入
		auto constHead = list.CBegin();
		ScoreData newData0(20, "newElement0");
		EXPECT_TRUE(list.Insert(constHead, newData0));

		//中央イテレータを渡して、新要素を挿入
		auto constIter = list.CBegin();
		++constIter;//中央へ移動
		ScoreData newData1(21, "newElement1");
		EXPECT_TRUE(list.Insert(constIter, newData1));

		//末尾イテレータを渡して、新要素を挿入
		auto constEnd = list.CEnd();
		ScoreData newData2(22, "newElement2");
		EXPECT_TRUE(list.Insert(constEnd, newData2));

	}

	/*********************************************************
	* @brief		不正なイテレータを渡して、挿入した場合の挙動
	* @details		ID:0-14
	* 				リストの参照がないイテレータ、別リストの要素を指すイテレータを渡した際の挙動などを確認します。
	*				リストの参照がないイテレータを指定したり、
	*				別リストの要素を指すイテレータを渡したりして、挿入します。
	*				イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれます。
	*				データの挿入関数の戻り値を確認します。
	*				戻り値がtrueの場合成功です。
	*
	********************************************************/
	TEST(ListInsertTest, WhenNotEmptyList_InsertWrongIterator)
	{
		DoubleLinkedList<ScoreData> list;
		ScoreData data0(10, "element0");
		auto iter = list.Begin();
		list.Insert(iter, data0);


		//別リストを作成
		DoubleLinkedList<ScoreData> otherList;
		ScoreData data1(11, "element1");
		iter = otherList.Begin();
		list.Insert(iter, data1);

		//リストの参照がないイテレータ
		DoubleLinkedList<ScoreData>::Iterator noReference;
		ScoreData newData(20, "newElement");
		EXPECT_FALSE(list.Insert(noReference, newData));

		//別リストの要素を指すイテレータ
		DoubleLinkedList<ScoreData>::Iterator wrongList = otherList.Begin();
		EXPECT_FALSE(list.Insert(wrongList, newData));
	}

#pragma endregion

#pragma region ========== データの削除 ==========

	using ListRemoveTest_F = ListFixture;

	/*********************************************************
	* @brief		リストが空である場合に、削除した際の挙動
	* @details		ID:0-16
	* 				リストが空である場合に、新要素をイテレータの指す位置に挿入します。
	*				イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
	*				データの削除関数の戻り値を確認します。
	*				戻り値がfalseの場合成功です。
	********************************************************/
	TEST(ListRemoveTest, WhenEmptyList)
	{
		//先頭要素を削除
		DoubleLinkedList<ScoreData> list1;
		auto head = list1.Begin();
		EXPECT_FALSE(list1.Remove(head));

		//末尾要素を削除
		DoubleLinkedList<ScoreData> list2;
		auto end = list2.End();
		EXPECT_FALSE(list2.Remove(end));
	}

	/*********************************************************
	* @brief		先頭要素の削除の挙動
	* @details		ID:0-17
	* 				リストに複数の要素がある場合に、先頭イテレータを渡して、削除します。
	*				先頭要素が削除されたかを確認します。
	*				データの削除関数の戻り値を確認します。
	*				戻り値がtrueの場合成功です。
	********************************************************/
	TEST_F(ListRemoveTest_F, WhenNotEmptyList_RemoveHead)
	{
		//複数の要素があるリストを作成
		InputTwoData();

		auto head = list.Begin();
		EXPECT_TRUE(list.Remove(head));
	}

	/*********************************************************
	* @brief		末尾要素を削除した際の挙動
	* @details		ID:0-18
	* 				リストに複数の要素がある場合に、末尾イテレータを渡して、削除します。
	*				末尾はダミーノードなので、削除は失敗するはずです。
	*				データの削除関数の戻り値を確認します。
	*				戻り値がfalseの場合成功です。
	********************************************************/
	TEST_F(ListRemoveTest_F, WhenNotEmptyList_RemoveEnd)
	{
		//複数の要素があるリストを作成
		InputTwoData();

		auto end = list.End();
		EXPECT_FALSE(list.Remove(end));
	}

	/*********************************************************
	* @brief		中間要素を削除した際の挙動
	* @details		ID:0-19
	* 				リストに複数の要素がある場合に、先頭でも末尾でもないイテレータを渡して削除した際に、
	*				イテレータに指された要素が削除されたかを確認します。
	*				データの削除関数の戻り値を確認します。
	*				戻り値がtrueの場合成功です。
	********************************************************/
	TEST_F(ListRemoveTest_F, WhenNotEmptyList_RemoveMiddle)
	{
		//複数の要素があるリストを作成
		InputTwoData();

		//中央要素を指すイテレータを作成
		auto iter = list.Begin();
		++iter;
		auto middle = iter;

		EXPECT_TRUE(list.Remove(middle));
	}

	/*********************************************************
	* @brief		ConstIteratorを指定して削除を行った際の挙動
	* @details		ID:0-20
	* 				リストに複数の要素がある場合に、ConstIteratorを指定してした際に、
	*				ConstIteratorに指された要素が削除されたかを確認します。
	*				データの削除関数の戻り値を確認します。
	*				戻り値がtrueの場合成功です。
	********************************************************/
	TEST_F(ListRemoveTest_F, WhenNotEmptyList_RemoveByConstIterator)
	{
		//複数の要素があるリストを作成
		InputTwoData();

		auto constIter = list.CBegin();
		EXPECT_TRUE(list.Remove(constIter));
	}

	/*********************************************************
	* @brief		不正なイテレータを渡して、削除した場合の挙動
	* @details		ID:0-21
	* 				リストの参照がないイテレータ、別リストの要素を指すイテレータなど
	*				不正なイテレータを渡した際に、
	*				データの削除関数の戻り値を確認します。
	*				戻り値がfalseの場合成功です。
	********************************************************/
	TEST(ListRemoveTest, WhenNotEmptyList_RemoveByWrongIterator)
	{
		DoubleLinkedList<ScoreData> list;
		ScoreData data0(10, "element0");
		list.Insert(list.End(), data0);

		//別リストを作成
		DoubleLinkedList<ScoreData> otherList;
		ScoreData data1(11, "element1");
		otherList.Insert(otherList.End(), data1);

		//リストの参照がないイテレータ
		DoubleLinkedList<ScoreData>::Iterator noReference;
		EXPECT_FALSE(list.Remove(noReference));

		//別リストの要素を指すイテレータ
		DoubleLinkedList<ScoreData>::Iterator wrongList = otherList.Begin();
		EXPECT_FALSE(list.Remove(wrongList));
	}

#pragma endregion

#pragma region ========== 先頭イテレータの取得 ==========

	using ListBeginTest_F = ListFixture;

	/*********************************************************
	* @brief		リストが空である場合に、呼び出した際の挙動
	* @details		ID:0-23
	* 				リストが空である場合に、呼び出した際に、
	*				戻り値はダミーノードを指すイテレータの場合成功です。
	********************************************************/
	TEST(ListBeginTest, WhenEmptyList)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData> list;

		//ダミーであるか
		EXPECT_DEATH((*list.Begin()), "iterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		リストに要素が一つある場合に、呼び出した際の挙動
	* @details		ID:0-24
	* 				リストに要素が一つある場合に、呼び出した際に、
	*				先頭要素を指すイテレータが返る場合成功です。
	********************************************************/
	TEST_F(ListBeginTest_F, WhenOneElementList)
	{
		//要素が一つあるリストを作成
		InputOneData();

		//リストに要素が一つであるかをチェック
		EXPECT_EQ(1, list.Count());

		EXPECT_EQ("head", (*list.Begin()).name);
	}

	/*********************************************************
	* @brief		リストに二つ以上の要素がある場合に、呼び出した際の挙動
	* @details		ID:0-25
	* 				リストに二つ以上の要素がある場合に、呼び出した際に、
	*				先頭要素を指すイテレータが返る場合成功です。
	********************************************************/
	TEST_F(ListBeginTest_F, WhenManyElementsList)
	{
		//要素が二つ以上あるリストを作成
		InputThreeData();

		//リストに要素が二つ以上あるかをチェック
		EXPECT_LE(2, list.Count());

		EXPECT_EQ("head", (*list.Begin()).name);
	}

	/*********************************************************
	* @brief		データの挿入を行った後に、呼び出した際の挙動
	* @details		ID:0-26
	* 				データの挿入を行った後に、呼び出した際に、
	*				先頭要素を指すイテレータが返る場合成功です。
	*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
	********************************************************/
	TEST_F(ListBeginTest_F, AfterInsert)
	{
		InputThreeData();
		ScoreData newData(20, "newData");

		//先頭に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(headIter, newData));
		EXPECT_EQ("newData", (*list.Begin()).name);

		//中央に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(middleIter, newData));
		EXPECT_EQ("newData", (*list.Begin()).name);

		//末尾に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(endIter, newData));
		EXPECT_EQ("newData", (*list.Begin()).name);
	}

	/*********************************************************
	* @brief		データの削除を行った後に、呼び出した際の挙動
	* @details		ID:0-27
	* 				データの削除を行った後に、呼び出した際に、
	*				先頭要素を指すイテレータが返る場合成功です。
	*				要素列の先頭、中央、末尾に削除を行った場合の各ケースについてチェックします。
	********************************************************/
	TEST_F(ListBeginTest_F, AfterRemove)
	{
		//3回削除を行うため、データ4つを用意
		InputDatas(4);//list: head middle0 middle1 tail

		//末尾要素を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(tailIter));
		EXPECT_EQ("head", (*list.Begin()).name);	//list: head middle0 middle1

		//中央を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(middleIter));
		EXPECT_EQ("head", (*list.Begin()).name);	//list: head middle1

		//先頭を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(headIter));
		EXPECT_EQ("middle1", (*list.Begin()).name);	//list: middle1
	}

#pragma endregion

#pragma region ========== 先頭コンストイテレータの取得 ==========

	using ListCBeginTest_F = ListFixture;

	/*********************************************************
	* @brief		リストが空である場合に、呼び出した際の挙動
	* @details		ID:0-29
	* 				リストが空である場合に、呼び出した際に、
	*				戻り値はダミーノードを指すイテレータの場合成功です。
	********************************************************/
	TEST(ListCBeginTest, WhenEmptyList)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData> list;

		//ダミーであるか
		EXPECT_DEATH((*list.CBegin()), "constIterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		リストに要素が一つある場合に、呼び出した際の挙動
	* @details		ID:0-30
	* 				リストに要素が一つある場合に、呼び出した際に、
	*				先頭要素を指すイテレータが返る場合成功です。
	********************************************************/
	TEST_F(ListCBeginTest_F, WhenOneElementList)
	{
		//要素が一つあるリストを作成
		InputOneData();

		//リストに要素が一つであるかをチェック
		EXPECT_EQ(1, list.Count());

		EXPECT_EQ("head", (*list.CBegin()).name);
	}

	/*********************************************************
	* @brief		リストに二つ以上の要素がある場合に、呼び出した際の挙動
	* @details		ID:0-31
	* 				リストに二つ以上の要素がある場合に、呼び出した際に、
	*				先頭要素を指すイテレータが返る場合成功です。
	********************************************************/
	TEST_F(ListCBeginTest_F, WhenManyElementsList)
	{
		//要素が二つ以上あるリストを作成
		InputThreeData();

		//リストに要素が二つ以上あるかをチェック
		EXPECT_LE(2, list.Count());

		EXPECT_EQ("head", (*list.CBegin()).name);
	}

	/*********************************************************
	* @brief		データの挿入を行った後に、呼び出した際の挙動
	* @details		ID:0-32
	* 				データの挿入を行った後に、呼び出した際に、
	*				先頭要素を指すイテレータが返る場合成功です。
	*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
	********************************************************/
	TEST_F(ListCBeginTest_F, AfterInsert)
	{
		InputThreeData();
		ScoreData newData(20, "newData");

		//先頭に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(headIter, newData));
		EXPECT_EQ("newData", (*list.CBegin()).name);

		//中央に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(middleIter, newData));
		EXPECT_EQ("newData", (*list.CBegin()).name);

		//末尾に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(endIter, newData));
		EXPECT_EQ("newData", (*list.CBegin()).name);
	}

	/*********************************************************
	* @brief		データの削除を行った後に、呼び出した際の挙動
	* @details		ID:0-33
	* 				データの削除を行った後に、呼び出した際に、
	*				先頭要素を指すイテレータが返る場合成功です。
	*				要素列の先頭、中央、末尾に削除を行った場合の各ケースについてチェックします。
	********************************************************/
	TEST_F(ListCBeginTest_F, AfterRemove)
	{
		//3回削除を行うため、データ4つを用意
		InputDatas(4);//list: head middle0 middle1 tail

		//末尾要素を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(tailIter));
		EXPECT_EQ("head", (*list.CBegin()).name);//list: head middle0 middle1

		//中央を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(middleIter));
		EXPECT_EQ("head", (*list.CBegin()).name);//list: head middle1

		//先頭を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(headIter));
		EXPECT_EQ("middle1", (*list.CBegin()).name);//list: middle1
	}

#pragma endregion

#pragma region ========== 末尾イテレータの取得 ==========

	using ListEndTest_F = ListFixture;

	/*********************************************************
	* @brief		リストが空である場合に、呼び出した際の挙動
	* @details		ID:0-35
	* 				リストが空である場合に、呼び出した際に、
	*				戻り値はダミーノードを指すイテレータの場合成功です。
	********************************************************/
	TEST(ListEndTest, WhenEmptyList)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData> list;

		//ダミーであるか
		EXPECT_DEATH((*list.End()), "iterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		リストに要素が一つある場合に、呼び出した際の挙動
	* @details		ID:0-36
	* 				リストに要素が一つある場合に、呼び出した際に、
	*				ダミーノードを指すイテレータが返る場合成功です。
	********************************************************/
	TEST_F(ListEndTest_F, WhenOneElementList)
	{
#ifdef _DEBUG
		//要素が一つあるリストを作成
		InputOneData();

		//リストに要素が一つであるかをチェック
		EXPECT_EQ(1, list.Count());

		EXPECT_DEATH((*list.End()), "iterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		リストに二つ以上の要素がある場合に、呼び出した際の挙動
	* @details		ID:0-37
	* 				リストに二つ以上の要素がある場合に、呼び出した際に、
	*				ダミーノードを指すイテレータが返る場合成功です。
	********************************************************/
	TEST_F(ListEndTest_F, WhenManyElementsList)
	{
#ifdef _DEBUG
		//要素が二つ以上あるリストを作成
		InputThreeData();

		//リストに要素が二つ以上あるかをチェック
		EXPECT_LE(2, list.Count());

		EXPECT_DEATH((*list.End()), "iterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		データの挿入を行った後に、呼び出した際の挙動
	* @details		ID:0-38
	* 				データの挿入を行った後に、呼び出した際に、
	*				ダミーノードを指すイテレータが返る場合成功です。
	*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
	********************************************************/
	TEST_F(ListEndTest_F, AfterInsert)
	{
#ifdef _DEBUG
		InputThreeData();
		ScoreData newData(20, "newData");

		//先頭に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(headIter, newData));
		EXPECT_DEATH((*list.End()), "iterator: is dummy");

		//中央に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(middleIter, newData));
		EXPECT_DEATH((*list.End()), "iterator: is dummy");

		//末尾に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(endIter, newData));
		EXPECT_DEATH((*list.End()), "iterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		データの削除を行った後に、呼び出した際の挙動
	* @details		ID:0-39
	* 				データの削除を行った後に、呼び出した際に、
	*				ダミーノードを指すイテレータが返る場合成功です。
	*				要素列の先頭、中央、末尾に削除を行った場合の各ケースについてチェックします。
	********************************************************/
	TEST_F(ListEndTest_F, AfterRemove)
	{
#ifdef _DEBUG
		//3回削除を行うため、データ4つを用意
		InputDatas(4);

		//末尾要素を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(tailIter));
		EXPECT_DEATH((*list.End()), "iterator: is dummy");

		//中央を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(middleIter));
		EXPECT_DEATH((*list.End()), "iterator: is dummy");

		//先頭を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(headIter));
		EXPECT_DEATH((*list.End()), "iterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

#pragma endregion

#pragma region ========== 末尾コンストイテレータの取得 ==========

	using ListCEndTest_F = ListFixture;

	/*********************************************************
	* @brief		リストが空である場合に、呼び出した際の挙動
	* @details		ID:0-41
	* 				リストが空である場合に、呼び出した際に、
	*				戻り値はダミーノードを指すイテレータの場合成功です。
	********************************************************/
	TEST(ListCEndTest, WhenEmptyList)
	{
#ifdef _DEBUG
		DoubleLinkedList<ScoreData> list;

		//ダミーであるか
		EXPECT_DEATH((*list.CEnd()), "constIterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		リストに要素が一つある場合に、呼び出した際の挙動
	* @details		ID:0-42
	* 				リストに要素が一つある場合に、呼び出した際に、
	*				ダミーノードを指すイテレータが返る場合成功です。
	********************************************************/
	TEST_F(ListCEndTest_F, WhenOneElementList)
	{
#ifdef _DEBUG
		//要素が一つあるリストを作成
		InputOneData();

		//リストに要素が一つであるかをチェック
		EXPECT_EQ(1, list.Count());

		EXPECT_DEATH((*list.CEnd()), "constIterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		リストに二つ以上の要素がある場合に、呼び出した際の挙動
	* @details		ID:0-43
	* 				リストに二つ以上の要素がある場合に、呼び出した際に、
	*				ダミーノードを指すイテレータが返る場合成功です。
	********************************************************/
	TEST_F(ListCEndTest_F, WhenManyElementsList)
	{
#ifdef _DEBUG
		//要素が二つ以上あるリストを作成
		InputThreeData();

		//リストに要素が二つ以上あるかをチェック
		EXPECT_LE(2, list.Count());

		EXPECT_DEATH((*list.CEnd()), "constIterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		データの挿入を行った後に、呼び出した際の挙動
	* @details		ID:0-44
	* 				データの挿入を行った後に、呼び出した際に、
	*				ダミーノードを指すイテレータが返る場合成功です。
	*				要素列の先頭、中央、末尾に挿入を行った場合の各ケースについてチェックします。
	********************************************************/
	TEST_F(ListCEndTest_F, AfterInsert)
	{
#ifdef _DEBUG
		InputThreeData();
		ScoreData newData(20, "newData");

		//先頭に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(headIter, newData));
		EXPECT_DEATH((*list.CEnd()), "constIterator: is dummy");

		//中央に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(middleIter, newData));
		EXPECT_DEATH((*list.CEnd()), "constIterator: is dummy");

		//末尾に挿入
		UpdateIterator();
		EXPECT_TRUE(list.Insert(endIter, newData));
		EXPECT_DEATH((*list.CEnd()), "constIterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

	/*********************************************************
	* @brief		データの削除を行った後に、呼び出した際の挙動
	* @details		ID:0-45
	* 				データの削除を行った後に、呼び出した際に、
	*				ダミーノードを指すイテレータが返る場合成功です。
	*				要素列の先頭、中央、末尾に削除を行った場合の各ケースについてチェックします。
	********************************************************/
	TEST_F(ListCEndTest_F, AfterRemove)
	{
#ifdef _DEBUG
		//3回削除を行うため、データ4つを用意
		InputDatas(4);//list: head middle0 middle1 tail

		//末尾要素を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(tailIter));
		EXPECT_DEATH((*list.CEnd()), "constIterator: is dummy");

		//中央を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(middleIter));
		EXPECT_DEATH((*list.CEnd()), "constIterator: is dummy");

		//先頭を削除
		UpdateIterator();
		EXPECT_TRUE(list.Remove(headIter));
		EXPECT_DEATH((*list.CEnd()), "constIterator: is dummy");
#else
		SUCCEED();
#endif // _DEBUG
	}

#pragma endregion

#endif
}