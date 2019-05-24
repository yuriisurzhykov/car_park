#include "header.h"

void DeleteDataMain() {
	system("cls");
	cout << endl << "\t\t\t\t\t\t�������� ������" << endl << endl;
	HeadTable();
	DataAvailibility();
	PrintTree(Root);
	cout << endl << "������� ��� ��� �������� ��� ������� 0, ����� ��������� �����: ";
	string SearchStr;
	cin.clear();
	getline(cin, SearchStr);
	if (SearchStr[0] == '0') {
		return;
	}
	while (SearchStr[0] == '\0') {
		cout << endl << "��� ������ ��� ����������! ������� ������!" << endl;
		cout << "������� ��� ��� ��������: ";
		cin.clear();
		getline(cin, SearchStr);
	}
	while (!SearchName(Root, SearchStr)) {
		cout << "������ " << SearchStr << " ����������� � ���� ������!" << endl;
		cout << "��������� �����? ������� '�' ��� '�'" << endl;
		char Answer = GetKey();
		if (Answer == '�')
			MainMenu();
		else {
			cout << endl << "������� ��� ��� ��������: ";
			cin.clear();
			getline(cin, SearchStr);
		}
	}
	cout << "�� ����� ������ ������� ������ " << SearchStr << "? ������� '�' ��� '�'" << endl;
	cin.clear();
	char Answer = GetKey();
	if (Answer == '�') {
		cout << endl << "������ ��������!" << endl;
		Sleep(900);
		MainMenu();
	}
	else {
		if (DeleteData(SearchStr)) {
			Data_is_Saved = false;
			if (Root == NULL) {
				cout << endl << "������ ������� �������!" << endl;
				cout << endl << endl << "\t� ���� ��� ������! ��������� ������� �����!" << endl << endl;
				system("cls");
				MenuAfterOutput();
			}
			else {
				system("cls");
				cout << endl << "\t\t\t\t\t\t�������� ������" << endl << endl;
				HeadTable();
				PrintTree(Root);
				cout << endl << "������ ������� �������!" << endl;
				cout << "������ ��� ������� �������? ������� � ��� �" << endl;
				cin.clear();
				char Answer = GetKey();
				if (Answer == '�')
					MenuAfterOutput();
				else DeleteDataMain();
			}
		}
	}
}

