#include "header.h"

/*
	������ ������������� ������
*/
void CorrectData() {
	system("cls");
	AUTOPARK_Tree *CorrectObj = NULL; // ��������� ��������� ���� ����� ���������
	cout << "\t\t\t\t\t������������� ������" << endl;
	HeadTable(); //������� ����� ������
	DataAvailibility(); //��������� ���� �� ������ � ����� ������
	PrintTree(Root); //������� ��� ������, ���� ��� ����
	string SearchData; //��������� ������ ��� ������ �������
	cout << endl << "������� ��� ��� ������������� ��� ������� 0, ����� ��������� �����:  ";
	cin.clear();
	getline(cin, SearchData); // ��������� ��� ������
	if (SearchData[0] == '0') { //���� ������������ ���� 0, ������ ������������ � ������� ����
		return;
	}
	while (SearchData[0] == '\0') { //���� ������������ ������ Enter
		cout << "��� ������ ��� ����������!" << endl; // ������� ��������� �� ������
		cout << "������� ��� ��� �������������: " << endl;
		cin.clear();
		getline(cin, SearchData); //� ������ ������ ������ ������
	}
	CorrectObj = SearchName(Root, SearchData); //������� ������ ��� �������(������� ���������� ��������� �� ������ ������)
	cin.clear(); //�������� �����
	while (CorrectObj == NULL) { //���� ��������� ������� �� ������
		cout << "� ���� ��� ������ ��������!" << endl; //������� ��������� �� ������
		cout << "��������� �������? ������� � ��� �" << endl;
		char Answer = GetKey();
		if (Answer == '�') {
			return;
		}
		cout << endl << "������� ��� ��� �������������, ��� ������� 0, ����� ��������� �����: ";
		cin.clear();
		getline(cin, SearchData);
		if (SearchData[0] == '0') { //���� ������������ ���� 0, ������ ������������ � ������� ����
			return;
		}
		while (SearchData[0] == '\0') { //���� ������������ ������ Enter
			cout << "��� ������ ��� ����������!" << endl;
			cout << "������� ��� ��� �������������: " << endl;
			getline(cin, SearchData);
		}
		cin.clear();
		CorrectObj = SearchName(Root, SearchData);
	}
	//���� ������������ ����������� ������� ���� �������������
	cout << "�������� ���� �������������" << endl;
	cout << "1. ��� ��������." << endl;
	cout << "2. ���������� ��������� ��������." << endl;
	cout << "3. ����� ��������." << endl;
	cout << "4. ����� �������� ��������." << endl;
	cout << "5. ����������� � �����." << endl;
	cout << "0. �������� � ��������� �����." << endl;
	char Answer = _getch();
	while (Answer < '0' && Answer > '5') {
		cout << "��� ������ �������� ������!" << endl;
		cout << "�������� ���������� �������!" << endl;
		Answer = _getch();
		if (Answer == '0')
			return;
	}
	AUTOPARK_Tree* Temp = new AUTOPARK_Tree; //��������� ��������� ���� ���������, �������� ��� ���� ������. ��� ������ ����� �������������� ��� ��������� ���������
	
	Temp->Name = CorrectObj->Name;//�������� ���� ��������� ������� � ���� ��������� ���������
	Temp->AmountValutation = CorrectObj->AmountValutation;
	Temp->NumberBus = CorrectObj->NumberBus;
	Temp->NumberWay = CorrectObj->NumberWay;
	Temp->Presense = CorrectObj->Presense;

	string TempStr; //��������� ������, � ������� ����� �������� ��������� ������, ��� �������� � �.�.
	switch (Answer) {
	case '1':
		cout << "������� ����� ��� ��������: ";
		cin.clear();
		getline(cin, Temp->Name); //��������� ������
		//���������, ����� ������������ �� ���� � ���� ����� �����, ��� �����-�� ������ �������, ����� ����
		while (CheckExistence(Root, *Temp, 1) 
			&& (CorrectObj->Name != Temp->Name) 
			|| !CheckStringToNumb(Temp->Name) 
			|| Temp->Name[0] == '\0') 
		{
			if (CheckExistence(Root, *Temp, 1) && (CorrectObj->Name != Temp->Name)) {
				cout << endl << "� ���� ��� ���� �������� � ����� ������!" << endl;
			}
			else if (Temp->Name[0] == '\0') {
				cout << endl << "��� ������ ��� ����������! ������� ������!" << endl;
			}
			else {
				cout << "� ����� �� ����� ���� ������� ��������, ����� ����!" << endl;
			}
			cout << "������� ����� ��� ��������: ";
			cin.clear();
			getline(cin, Temp->Name);
		}
		cin.clear();
		break;
	case '2':
		cout << "������� ���������� ��������� ��������: ";
		cin.clear();
		getline(cin, TempStr); //��������� � ������ ��������� ������
		while (!CheckInt(TempStr) || TempStr[0] == '\0' || StringToInt(TempStr) >= 1000) { //���������, ����� � ������ �� ���� ������� ��������, ����� ����
			if (TempStr[0] == '\0') {
				cout << endl << "��� ������ ��� ����������! ������� ������!" << endl;
			}
			else if (StringToInt(TempStr) >= 1000) {
				cout << endl << "������� ������� �����! ������ �������� ������ 1000" << endl;
			}
			else {
				cout << endl << "������� ���������� ��������! (������ �����)" << endl;
			}
			cout << "������� ���������� ��������� ��������: ";
			cin.clear();
			getline(cin, TempStr);
		}
		Temp->AmountValutation = StringToInt(TempStr); //���� ������������ ���� ������ �����, �� ��������������� ������ � ����� ���� int
		cin.clear();
		break;
	case '3':
		cout << "������� ����� ��������: ";
		cin.clear();
		getline(cin, Temp->NumberBus); //��������� ����� ��������
		//������ ��������, ����� ������������� �� ���� ������ �������, ����� ���� ��� ����, ����� �� ���� Enter ��� 0
		while (Temp->NumberBus.size() > 8 || //����� ����������� �������� ���� �� ������ 6
			   Temp->NumberBus[0] == '\0' || //����� �� ��� ������ Enter
			   !CheckForNotLetter(Temp->NumberBus) || //����� �� ������������ �� ���� ������ �������, ����� ���� ��� ����
			   StringToInt(Temp->NumberBus) == 0) { //� ����� ������������� �� ���� 0

			if (Temp->NumberBus[0] == '\0') {
				cout << endl << "��� ������ ��� ����������! ������� ������!" << endl;
			}
			else if (StringToInt(Temp->NumberBus) == 0) {
				cout << "����� �� ����� ���� 0!" << endl;
			}
			else if (!CheckForNotLetter(Temp->NumberBus)) {
				cout << "� ������ �� ����� �������������� ������ �������, �����  ���� � ����!" << endl;
			}
			else {
				cout << endl << "������������ ���������� �������� 8!" << endl;
			}
			cout << "������� ����� ��������: ";
			cin.clear();
			getline(cin, Temp->NumberBus);
		}
		cin.clear();
		break;
	case '4':
		cout << "������� ����� ��������: ";
		cin.clear();
		getline(cin, TempStr);
		//���������, ����� ������������ �� ���� �����, ��� ����� �� ���� 0, ��� ����� �� ���� Enter, � ����� �������� ���� �� ������ 4
		while (!CheckInt(TempStr)
			|| TempStr[0] < (1 - '0')
			|| TempStr[0] == '\0'
			|| StringToInt(TempStr) > 2000
			|| StringToInt(TempStr) == 0)
		{
			if (TempStr[0] == '\0') {
				cout << endl << "��� ������ ��� ����������! ������� ������!" << endl;
			}
			else if (StringToInt(TempStr) > 2000) {
				cout << endl << "������� ������� �����! ������ �������� ������ 2000" << endl;
			}
			else if (StringToInt(TempStr) == 0) {
				cout << "����� �� ����� ���� 0!" << endl;
			}
			else {
				cout << endl << "������� ���������� ��������!" << endl;
			}
			cout << "������� ����� ��������: ";
			cin.clear();
			getline(cin, TempStr);
		}
		Temp->NumberWay = StringToInt(TempStr);
		cin.clear();
		break;
	case '5':
		cout << "������� ���������� � �����?  ������� '�' ��� '�'" << endl;
		Temp->Presense = GetKey(); //����������� ����������� �������� � �����
		break;
	case '0':
		return;
		break;
	}
	TempStr = CorrectObj->Name;
	cout << endl << "�� ����� ������ �������� ������ � �������� " << CorrectObj->Name << "? ������� '�' ��� '�'" << endl;
	if ((Answer = GetKey()) == '�') { //���� ���, �� ������ ������� ���������, ��� ������ �� ���� �������
		cout << "������ ��������������";
	}
	else {							  //���� ������������� ����� "��", 
		DeleteData(CorrectObj->Name); //������ ������� ������������� ������
		PushData(&Root, NULL, *Temp); //� ����� ������ ������� ���������� ������
		cout << endl << "������ � " << TempStr << " ������� ��������!" << endl;
		Data_is_Saved = false;
	}
	delete Temp; // ������� ��������� ���������
	system("cls");
	MenuAfterOutput(); //������������ � ������� ����
}
