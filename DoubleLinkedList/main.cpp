/*********************************************************
* @brief	双方向リストで読み取ったデータを標準出力に表示
* @date		2022/10/11
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "ScoreData.h"
#include "DoubleLinkedList.h"

#include <windows.h>

void myTest()
{
	//データを格納するためのリストを用意
	DoubleLinkedList<ScoreData>* list=new DoubleLinkedList<ScoreData>;

	//ファイルを読み込み、データを格納 
	{
		FILE* fp;
		char fileName[] = "Scores.txt";

		//ファイルを開く、失敗すると終了
		{
			fp = fopen(fileName, "r");
			if (fp == NULL) {
				std::cout << fileName << "file open error!" << std::endl;
				return;
			}
			else {
				std::cout << fileName << "file opened!" << std::endl;
			}
		}


		//ループで1行ずつ読み取った内容をデータに格納、
		//内容が取らない場合ループ終了
		{
			int score;					//スコアデータを一時格納用
			char name[50];		//名前データを一時格納用

			while (fscanf(fp, "%d\t%s", &score, name) != EOF) {
#if 0
				//1行ずつ読み取った内容を確認
				std::cout << name << ":" << score << std::endl;//test
#endif

				//スコアデータを作成して、データを格納
				ScoreData data(score, name);
				auto iter = list->End();
				list->Insert(iter, data);
			}
		}

		//ファイルを閉じる
		fclose(fp);
	}

	//イテレートして「格納した順で」標準出力に表示
	{
		auto it = list->Begin();
		auto end = list->End();
		for (; it != end; ++it)
		{
			std::cout
				<< (*it).name
				<< ((*it).name.size() < 8 ? "\t\t:" : "\t:")//整列するためです
				<< (*it).score
				<< std::endl;
		}
	}

	for (int i = 0; i < 20; i++)
	{
		auto it= list->Begin();
		list->Remove(it);
	}
	delete list;
}

/*********************************************************
* @brief		main関数
* @return		成功の場合0を返す、失敗の場合ほかの値を返す
********************************************************/
int main(void)
{
	while (1)
	{
		myTest();
		Sleep(3000);
	}

	//エンターキーを押して終了
	(void)getchar();
	return 0;
}

