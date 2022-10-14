/*********************************************************
* @brief		双方向リスト単体テスト(手動テスト)
* @date			2022/10/14
********************************************************/
#include "gtest/gtest.h"
#include "../DoubleLinkedList/DoubleLinkedList.h"
#include "ManualTest_DoubleLinkedList.h"

namespace ex01_DoubleLinkedList
{
	/*********************************************************
	* @brief		constのメソッドであるか
	* @details		ID:0-8
	*				constのリストから呼び出して、
	* 				コンパイルエラーとならないかをチェックします。（手動テスト）
	********************************************************/
	TEST(ListCountTest, IsConst)
	{
#ifdef MANUAL_TEST_LIST_COUNT_IS_CONST
		const DoubleLinkedList<int> list;
		list.Count();
#else
		SUCCEED();
#endif // 
	}

	/*********************************************************
	* @brief		非constのメソッドであるか
	* @details		ID:0-15
	*				constのリストから呼び出して、
	* 				コンパイルエラーとなるかをチェックします。（手動テスト）
	********************************************************/
	TEST(ListInsertTest, NotConst)
	{
#ifdef  MANUAL_TEST_LIST_INSERT_NOT_CONST
		const DoubleLinkedList<int> list;
		auto iter = list.CBegin();
		list.Insert(iter, 0);
#else
		SUCCEED();
#endif //  
	}

	/*********************************************************
	* @brief		非constのメソッドであるか
	* @details		ID:0-22
	*				constのリストから呼び出して、
	* 				コンパイルエラーとなるかをチェックします。（手動テスト）
	********************************************************/
	TEST(ListRemoveTest, NotConst)
	{
#ifdef  MANUAL_TEST_LIST_REMOVE_NOT_CONST
		const DoubleLinkedList<int> list;
		list.Remove(DoubleLinkedList<int>::Iterator());
#else
		SUCCEED();
#endif //  
	}

	/*********************************************************
	* @brief		constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
	* @details		ID:0-28
	* 				constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
	*				コンパイラエラーになるかをチェックします（手動テスト）
	********************************************************/
	TEST(ListBeginTest, NotConst)
	{
#ifdef MANUAL_TEST_LIST_BEGIN_NOT_CONST
		const DoubleLinkedList<int> constList;
		constList.Begin();
#else
		SUCCEED();
#endif
	}

	/*********************************************************
	* @brief		constのリストから呼び出して、コンパイルエラーとならないかをチェック
	* @details		ID:0-34
	* 				constのリストから呼び出して、コンパイルエラーとならないかをチェック
	*				手動テスト
	********************************************************/
	TEST(ListCBeginTest, IsConst)
	{
#ifdef MANUAL_TEST_LIST_CBEGIN_IS_CONST
		const DoubleLinkedList<int> constList;
		constList.CBegin();
#else
		SUCCEED();
#endif
	}

	/*********************************************************
	* @brief		constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
	* @details		ID:0-40
	* 				constのリストから、ConstIteratorでないIteratorの取得が行えないかをチェック
	*				コンパイラエラーになるかをチェックします（手動テスト）手動テスト
	********************************************************/
	TEST(ListEndTest, NotConst)
	{
#ifdef MANUAL_TEST_LIST_END_NOT_CONST
		const DoubleLinkedList<int> constList;
		constList.End();
#else
		SUCCEED();
#endif
	}

	/*********************************************************
	* @brief		constのリストから呼び出して、コンパイルエラーとならないかをチェック
	* @details		ID:0-46
	* 				constのリストから呼び出して、コンパイルエラーとならないかをチェック
	*				手動テスト
	********************************************************/
	TEST(ListCEndTest, IsConst)
	{
#ifdef MANUAL_TEST_LIST_CEND_IS_CONST
		const DoubleLinkedList<int> constList;
		constList.CEnd();
#else
		SUCCEED();
#endif
	}
}


