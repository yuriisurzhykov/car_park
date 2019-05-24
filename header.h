#pragma once
#ifndef _HEADER_H
#define _HEADER_H
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <string>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;


//��������� ������ "��������".
//���� ���������:
//  1)��������� �� ������� �������, �� ������ � �� ��������
//  2)������ �����
//  3)���������� ���������� ���������
//  4)������ ����� ���������
//  5)�������� ���������� ����� ��������
//  6)���������� ���������� ����������� � �����
struct AUTOPARK_Tree {
	string Name;
	int AmountValutation;
	string NumberBus;
	int NumberWay;
	char Presense;
	AUTOPARK_Tree* Parent = NULL;
	AUTOPARK_Tree* Left = NULL;
	AUTOPARK_Tree* Right = NULL;
};

__declspec(selectany) AUTOPARK_Tree* Root = NULL;
__declspec(selectany) AUTOPARK_Tree* NewRoot = NULL;
__declspec(selectany) AUTOPARK_Tree* RootMaxValutation = NULL;
__declspec(selectany) int Position = 0;
__declspec(selectany) bool Data_is_Saved;

//������� "����"
void MainMenu();
void OutputMenu();
void MenuOutputTree();
void ShowDataMenu();
void AllOportunuties();
void MenuAfterOutput();

//������ ����� ������ ������
void InputData();
void ShowData();
void HeadTable();
AUTOPARK_Tree* PushData(AUTOPARK_Tree** Branch, AUTOPARK_Tree* ParentFunc, AUTOPARK_Tree Data);
void PrintTree(AUTOPARK_Tree* Branch);
void PrintTreeAsTree(AUTOPARK_Tree* Branch, int Level);

//������������ �������� ���������
void ShowListOfBus();
int ShowBus(AUTOPARK_Tree* Branch, char CharPresence);
void ResortingMain();
int Re_Sorting(AUTOPARK_Tree* Data);
int Re_SortingValut(AUTOPARK_Tree* Data);
void Re_SortingTree(AUTOPARK_Tree** Branch, AUTOPARK_Tree* ParentFunc, AUTOPARK_Tree* Data);

//�������������� ������ + ����� ������� � ������
void CorrectData();
AUTOPARK_Tree* SearchName(AUTOPARK_Tree* Branch, string SearchData);
void SearchForLetter();
int SearchDriver(AUTOPARK_Tree* Branch, char SearchChar, int* Counter);
void ShowMaxValutation();
int SearchMaxValutation(AUTOPARK_Tree* Branch, int ParentValutation);
void SortingTreeFotValut(AUTOPARK_Tree** Branch, AUTOPARK_Tree* ParentFunc, AUTOPARK_Tree* Data);

//�������� ������
void DeleteDataMain();
int DeleteData(string Search);
void DemageTree(AUTOPARK_Tree* Branch);
void DeleteAllData();

//������ � �������
void StartProgramm();
int ReadFromFile(string FileName);
int WriteInFile(AUTOPARK_Tree* Data, string FileName);
void WriteBuferData(AUTOPARK_Tree* Data, string FileName);
void Login();

//�������������� �������
void Greeting();
void SavingData();
void DataAvailibility();
bool CheckExistence(AUTOPARK_Tree* Branch, AUTOPARK_Tree CheckData, int CodeOperation);
int CheckForNotLetter(string str);
bool CorrectPathName(string Path);
int StringCompare(string str1, string str2);
int StringToInt(string str);
char GetKey();
bool IsLetter(const char sym);
int CheckStringToNumb(string str);
int CheckInt(string str);
void StringToCharArray(string NameFileStr, char* NameFileChar);
bool IsDigit(const char sym);
void CheckBufer();

#endif