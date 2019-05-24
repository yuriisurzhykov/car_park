#include "header.h"

void InputData() {
	system("cls");
	AUTOPARK_Tree* Data = new AUTOPARK_Tree;
	cout << endl << "\t\t���� ������" << endl << endl;
	cout << "������� ��� �������� ��� ������� 0, ����� ��������� �����: ";
	cin.clear();
	getline(cin, Data->Name);
	if (Data->Name[0] == '0') {
		return;
	}
	while (!CheckStringToNumb(Data->Name) || Data->Name[0] == '\0') {
		if (Data->Name[0] == '\0') {
			cout << endl << "��� ������ ��� ����������! ������� ������!" << endl;
		}
		else {
			cout << endl << "� ����� �� ����� ���� ���� ��� ��������!" << endl;
		}
		cout << "������� ��� ��������: ";
		cin.clear();
		getline(cin, Data->Name);
	}
	if (CheckExistence(Root, *Data, 1)) {
		cout << endl << "������ � ����� ������ ��� ����!" << endl;
		delete Data;
	}
	else {
		cout << "������� ����������� ��������� ��������: ";
		string Temp;
		cin.clear();
		getline(cin, Temp);
		while (!CheckInt(Temp) || Temp[0] == '\0' || Temp.size() > 3) {
			if (!CheckInt(Temp)) {
				cout << "������ ������� �����!" << endl;
			}
			else if (Temp.size() > 3) {
				cout << endl << "������� ������� �����! ������ �������� ������ 1000" << endl;
			}
			else if (Temp[0] == '\0') {
				cout << endl << "��� ������ ��� ����������! ������� ������!" << endl;
			}
			else {
				cout << endl << "������� ���������� ��������!" << endl;
			}
			cout << "������� ����������� ��������� ��������: ";
			cin.clear();
			getline(cin, Temp);
		}
		Data->AmountValutation = StringToInt(Temp);
		cout << "������� ����� ��������: ";
		cin.clear();
		getline(cin, Data->NumberBus);
		while ( Data->NumberBus.size() > 8 || 
				Data->NumberBus[0] == '\0' || 
				!CheckForNotLetter(Data->NumberBus) || 
				(StringToInt(Data->NumberBus) == 0 )) 
		{
			if (Data->NumberBus[0] == '\0') {
				cout << endl << "��� ������ ��� ����������! ������� ������!" << endl;
			}
			else if (StringToInt(Data->NumberBus) == 0) {
				cout << "����� �� ����� ���� 0!" << endl;
			}
			else if (!CheckForNotLetter(Data->NumberBus)) {
				cout << "� ������ �� ����� �������������� ������ �������, �����  ���� � ����!" << endl;
			}
			else {
				cout << endl << "������������ ���������� �������� 8!" << endl;
			}
			cout << "������� ����� ��������: ";
			cin.clear();
			getline(cin, Data->NumberBus);
		}
		cout << "������� ����� ��������: ";
		cin.clear();
		getline(cin, Temp);
		while (!CheckInt(Temp) 
			|| Temp[0] < (1 - '0') 
			|| Temp[0] == '\0' 
			|| StringToInt(Temp) > 2000 
			|| StringToInt(Temp) == 0)
		{
			if (Temp[0] == '\0') {
				cout << endl << "��� ������ ��� ����������! ������� ������!" << endl;
			}
			else if (StringToInt(Temp) > 2000) {
				cout << endl << "������� ������� �����! ������ �������� ������ 2000" << endl;
			}
			else if (StringToInt(Temp) == 0) {
				cout << "����� �� ����� ���� 0!" << endl;
			}
			else {
				cout << endl << "������� ���������� ��������!" << endl;
			}
			cout << "������� ����� ��������: ";
			cin.clear();
			getline(cin, Temp);
		}
		Data->NumberWay = StringToInt(Temp);
		cout << "������� ���������� � �����?  ������� '�' ��� '�'" << endl;
		cin.clear();
		Data->Presense = GetKey();
		WriteBuferData(Data, "BUFER_DATA.txt");
		if (!PushData(&Root, NULL, *Data)) {
			cout << endl << "��������� ������ ��� ���������� ������!" << endl;
			delete Data;
		}
		else {
			cout << endl << "������ ������� ����c���!" << endl;
			delete Data;
		}
	}
	cin.clear();
	cout << "������ ��� ������ ������? ������� � ��� �";
	char Answer = GetKey();
	if (Answer == '�') {
		Data_is_Saved = false;
		return;
	}
	else InputData();
}

void HeadTable() {
	Position = 0;
	cout << "\t" << "+----+------------------------------------------------+------------------------------------------+" << endl;
	cout << "\t" << "|  � |         ��� ��������             |  ���������� |  ����� ��������  |   �����   | ������� � |" << endl;
	cout << "\t" << "| �/�|                                  |  ���������  |                  |  �������� |   �����   |" << endl;
	cout << "\t" << "+----+------------------------------------------------+------------------------------------------+" << endl;
}

void ShowData() {
	system("cls");
	cout << endl << "\t\t\t\t\t\t���� ������" << endl << endl;
	HeadTable();
	DataAvailibility();
	PrintTree(Root);
	MenuAfterOutput();
}

void PrintTreeAsTree(AUTOPARK_Tree *Branch, int level) {
	if (Branch == NULL) return;
	else {
		PrintTreeAsTree(Branch->Right, level + 1);
		for (int i = 0; i < level; i++)
			cout << "    ";
		cout << Branch->Name << "   " << Branch->AmountValutation << "   " << Branch->NumberBus << "   " << Branch->NumberWay << "   " << Branch->Presense << endl;
		PrintTreeAsTree(Branch->Left, level + 1);
	}
}

void PrintTree(AUTOPARK_Tree *Branch) {
	if (Branch == NULL) return;
	else {
		PrintTree(Branch->Left);
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
		PrintTree(Branch->Right);
	}
}


AUTOPARK_Tree* PushData(AUTOPARK_Tree** Branch, AUTOPARK_Tree* ParentFunc, AUTOPARK_Tree Data) {
	if ((*Branch) == NULL) {
		(*Branch) = new AUTOPARK_Tree;
		(*Branch)->Name = Data.Name;
		(*Branch)->AmountValutation = Data.AmountValutation;
		(*Branch)->NumberBus = Data.NumberBus;
		(*Branch)->NumberWay = Data.NumberWay; 
		(*Branch)->Presense = Data.Presense;
		(*Branch)->Left = (*Branch)->Right = NULL;
		(*Branch)->Parent = ParentFunc;
		return (*Branch);
	}
	else {
		if (Data.Name >= (*Branch)->Name)
			return PushData(&(*Branch)->Right, (*Branch), Data);
		else 
			return PushData(&(*Branch)->Left, (*Branch), Data);
	}
}
