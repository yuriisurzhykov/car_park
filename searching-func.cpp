#include "header.h"

AUTOPARK_Tree* SearchName(AUTOPARK_Tree* Branch, string SearchData) {
	if (Branch == NULL || Branch->Name == SearchData)
		return Branch;
	else if (SearchData > Branch->Name)
		return SearchName(Branch->Right, SearchData);
	else return SearchName(Branch->Left, SearchData);
}

void SearchForLetter() {
	system("cls");
	DataAvailibility();
	int *AmountFindsElem = new int(0);
	cout << "������� ����� ��� ������ ��������, ��� ������� 0 , ����� ��������� �����: ";
	string SearchChar;
	cin.clear();
	getline(cin, SearchChar);
	if (SearchChar[0] == '0') {
		AllOportunuties();
	}
	while (SearchChar.size() > 1 || !CheckStringToNumb(SearchChar)) {
		if (SearchChar[0] == '0') {
			AllOportunuties();
		}
		else if (SearchChar.size() > 1) {
			cout << "������� ������ ���� ������, ��� ������� 0 , ����� ��������� �����" << endl;
			cin.clear();
			getline(cin, SearchChar);
		}
		else if (!CheckStringToNumb(SearchChar)) {
			cout << "��� �� �������� ����!" << endl << "������� ������ �����, ��� ������� 0 , ����� ��������� �����: ";
			cin.clear();
			getline(cin, SearchChar);
		}
	}
	system("cls");
	cout << endl << "\t\t\t\t\t����� ��������� �� �������� �����" << endl << endl;
	HeadTable();
	if (!SearchDriver(Root, SearchChar[0], AmountFindsElem)) {
		cout << "\t��������� �� ����� " << SearchChar[0] << " ���!" << endl;
	}
	cout << "\t��������� �����? ������� '�' ��� '�'" << endl;
	cin.clear();
	char Answer = GetKey();
	if (Answer == '�') {
		delete AmountFindsElem;
		MainMenu();
	}
	else {
		delete AmountFindsElem;
		SearchForLetter();
	}
}

int SearchDriver(AUTOPARK_Tree* Branch, char SearchChar, int* Counter) {
	if (Branch == NULL) return 0;
	else {
		if (Branch->Name[0] == SearchChar) {
			(*Counter)++;
			cout << "\t" << "|" << setw(4) << right << ++Position;
			cout << "|";
			cout << setw(33) << left << Branch->Name << " | ";
			cout << setw(12) << right << Branch->AmountValutation;
			cout << "|";
			cout << setw(18) << right << Branch->NumberBus;
			cout << "|";
			cout << setw(11) << right << Branch->NumberWay;
			cout << "|";
			if (Branch->Presense == '�') cout << "    ��     ";
			else cout << "    ���    ";
			cout << "|" << endl;
			cout << "\t" << "+----+------------------------------------------------+------------------------------------------+" << endl;
		}
		int ForReturn = (SearchDriver(Branch->Left, SearchChar, Counter) + *Counter) + (SearchDriver(Branch->Right, SearchChar, Counter) + *Counter);
		return ForReturn;
	}
}

void ShowMaxValutation() {

	AUTOPARK_Tree* Branch;

	system("cls");
	DataAvailibility();
	cout << endl << "\t\t\t\t������ � ��������(-��) � ���������� ������ ���������" << endl << endl;
	Re_SortingValut(Root);
	HeadTable();
	Branch = RootMaxValutation;
	while (Branch->Right)
		Branch = Branch->Right;
	SearchMaxValutation(RootMaxValutation, Branch->AmountValutation);
	DemageTree(RootMaxValutation);
	RootMaxValutation = NULL;
	system("pause"); 
	AllOportunuties();
}

int Re_SortingValut(AUTOPARK_Tree* Data) {
	if (Data == NULL) return 0;
	else {
		int ForReturn = Re_SortingValut(Data->Left) + Re_SortingValut(Data->Right) + Data->AmountValutation;
		SortingTreeFotValut(&RootMaxValutation, NULL, Data);
		return  ForReturn;
	}
}

