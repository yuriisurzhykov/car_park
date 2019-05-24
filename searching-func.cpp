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
	cout << "Введите букву для поиска водителя, или введите 0 , чтобы вернуться назад: ";
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
			cout << "Введите только ОДИН символ, или введите 0 , чтобы вернуться назад" << endl;
			cin.clear();
			getline(cin, SearchChar);
		}
		else if (!CheckStringToNumb(SearchChar)) {
			cout << "Имя не содердит цифр!" << endl << "Введите нужную букву, или введите 0 , чтобы вернуться назад: ";
			cin.clear();
			getline(cin, SearchChar);
		}
	}
	system("cls");
	cout << endl << "\t\t\t\t\tПОИСК ВОДИТЕЛЕЙ НА ЗАДАННУЮ БУКВУ" << endl << endl;
	HeadTable();
	if (!SearchDriver(Root, SearchChar[0], AmountFindsElem)) {
		cout << "\tВодителей на букву " << SearchChar[0] << " нет!" << endl;
	}
	cout << "\tПовторить поиск? Нажмите 'Д' или 'Н'" << endl;
	cin.clear();
	char Answer = GetKey();
	if (Answer == 'н') {
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
			if (Branch->Presense == 'д') cout << "    да     ";
			else cout << "    нет    ";
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
	cout << endl << "\t\t\t\tДАННЫЕ О ВОДИТЕЛЕ(-ЯХ) С НАЙБОЛЬШИМ ЧИСЛОМ НАРУШЕНИЙ" << endl << endl;
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
		if (Branch->Presense == 'д') cout << "    да     ";
		else cout << "    нет    ";
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
	cout << "Выберите действие." << endl;
	cout << "1. Показать список выехавших автобусов." << endl;
	cout << "2. Показать список оставшихся автобусов." << endl;
	cout << "0. Вернуться назад." << endl;
	cin.clear();
	char Answer = _getch();
	switch (Answer) {
	case '1':
		system("cls");
		cout << endl << "\t\t\tСПИСОК ВЫЕХАВШИХ АВТОБУСОВ" << endl << endl;
		cout << "\t" << "+----+------------------------------------------+ " << endl;
		cout << "\t" << "|  № |  Номер автобуса  |    Номер  | Наличие в | " << endl;
		cout << "\t" << "| п/п|                  |  маршрута |   парке   | " << endl;
		cout << "\t" << "+----+------------------------------------------+ " << endl;
		counter = ShowBus(Root, 'н');
		if (counter == 0) {
			cout << endl << "\t" << "Все автобусы находяться в парке" << endl;
		}
		system("pause");
		ShowListOfBus();
		break;
	case '2':
		system("cls");
		cout << endl << "\t\t\tСПИСОК ОСТАВШИХСЯ АВТОБУСОВ" << endl << endl;
		cout << "\t" << "+----+------------------------------------------+" << endl;
		cout << "\t" << "|  № |  Номер автобуса  |    Номер  | Наличие в |" << endl;
		cout << "\t" << "| п/п|                  |  маршрута |   парке   |" << endl;
		cout << "\t" << "+----+------------------------------------------+" << endl;
		counter = ShowBus(Root, 'д');
		if (counter == 0) {
			cout << endl << "\t" << "В парке нет автобусов" << endl;
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
			if (CharPresence == 'н')
				cout << "    нет    ";
			else cout << "     да    ";
			cout << "|" << endl;
			cout << "\t" << "+----+------------------------------------------+" << endl;
		}
		int ForReturn = (ShowBus(Branch->Left, CharPresence) + Position) + (ShowBus(Branch->Right, CharPresence) + Position);
		return ForReturn;
	}
}