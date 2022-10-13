/*********************************************************
* @brief	�o�������X�g�œǂݎ�����f�[�^��W���o�͂ɕ\��
* @date		2022/10/11
********************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "ScoreData.h"
#include "DoubleLinkedList.h"

int main(void)
{
	//�f�[�^���i�[���邽�߂̃��X�g��p��
	DoubleLinkedList<ScoreData> list;	

	//�t�@�C����ǂݍ��݁A�f�[�^���i�[ 
	{
		FILE* fp; 
		char fileName[] = "Scores.txt";

		//�t�@�C�����J���A���s����ƏI��
		{
			fp = fopen(fileName, "r");
			if (fp == NULL) {
				std::cout << fileName << "file open error!" << std::endl;
				return -1;
			}
			else {
				std::cout << fileName << "file opened!" << std::endl;
			}
		}

		
		//���[�v��1�s���ǂݎ�������e���f�[�^�Ɋi�[�A
		//���e�����Ȃ��ꍇ���[�v�I��
		{
			int score;					//�X�R�A�f�[�^���ꎞ�i�[�p
			char name[WORD_SIZE];		//���O�f�[�^���ꎞ�i�[�p

			while (fscanf(fp, "%d\t%s", &score, name) != EOF) {
#if 1
				//1�s���ǂݎ�������e���m�F
				std::cout << name << ":" << score << std::endl;//test
#endif

				//�X�R�A�f�[�^���쐬���āA�f�[�^���i�[
				ScoreData data(score, name);
				auto iter = list.End();
				list.Insert(iter, data);
			}
		}
		

		//�t�@�C�������
		fclose(fp);
	}

	//�C�e���[�g���āu�i�[�������Łv�W���o�͂ɕ\��
	{
		auto it = list.Begin();
		auto end = list.End();

		for (; it != end; ++it)
		{
			std::cout 
				<< (*it).name
				<< ((*it).name.size() < 8 ? "\t\t:" : "\t:")//���񂷂邽�߂ł�
				<< (*it).score
				<< std::endl;
		}
	}

	//�G���^�[�L�[�������ďI��
	(void)getchar();
	return 0;
}
