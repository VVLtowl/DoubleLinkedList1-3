/*********************************************************
* @brief		イテレータ単体テスト(手動テスト)
* @date			2022/10/14
********************************************************/
#include "gtest/gtest.h"
#include "../DoubleLinkedList/DoubleLinkedList.h"
#include "ManualTest_ConstIterator.h"

namespace ex02_ConstIterator
{
	/*********************************************************
	* @brief		ConstIteratorから取得した要素に対して、値の代入が行えないかをチェック
	* @details		ID:1-2
	*				ConstIteratorから取得した要素に対して、
	*				値の代入が行えないかをチェックします。
	*				コンパイルエラーになることをチェックします。(手動テスト)
	********************************************************/
	TEST(IteratorGetDataTest, WhenEmptyList_GetFromBegin)
	{
#ifdef MANUAL_TEST_ITERATOR_CANT_ASSIGN_CONSTITERATOR
		DoubleLinkedList<int> list;

		//Iteratorから取得した要素に値を代入
		auto iter = list.Begin();
		(*iter) = 10;

		//ConstIteratorから取得した要素に値を代入
		auto constIter = list.CBegin();
		(*constIter) = 10;
#else
		SUCCEED();
#endif // GT_MANUAL_TEST_ITERATOR
	}

	/*********************************************************
	* @brief		ConstIteratorから、Iteratorのコピーが作成されないかをチェック
	* @details		ID:1-17
	* 				ConstIteratorから、Iteratorのコピーが作成されないかをチェックします。
	*				コンパイルエラーになることを確認します。(手動テスト)
	********************************************************/
	TEST(IteratorCopyTest, ConstIteratorCopyIterator)
	{
#ifdef MANUAL_TEST_ITERATOR_CONSTITERATOR_CANT_COPY_ITERATOR
		DoubleLinkedList<int>::Iterator iter;
		DoubleLinkedList<int>::ConstIterator constIter;
		DoubleLinkedList<int>::ConstIterator constIter1(iter);//Iteratorから、ConstIteratorのコピーを作成
		DoubleLinkedList<int>::Iterator iter1(constIter);//ConstIteratorから、Iteratorのコピーを作成
#else
		SUCCEED();
#endif //
	}

	/*********************************************************
	* @brief		IteratorにConstIteratorを代入できない事をチェック
	* @details		ID:1-19
	* 				IteratorにConstIteratorを代入できない事をチェックします。
	*				コンパイルエラーになることを確認します。(手動テスト)
	********************************************************/
	TEST(IteratorAssignTest, AssginConstIteratorToIterator)
	{
#ifdef MANUAL_TEST_ITERATOR_CANT_ASSIGN_CONSTITERATOR_TO_ITERATOR
		DoubleLinkedList<int>::ConstIterator constIter;
		DoubleLinkedList<int>::Iterator iter;
		constIter = iter;//ConstIteratorにIteratorを代入
		iter = constIter;//IteratorにConstIteratorを代入
#else
		SUCCEED();
#endif
	}

}