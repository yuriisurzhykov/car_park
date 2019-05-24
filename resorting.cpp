#include "header.h"

/*
	������� ���������� ������ �� ������� ���������.
	������� ��������� �����������.
*/
void ResortingMain() {
	DataAvailibility();
	int AmountElem = Re_Sorting(Root);
	if (AmountElem != 0) {
		cout << endl << "�������������� ��������� �������";
		Sleep(700);
		system("cls");
		cout << endl << "\t\t\t\t��������������� ������ �� ������� ���������" << endl << endl;
		HeadTable();
		PrintTree(NewRoot);
		DemageTree(NewRoot);
		NewRoot = NULL;
		cout << endl << "\t";
		system("pause");
		AllOportunuties();
	}
	else {
		cout << endl << "��������� ������ ��� �������������� ������!" << endl;
		NewRoot = NULL;
		Sleep(900);
		return;
	}
}

/*
	������� �������� �� ������ � �������� ������� ������������ ������ ������.
	������� ���������: 
		1) AUTOPARK_Tree* Data - ��������� �� ������ ������.
	����������:
		1) 0 - ���� ��������� �� NULL
		2) Data->AmountValutation - ���� ������ ������������
*/
int Re_Sorting(AUTOPARK_Tree* Data) {
	if (Data == NULL) return 0;
	else {
		Re_SortingTree(&NewRoot, NULL, Data);
		return Re_Sorting(Data->Left) + Re_Sorting(Data->Right) + Data->AmountValutation;
	}
}

/*
	������� ������������ ������ ������, �� ������� ��������
*/
void Re_SortingTree(AUTOPARK_Tree** Branch, AUTOPARK_Tree* ParentFunc, AUTOPARK_Tree* Data) {
	if ((*Branch) == NULL) {
		(*Branch) = new AUTOPARK_Tree;
		*(*Branch) = *Data;
		(*Branch)->Left = (*Branch)->Right = NULL;
		(*Branch)->Parent = ParentFunc;
	}
	else {
		if (Data->NumberBus > (*Branch)->NumberBus)
			Re_SortingTree(&(*Branch)->Right, (*Branch), Data);
		else if (Data->NumberBus < (*Branch)->NumberBus)
			Re_SortingTree(&(*Branch)->Left, (*Branch), Data);
		else {
			if (Data->Name >= (*Branch)->Name)
				Re_SortingTree(&(*Branch)->Right, (*Branch), Data);
			else 
				Re_SortingTree(&(*Branch)->Left, (*Branch), Data);
		}
	}
}