int DeleteData(string Search) {
	AUTOPARK_Tree** NeededElem = new AUTOPARK_Tree*;
	*NeededElem = SearchName(Root, Search);
	
	//���� ��������� �� �������� ����� ������ ����� ����, ������ ������� ����� �� �������,
	//������� ���������� 0
	if (*NeededElem == NULL)
		return 0;
	//� ��������� �������� ��� �������� - ����� ������� ������.
	if ((*NeededElem)->Right == NULL && (*NeededElem)->Left == NULL) {
		if ((*NeededElem) == Root) {
			Root = NULL;
		}
		else if ((*NeededElem)->Parent->Right == (*NeededElem)) {//�������� ����� �������� - ������ ��� �����, �������� �������� �������
			(*NeededElem)->Parent->Right = NULL; //������� ��������, ��� ������ � ���� ��� �������.
		}
		else (*NeededElem)->Parent->Left = NULL; //������� ��������, ��� ������ � ���� ��� �������.
	}

	//� ��������� �������� ���� ������ �������
	else if ((*NeededElem)->Left == NULL) {
		if ((*NeededElem) == Root) {
			Root = Root->Right;
		}
		else {
			if ((*NeededElem)->Parent->Right == (*NeededElem)) { //�������� ����� �������� - ������ ��� �����, �������� �������� �������
				(*NeededElem)->Right->Parent = (*NeededElem)->Parent; //������� ������� ��������� ��������, ��� ������ ��� �������� - ��� �������� ��������� ��������.
				(*NeededElem)->Parent->Right = (*NeededElem)->Right; //������� ��������, ��� ������ ��� �������, ��� ������� ������� ��������
			}
			else {
				(*NeededElem)->Right->Parent = (*NeededElem)->Parent;
				(*NeededElem)->Parent->Left = (*NeededElem)->Right;
			}
		}
	}

	//� ��������� �������� ���� ����� �������
	else if ((*NeededElem)->Right == NULL) {
		if ((*NeededElem) == Root) {
			Root = Root->Left;
		}
		else {
			if ((*NeededElem)->Parent->Right == (*NeededElem)) {  //�������� ����� �������� - ������ ��� �����, �������� �������� �������
				(*NeededElem)->Parent->Right = (*NeededElem)->Left; //������� ��������, ��� ������ ��� �������, ��� ������� ������� ��������
				(*NeededElem)->Left->Parent = (*NeededElem)->Parent; //������� ������� ��������� ��������, ��� ������ ��� �������� - ��� �������� ��������� ��������.
			}
			else {
				(*NeededElem)->Parent->Left = (*NeededElem)->Left;  //������� ��������, ��� ������ ��� �������, ��� ������� ������� ��������
				(*NeededElem)->Left->Parent = (*NeededElem)->Parent;  //������� ������� ��������� ��������, ��� ������ ��� �������� - ��� �������� ��������� ��������
			}
		}
	}

	//����� ������� ������. � ��������� �������� 2 �������.
	else {
		AUTOPARK_Tree* MinRightElem = (*NeededElem)->Right; //��������� ��������� �� ����������� ������� ������� ���������
		while (MinRightElem->Left) {
			MinRightElem = MinRightElem->Left; //���� ���� ����� ����������� �������
		}
		if (!MinRightElem->Right) { //���� � ���.�������� ��� ������� �������
			if ((*NeededElem) == Root) {  // ���� ��������� ������� - ������ ������
				if (MinRightElem == (*NeededElem)->Right) { // ���� ����������� ������� ������� ���������, ��� ������ ������� ���������� ��������
					Root->Left->Parent = MinRightElem;  //������� ������� ���������� ��������, ��� ��� �������� - ��� ������ ��� ��������� ���.�������
					MinRightElem->Left = Root->Left; //������ ���.��-�� ����� ������. �������, ��� ����� ������� ���.��-��, ��� ����� ������� ���������� ��������
					MinRightElem->Right = NULL;  //�������, ��� � ������ ����� ��� ������ �����, ��� ��� ��� ����� ������ ��� ������������ ��������
					MinRightElem->Parent = NULL; //�������, ��� �������� � ���� ���
					Root = MinRightElem; //� ����������� ��������� �� ������ ����� ������ ��������
				}
				else { //���� ���.������� �� �������� ������ �������� ���������� ��������
					Root->Left->Parent = MinRightElem; //������� ������ ������� ���������� �������� ��� ��� �������� - ��� ���.�������, ������� ��������� 
					Root->Right->Parent = MinRightElem;//������� ������� ������� ���������� �������� ��� ��� �������� - ��� ���.�������, ������� ��������� 
					//������� �������� ���.��������, ��� ������ � ���� ��� �������
					MinRightElem->Parent->Left = NULL; 
					//�������� ���.������� ������ ��� ����� �����
					MinRightElem->Left = Root->Left; 
					MinRightElem->Right = Root->Right;
					//������� ���.��������, ��� � ���� ��� ���������
					MinRightElem->Parent = NULL; 
					//����������� ��������� �� ������ ������ ����� �����
					Root = MinRightElem; 
				}
			}
			else { //���� ��������� ������� �� ������, � ���.�������� ������� ��������� ��� ������� �������
				if (MinRightElem == (*NeededElem)->Right) {
					//������� ������� ���������� ��������, ��� ��� �������� - ��� ������ ��� ��������� ���.�������
					(*NeededElem)->Left->Parent = MinRightElem; 
					//�������, ��� ����� ������� ���.��-��, ��� ����� ������� ���������� ��������
					MinRightElem->Left = (*NeededElem)->Left; 
					//�������, ��� ������ �������� � ���.�������� ������ ���
					MinRightElem->Right = NULL; 
					MinRightElem->Parent = (*NeededElem)->Parent;
					
					if ((*NeededElem)->Parent->Right == (*NeededElem)) {
						(*NeededElem)->Parent->Right = MinRightElem;
					}
					else {
						(*NeededElem)->Parent->Left = MinRightElem;
					}
				}
				else {
					MinRightElem->Parent->Left = NULL; //������� �������� ������������ ��������, ��� � ���� ������ ��� �������
					//������� ������ ������� ���������� �������� ����� ������ ��������
					(*NeededElem)->Left->Parent = MinRightElem; 
					//������� ������� ������� ���������� �������� ����� ������ ��������
					(*NeededElem)->Right->Parent = MinRightElem; 
					//����������� ���.�������� ������ ��� ����� ��������
					MinRightElem->Left = (*NeededElem)->Left; 
					MinRightElem->Right = (*NeededElem)->Right; 
					//������ ���.�������� ����� ��� ������ ��������
					MinRightElem->Parent = (*NeededElem)->Parent; 

					if ((*NeededElem)->Parent->Right == (*NeededElem)) {
						//���� ��������� ������� - ������ �������, �� ������� ��������, ��� ��� ������ �������, ��� ������ ���.�������
						(*NeededElem)->Parent->Right = MinRightElem;  
					}
					else {
						//���� ��������� ������� - ����� �������, �� ������� ��������, ��� ��� �����  �������, ��� ������ ���.�������
						(*NeededElem)->Parent->Left = MinRightElem; 
					}
				}
			}
		}
		else {  //���� � ��� �������� ���� ������ �������
			if ((*NeededElem) == Root) { // ���� ��������� ������� - ��� ������ ����� ������
				if (MinRightElem == (*NeededElem)->Right) { // ���� ���.������� ������� ���������, ��� ������ �������, ���������� ��������.
					//�������� ���.�������� ��� ������ ����� ��������
					MinRightElem->Left = Root->Left; 
					 //�������, ���.�������� ��� � ���� ��� ��������
					MinRightElem->Parent = NULL;
					 //��������� ����� ������� � ����� ������
					Root->Left->Parent = MinRightElem;
					//����������� ��������� �� ������ ������ ����� �����
					Root = MinRightElem; 
				}
				else { //���� ���.������� ������� ���������, �� �������� ������ ��������, ���������� ��������.
					//��������� ������� ������� ���.�������� � ��������� ����� ���.��������
					MinRightElem->Right->Parent = MinRightElem->Parent; 
					//��������� �������� ���.�������� � ������ �������� ����� ���.��������
					MinRightElem->Parent->Left = MinRightElem->Right; 
					//�������� ���.�������� ������ ��� ����� ��������
					MinRightElem->Left = Root->Left;
					MinRightElem->Right = Root->Right;
					//�������, ��� �������� � ���� ���
					MinRightElem->Parent = NULL;
					//��������� �������� ����� ������ � ����� ���������
					Root->Left->Parent = MinRightElem;
					Root->Right->Parent = MinRightElem;
					//����������� ��������� �� ������ ������ ����� �����
					Root = MinRightElem;
				}
			}
			else {
				//�� �������� � ���������� ������� ������ ����� ��� ���� �����
				if (MinRightElem == (*NeededElem)->Right) {
					(*NeededElem)->Left->Parent = MinRightElem;
					MinRightElem->Parent = (*NeededElem)->Parent;
					MinRightElem->Left = (*NeededElem)->Left;
					if ((*NeededElem)->Parent->Right == (*NeededElem)) {
						(*NeededElem)->Parent->Right = MinRightElem;
					}
					else {
						(*NeededElem)->Parent->Left = MinRightElem;
					}
				}
				else {
					MinRightElem->Right->Parent = MinRightElem->Parent;
					MinRightElem->Parent->Left = MinRightElem->Right;
					MinRightElem->Left = (*NeededElem)->Left;
					MinRightElem->Right = (*NeededElem)->Right;
					MinRightElem->Parent = (*NeededElem)->Parent;
					(*NeededElem)->Left->Parent = MinRightElem;
					(*NeededElem)->Right->Parent = MinRightElem;
					if ((*NeededElem)->Parent->Right == (*NeededElem)) {
						(*NeededElem)->Parent->Right = MinRightElem;
					}
					else {
						(*NeededElem)->Parent->Left = MinRightElem;
					}
				}
			}
		}
	}
	//������� ������ �������
	delete (*NeededElem);
	(*NeededElem) = NULL;
	delete NeededElem;
	return 1;
}



void DemageTree(AUTOPARK_Tree* Branch) {
	if (Branch == NULL)
		return;
	else {
		DemageTree(Branch->Left);
		DemageTree(Branch->Right);
		delete Branch;
		Branch = NULL;
		return;
	}
}