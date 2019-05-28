#include "header.h"

#define _CRT_SECURE_NO_WARNINGS
int ReadFromBuferFile(AUTOPARK_Tree** NeededRoot, string FileName);

/*
	������� ��������� ����� � �������.
	������ ������������ ������� ������ ��������� ������: �� �������� ���� ������, ��� �� ����������������.
	���� �� ����������������, �� ������ ������ ��� �����, ���� ���� ������� �������, ������� ��������� �� �����,
	��� ����������� ������ �������. ���� �� ����������, ����������, ����� �� ������������ ��� ��� ������ ��� �����, ���� ��, �� 
*/
void StartProgramm() {
	bool SuccessRead = false;
	char Answer;
	system("cls");
	cout << "�������� ������ �������� �����" << endl;
	cout << "________________________________" << endl;
	cout << "1. ������� �������� ���� ������." << endl;
	cout << "2. ������� ���� ���� ������." << endl;
	cout << "3. ��������� ������ ��� �������� ����� � �������." << endl;
	cout << "0. �����.";
	Answer = _getch();
	while (Answer != '1' && Answer != '2' && Answer != '3' && Answer != '0') {
		cout << endl << "��� ������ �������� ������!" << endl;
		cout << "�������� ������ �������� �����" << endl;
		Answer = _getch();
	}
	if (Answer == '0')
		exit(0);
	if (Answer == '3') {
		Data_is_Saved = true;
		MainMenu();
	}
	if (Answer == '2') {
		string FileName;
		do {
			cout << endl << "������� ��� ����a ��� ��������: ";
			cin.clear();
			getline(cin, FileName);
			while (!CorrectPathName(FileName)) {
				cout << endl << "������ ������������ ������� *, <, >, +, =, /, !, #, . � ��." << endl;
				cout << "������� �������� �����: ";
				cin.clear();
				getline(cin, FileName);
			}
			if (!ReadFromFile(FileName + ".txt")) {
				cout << endl << "������� ������� ��� �����, ��� ���� � �����!" << endl;
				cout << "����������� ��� ���?  ������� '�' ��� '�'" << endl;
			}
			else {
				SuccessRead = true;
				break;
			}
			Answer = GetKey();
			if (Answer == '�')
				break;

		} while (Answer == '�');
		if (SuccessRead) {
			Data_is_Saved = true;
			cout << "������ ������� �������� �� �����!" << endl;
			CheckBufer();
			return;
		}
	}
	
	if (!ReadFromFile("BASE.txt")) {
		if (ReadFromFile("BASE_old.txt")) {
			cout << endl << "�������� ������ �� �������� ���� �� ����������" << endl;
			cout << "������ �������� �� ����� BASE_old.txt �����." << endl;
			system("cls");
		}
		else {
			cout << endl << "�� ������� �������� ������. �������� ���� ��� ��������� ��� ������!" << endl;
			system("cls");
		}
	}
	else {
		remove("BASE_old.txt");
		if (!rename("BASE.txt", "BASE_old.txt")) {}
		cout << endl << "������ ������� �������� �� ����� BASE.txt!";
		system("cls");
	}
	Data_is_Saved = true;
	CheckBufer();
}

void CheckBufer() {
	char Answer;
	ifstream bufer("BUFER_DATA.txt");
	if (bufer.is_open()) {
		bufer.close();
		cout << "� ��� ���� ������������� ������ � ����������� �������� ��������." << endl;
		cout << "�� ������ �� �����������?  ������� ������� � ��� �" << endl;
		Answer = GetKey();
		if (Answer == '�') {
			AUTOPARK_Tree* BuferTree = NULL;
			ReadFromBuferFile(&BuferTree, "BUFER_DATA.txt");
			system("cls");
			HeadTable();
			PrintTree(BuferTree);
			cout << endl << "������ ������������ ��� ������?  ������� ������� � ��� �";
			Answer = GetKey();
			if (Answer == '�') {
				ReadFromFile("BUFER_DATA.txt");
				Data_is_Saved = false;
			}
			remove("BUFER_DATA.txt");
			DemageTree(BuferTree);
		}
	}
}

/*
	������� ������ ������ �� ����� �������� ������.
	������� ������:
		1) AUTOPARK_Tree** NeededRoot - ��������� ���� ���������, �� ��������� ���� ���������
		2) string FileName - ��� ��������� �����.
	����������: 
		1) 0 - ���� ������ ������� �� �������
		2) 1 - ���� ������ �������
*/
int ReadFromBuferFile(AUTOPARK_Tree** NeededRoot, string FileName)
{
	AUTOPARK_Tree* Data;
	Data = new AUTOPARK_Tree;
	ifstream file(FileName);
	if (!file.is_open()) {
		return 0;
	}
	while (file.peek() != EOF) {
		file.ignore();
		getline(file, Data->Name);
		file >> Data->AmountValutation;
		file >> Data->NumberBus;
		file >> Data->NumberWay;
		file >> Data->Presense;
		PushData(NeededRoot, NULL, *Data);
	}
	file.close();
	delete Data;
	return 1;
}

