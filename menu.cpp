#include "header.h"

void MainMenu() {
	system("cls");
	cout << "1. �������� ������." << endl;
	cout << "2. ������� ������." << endl;
	cout << "3. ������������� ������." << endl;
	cout << "4. �������� ������." << endl;
	cout << "5. ������ �����������." << endl;
	cout << "6. ��������� ������." << endl;
	cout << "7. ������� ������ ���� � �������." << endl;
	cout << "0. �����." << endl;
	char Answer = _getch();
	switch (Answer) {
	case '1':
		InputData();
		break;
	case '2':
		DeleteDataMain();
		break;
	case '3':
		CorrectData();
		break;
	case '4':
		ShowDataMenu();
		break;
	case '5':
		AllOportunuties();
		break;
	case '6':
		SavingData();
		break;
	case '7':
		if (Data_is_Saved) {
			DemageTree(Root);
			Root = NULL;
			StartProgramm();
			return;
		}
		SavingData();
		DemageTree(Root);
		Root = NULL;
		StartProgramm();
		break;
	case '0':
		if (Data_is_Saved) {
			DemageTree(Root);
			remove("BUFER_DATA.txt");
			if (!rename("BASE_old.txt", "BASE.txt")) {}
			exit(0);
		}
		SavingData();
		DemageTree(Root);
		remove("BUFER_DATA.txt");
		if (!rename("BASE_old.txt", "BASE.txt")) {}
		exit(0);
		break;
	case 107:
		if (Data_is_Saved) {
			DemageTree(Root);
			remove("BUFER_DATA.txt");
			if (!rename("BASE_old.txt", "BASE.txt")) {}
			exit(0);
		}
		SavingData();
		DemageTree(Root);
		remove("BUFER_DATA.txt");
		if (!rename("BASE_old.txt", "BASE.txt")) {}
		exit(0);
		break;
	default:
		MainMenu();
	}
	MainMenu();
}

void ShowDataMenu() {
	system("cls");
	cout << "1. �������� � ���� ������." << endl;
	cout << "2. ������� � ���� ������." << endl;
	cout << "0. ��������� �����." << endl;
	char Answer = _getch();
	switch (Answer) {
	case '1':
		ShowData();
		break;
	case '2':
		system("cls");
		cout << "\t\t\t����� ������ � ���� ������" << endl << endl;
		cout << "\t��� �������� -- ���������� ��������� -- ����� �������� -- ����� �������� -- ������� � �����" << endl;
		DataAvailibility();
		PrintTreeAsTree(Root, 0);
		MenuAfterOutput();
		break;
	case '0':
		MainMenu();
		break;
	case 107:
		if (Data_is_Saved) {
			DemageTree(Root);
			remove("BUFER_DATA.txt");
			if (!rename("BASE_old.txt", "BASE.txt")) {}
			exit(0);
		}
		SavingData();
		DemageTree(Root);
		remove("BUFER_DATA.txt");
		if (!rename("BASE_old.txt", "BASE.txt")) {}
		exit(0);
		break;
	default:
		ShowDataMenu();
	}
}

void AllOportunuties() {
	system("cls");
	cout << "1. ���������� ������." << endl;
	cout << "2. �������� ������." << endl;
	cout << "3. �������������� ������." << endl;
	cout << "4. ����� ������ �� ������� �����." << endl;
	cout << "5. ������������ ������� ���������." << endl;
	cout << "6. ����� �������� � ���������� ������ ���������." << endl;
	cout << "7. ���������� ������ �� ������ ��������." << endl;
	cout << "8. ����� ������." << endl;
	cout << "9. ������� ��� ������." << endl;
	cout << "0. ��������� �����." << endl;
	char Answer = _getch();
	switch (Answer) {
	case '1':
		InputData();
		break;
	case '2':
		DeleteDataMain();

		break;
	case '3':
		CorrectData();
		break;
	case '4':
		SearchForLetter();
		break;
	case '5':
		ShowListOfBus();
		break;
	case '6':
		ShowMaxValutation();
		break;
	case '7':
		ResortingMain();
		ShowData();
		break;
	case '8':
		ShowDataMenu();
		break;
	case '9':
		cout << "�� ����� ������ ������� ��� ������? ������� '�' ��� '�'";
		Answer = GetKey();
		if (Answer == '�') {
			cout << endl << endl << "��������� ��� ���, �� ����� ������ ������� ��� ������?" << endl << "����� ����, ��� �� ������� �, �� �� ������� �� ������������  ������� '�' ��� '�'";
			Answer = GetKey();
			if (Answer == '�') {
				cout << endl << endl << "�� ������ ��������? ������� '�' ��� '�'";
				Answer = GetKey();
				if (Answer == '�') {
					DemageTree(Root);
					Root = NULL;
					AllOportunuties();
				}
				else {
					return;
				}
			}
			else {
				return;
			}
		}
		else {
			return;
		}
		break;
	case '0':
		MainMenu();
		break;
	case 107:
		if (Data_is_Saved) {
			remove("BUFER_DATA.txt");
			if (!rename("BASE_old.txt", "BASE.txt")) {}
			DemageTree(Root);
			exit(0);
		}
		SavingData();
		DemageTree(Root);
		remove("BUFER_DATA.txt");
		if (!rename("BASE_old.txt", "BASE.txt")) {}
		exit(0);
		break;
	default:
		AllOportunuties();
	}
}

void MenuAfterOutput() {
	cout << endl << "�������� ���������� ��������" << endl;
	cout << "1. �������� ������." << endl;
	cout << "2. ������� ������." << endl;
	cout << "3. ������������� ������." << endl;
	cout << "4. ��������� ������." << endl;
	cout << "0. ��������� � ������� ����." << endl;
	char Answer = _getch();
	while (Answer != '0' && Answer != '1' && Answer != '2' && Answer != '3' && Answer != '4') {
		cout << "�������� ������� ������!" << endl;
		cout << "�������� ���������� �������!" << endl;
		Answer = _getch();
	}
	switch (Answer) {
	case '1':
		InputData();
		break;
	case '2':
		DeleteDataMain();
		break;
	case '3':
		CorrectData();
		break;
	case '4':
		SavingData();
		break;
	case '0':
		MainMenu();
		break;
	case 107:
		if (Data_is_Saved) {
			DemageTree(Root);
			remove("BUFER_DATA.txt");
			if (!rename("BASE_old.txt", "BASE.txt")) {}
			exit(0);
		}
		SavingData();
		DemageTree(Root);
		remove("BUFER_DATA.txt");
		if (!rename("BASE_old.txt", "BASE.txt")) {}
		exit(0);
		break;
	}
}