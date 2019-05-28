#include "header.h"

#define _CRT_SECURE_NO_WARNINGS
int ReadFromBuferFile(AUTOPARK_Tree** NeededRoot, string FileName);

/*
	Функция открывает файлы с данными.
	Просим пользователя выбрать способ получения данных: из основной базы данных, или из пользовательской.
	Если из пользовательской, то просим ввести имя файла, если файл удалось открыть, выводим сообщение на экран,
	что считываение данных удалось. Если не получилось, спрашиваем, хочет ли пользователь еще раз ввести имя файла, если да, то 
*/
void StartProgramm() {
	bool SuccessRead = false;
	char Answer;
	system("cls");
	cout << "Выберите способ открытия файла" << endl;
	cout << "________________________________" << endl;
	cout << "1. Открыть основную базу данных." << endl;
	cout << "2. Открыть свою базу данных." << endl;
	cout << "3. Выполнить запуск без открытия файла с данными." << endl;
	cout << "0. Выход.";
	Answer = _getch();
	while (Answer != '1' && Answer != '2' && Answer != '3' && Answer != '0') {
		cout << endl << "Нет такого варианта ответа!" << endl;
		cout << "Выберите способ открытия файла" << endl;
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
			cout << endl << "Введите имя файлa для открытия: ";
			cin.clear();
			getline(cin, FileName);
			while (!CorrectPathName(FileName)) {
				cout << endl << "Нельзя использовать симовлы *, <, >, +, =, /, !, #, . и др." << endl;
				cout << "Введите название файла: ";
				cin.clear();
				getline(cin, FileName);
			}
			if (!ReadFromFile(FileName + ".txt")) {
				cout << endl << "Неверно введено имя файла, или путь к файлу!" << endl;
				cout << "Попробовать еще раз?  Нажмите 'Д' или 'Н'" << endl;
			}
			else {
				SuccessRead = true;
				break;
			}
			Answer = GetKey();
			if (Answer == 'н')
				break;

		} while (Answer == 'д');
		if (SuccessRead) {
			Data_is_Saved = true;
			cout << "Данные успешно получены из файла!" << endl;
			CheckBufer();
			return;
		}
	}
	
	if (!ReadFromFile("BASE.txt")) {
		if (ReadFromFile("BASE_old.txt")) {
			cout << endl << "Получить данные из основной базы не получилось" << endl;
			cout << "Данные получены из файла BASE_old.txt копии." << endl;
			system("cls");
		}
		else {
			cout << endl << "Не удалось получить данные. Возможно файл был перемещен или удален!" << endl;
			system("cls");
		}
	}
	else {
		remove("BASE_old.txt");
		if (!rename("BASE.txt", "BASE_old.txt")) {}
		cout << endl << "Данные успешно получены из файла BASE.txt!";
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
		cout << "У вас есть несохраненные данные с предыдущего открытия програмы." << endl;
		cout << "Вы хотите их просмотреть?  Нажмите клавишу Д или Н" << endl;
		Answer = GetKey();
		if (Answer == 'д') {
			AUTOPARK_Tree* BuferTree = NULL;
			ReadFromBuferFile(&BuferTree, "BUFER_DATA.txt");
			system("cls");
			HeadTable();
			PrintTree(BuferTree);
			cout << endl << "Хотите использовать эти данные?  Нажмите клавишу Д или Н";
			Answer = GetKey();
			if (Answer == 'д') {
				ReadFromFile("BUFER_DATA.txt");
				Data_is_Saved = false;
			}
			remove("BUFER_DATA.txt");
			DemageTree(BuferTree);
		}
	}
}

/*
	Функция чтения данных из файли буферных данных.
	Входные данные:
		1) AUTOPARK_Tree** NeededRoot - указатель типа структуры, на указатель типа структуры
		2) string FileName - имя буферного файла.
	Возвращает: 
		1) 0 - если данные считать не удалось
		2) 1 - если чтение удалось
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
	Функция чтения данных из любого файла, с последующим занесением данных в дерево.
	Входные данные:
		1) string FileName - название файла;
	Возвращает: 
		1) 0 - если файл не удалось открыть для чтения;
		2) 1 - если данные с файла прочитаны, либо если файл существует, но данных там нет
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
	Функция записи вводимы данных, во время работы программы. 
	Входные параметры: 
		1) AUTOPARK_Tree *Data - укзатель на объект, которые необходимо занести в файл
		2) string FileName - имя файла.
	Функция ничего не возвращает.
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
	Фукнция записывает данные в файл проходя по всему дереву.
	Входные параметры: 
		1) AUTOPARK_Tree *Data - укзатель на объект, которые необходимо занести в файл
		2) string FileName - имя файла.
	Функция ничего не возвращает.
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
	cout << endl << "У вас есть несохраненные данные." << endl;
	cout << "Хотите ввести имя файла для сохранения? Нажмите клавишу Д или Н";
	Answer = GetKey();
	switch (Answer) {
	case 'д': 
	{
		cout << endl << "Введите название файла для сохранения: ";
		cin.clear();
		getline(cin, NameFile);
		while (!CorrectPathName(NameFile)) {
			cout << "Нельзя использовать симовлы *, <, >, +, =, /, !, #, и т.д." << endl;
			cout << "Введите название файла для сохранения: ";
			cin.clear();
			getline(cin, NameFile);
		}
		NameFile += ".txt";
		char* FileName = new char[NameFile.size() + 1];
		strcpy(FileName, NameFile.c_str());
		remove(FileName);
		delete[]FileName;
		if (!WriteInFile(Root, NameFile)) {
			cout << endl << "Данные не были сохранены в указанный файл!" << endl;
			cout << "Хотите еще попробовать еще раз? Нажмите клавишу Д или Н" << endl;
			Answer = GetKey();
			if (Answer == 'д')
				SavingData();
		}
		else {
			cout << endl << "Данные успешно сохранены!" << endl;
			system("pause");
		}
		break;
	}
	case 'н':
		remove("BASE.txt");
		if (!WriteInFile(Root, "BASE.txt")) {
			cout << endl << "Произошла ошибка при записи файла с указанным именем!";
			SavingData();
		}
		else {
			cout << endl << "Данные успешно записаны в файл BASE.txt!";
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