/*
	������� ������ ������ �� ������ �����, � ����������� ���������� ������ � ������.
	������� ������:
		1) string FileName - �������� �����;
	����������: 
		1) 0 - ���� ���� �� ������� ������� ��� ������;
		2) 1 - ���� ������ � ����� ���������, ���� ���� ���� ����������, �� ������ ��� ���
*/
int ReadFromFile(string FileName)
{
	AUTOPARK_Tree* Data;
	Data = new AUTOPARK_Tree;
	ifstream file(FileName);
	if (!file.is_open()) {
		delete Data;
		return 0;
	}
	if (file.eof()) {
		file.close();
		delete Data;
		return 1;
	}
	while (file.peek() != EOF) {
		file.ignore();
		getline(file, Data->Name);
		file >> Data->AmountValutation;
		file >> Data->NumberBus;
		file >> Data->NumberWay;
		file >> Data->Presense;
		PushData(&Root, NULL, *Data);
	}
	file.close();
	delete Data;
	return 1;
}

/*
	������� ������ ������� ������, �� ����� ������ ���������. 
	������� ���������: 
		1) AUTOPARK_Tree *Data - �������� �� ������, ������� ���������� ������� � ����
		2) string FileName - ��� �����.
	������� ������ �� ����������.
*/
void WriteBuferData(AUTOPARK_Tree *Data, string FileName) {
	ofstream file(FileName, ios::app);
	if (!file.is_open())
		return;
	else {
		file << endl << Data->Name << endl;
		file << Data->AmountValutation << endl;
		file << Data->NumberBus << endl;
		file << Data->NumberWay << endl;
		file << Data->Presense;
		file.close();
		return;
	}
}


/*
	������� ���������� ������ � ���� ������� �� ����� ������.
	������� ���������: 
		1) AUTOPARK_Tree *Data - �������� �� ������, ������� ���������� ������� � ����
		2) string FileName - ��� �����.
	������� ������ �� ����������.
*/
int WriteInFile(AUTOPARK_Tree* Data, string FileName)
{
	if (Data == NULL) return 1;
	else {
		ofstream file(FileName, ios::app);
		if (!file.is_open())
			return 0;
		file << endl << Data->Name << endl;
		file << Data->AmountValutation << endl;
		file << Data->NumberBus << endl;
		file << Data->NumberWay << endl;
		file << Data->Presense;
		file.close();
		return WriteInFile(Data->Left, FileName) + WriteInFile(Data->Right, FileName);
	}
}

void SavingData() {
	string NameFile;
	char Answer;
	cout << endl << "� ��� ���� ������������� ������." << endl;
	cout << "������ ������ ��� ����� ��� ����������? ������� ������� � ��� �";
	Answer = GetKey();
	switch (Answer) {
	case '�': 
	{
		cout << endl << "������� �������� ����� ��� ����������: ";
		cin.clear();
		getline(cin, NameFile);
		while (!CorrectPathName(NameFile)) {
			cout << "������ ������������ ������� *, <, >, +, =, /, !, #, � �.�." << endl;
			cout << "������� �������� ����� ��� ����������: ";
			cin.clear();
			getline(cin, NameFile);
		}
		NameFile += ".txt";
		char* FileName = new char[NameFile.size() + 1];
		strcpy(FileName, NameFile.c_str());
		remove(FileName);
		delete[]FileName;
		if (!WriteInFile(Root, NameFile)) {
			cout << endl << "������ �� ���� ��������� � ��������� ����!" << endl;
			cout << "������ ��� ����������� ��� ���? ������� ������� � ��� �" << endl;
			Answer = GetKey();
			if (Answer == '�')
				SavingData();
		}
		else {
			cout << endl << "������ ������� ���������!" << endl;
			system("pause");
		}
		break;
	}
	case '�':
		remove("BASE.txt");
		if (!WriteInFile(Root, "BASE.txt")) {
			cout << endl << "��������� ������ ��� ������ ����� � ��������� ������!";
			SavingData();
		}
		else {
			cout << endl << "������ ������� �������� � ���� BASE.txt!";
			Sleep(1000);
		}
		break;
	}
	remove("BUFER_DATA.txt");
	cin.clear();
	Data_is_Saved = true;
	MainMenu();
	return;
}