void SortingTreeFotValut(AUTOPARK_Tree** Branch, AUTOPARK_Tree* ParentFunc, AUTOPARK_Tree* Data) {
	if ((*Branch) == NULL) {
		(*Branch) = new AUTOPARK_Tree;
		*(*Branch) = *Data;
		(*Branch)->Left = (*Branch)->Right = NULL;
		(*Branch)->Parent = ParentFunc;
		return;
	}
	else {
		if (Data->AmountValutation > (*Branch)->AmountValutation)
			SortingTreeFotValut(&(*Branch)->Right, (*Branch), Data);
		else SortingTreeFotValut(&(*Branch)->Left, (*Branch), Data);
	}
}


int SearchMaxValutation(AUTOPARK_Tree* Branch, int MaxAmountValut) {
	if (Branch == NULL)
		return MaxAmountValut;
	SearchMaxValutation(Branch->Right, MaxAmountValut);
	if (Branch->AmountValutation != MaxAmountValut)
		return MaxAmountValut;
	else {
		cout << "\t" << "|" << setw(4) << right << ++Position;
		cout << "|";
		cout << setw(33) << left << Branch->Name << " | ";
		cout << setw(12) << right << Branch->AmountValutation;
		cout << "|";
		cout << setw(18) << right << Branch->NumberBus;
		cout << "|";
		cout << setw(11) << right << Branch->NumberWay;
		cout << "|";
		if (Branch->Presense == '�') cout << "    ��     ";
		else cout << "    ���    ";
		cout << "|" << endl;
		cout << "\t" << "+----+------------------------------------------------+------------------------------------------+" << endl;
	}
	SearchMaxValutation(Branch->Left, MaxAmountValut);
}


void ShowListOfBus() {
	DataAvailibility();
	Position = 0;
	int counter = 0;
	system("cls");
	cout << "�������� ��������." << endl;
	cout << "1. �������� ������ ��������� ���������." << endl;
	cout << "2. �������� ������ ���������� ���������." << endl;
	cout << "0. ��������� �����." << endl;
	cin.clear();
	char Answer = _getch();
	switch (Answer) {
	case '1':
		system("cls");
		cout << endl << "\t\t\t������ ��������� ���������" << endl << endl;
		cout << "\t" << "+----+------------------------------------------+ " << endl;
		cout << "\t" << "|  � |  ����� ��������  |    �����  | ������� � | " << endl;
		cout << "\t" << "| �/�|                  |  �������� |   �����   | " << endl;
		cout << "\t" << "+----+------------------------------------------+ " << endl;
		counter = ShowBus(Root, '�');
		if (counter == 0) {
			cout << endl << "\t" << "��� �������� ���������� � �����" << endl;
		}
		system("pause");
		ShowListOfBus();
		break;
	case '2':
		system("cls");
		cout << endl << "\t\t\t������ ���������� ���������" << endl << endl;
		cout << "\t" << "+----+------------------------------------------+" << endl;
		cout << "\t" << "|  � |  ����� ��������  |    �����  | ������� � |" << endl;
		cout << "\t" << "| �/�|                  |  �������� |   �����   |" << endl;
		cout << "\t" << "+----+------------------------------------------+" << endl;
		counter = ShowBus(Root, '�');
		if (counter == 0) {
			cout << endl << "\t" << "� ����� ��� ���������" << endl;
		}
		system("pause");
		ShowListOfBus();
		break;
	case '0':
		AllOportunuties();
		break;
	}
	ShowListOfBus();
}

int ShowBus(AUTOPARK_Tree* Branch, char CharPresence) {
	if (Branch == NULL) return 0;
	else {
		if (Branch->Presense == CharPresence) {
			cout << "\t" << "|" << setw(4) << right << ++Position;
			cout << "|";
			cout << setw(18) << right << Branch->NumberBus;
			cout << "|";
			cout << setw(11) << right << Branch->NumberWay;
			cout << "|";
			if (CharPresence == '�')
				cout << "    ���    ";
			else cout << "     ��    ";
			cout << "|" << endl;
			cout << "\t" << "+----+------------------------------------------+" << endl;
		}
		int ForReturn = (ShowBus(Branch->Left, CharPresence) + Position) + (ShowBus(Branch->Right, CharPresence) + Position);
		return ForReturn;
	}
}