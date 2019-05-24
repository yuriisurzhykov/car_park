#include "header.h"

void MainMenu() {
	system("cls");
	cout << "1. Добавить данные." << endl;
	cout << "2. Удалить данные." << endl;
	cout << "3. Редактировать данные." << endl;
	cout << "4. Показать данные." << endl;
	cout << "5. Другие возможности." << endl;
	cout << "6. Сохранить данные." << endl;
	cout << "7. Открыть другой файл с данными." << endl;
	cout << "0. Выход." << endl;
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
	cout << "1. Вывестив в виде списка." << endl;
	cout << "2. Вывести в виде дерева." << endl;
	cout << "0. Вернуться назад." << endl;
	char Answer = _getch();
	switch (Answer) {
	case '1':
		ShowData();
		break;
	case '2':
		system("cls");
		cout << "\t\t\tВЫВОД ДАННЫХ В ВИДЕ ДЕРЕВА" << endl << endl;
		cout << "\tИмя водителя -- Количество нарушений -- Номер автобуса -- Номер маршрута -- Наличие в парке" << endl;
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
	cout << "1. Добавление данных." << endl;
	cout << "2. Удаление данных." << endl;
	cout << "3. Редактирование данных." << endl;
	cout << "4. Поиск данных на заданую букву." << endl;
	cout << "5. Формирование списков автобусов." << endl;
	cout << "6. Поиск водителя с найбольшим числом нарушений." << endl;
	cout << "7. Сортировка данных по номеру автобуса." << endl;
	cout << "8. Вывод данных." << endl;
	cout << "9. Удалить все данные." << endl;
	cout << "0. Вернуться назад." << endl;
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
		cout << "Вы точно хотите удалить все данные? Нажмите 'Д' или 'Н'";
		Answer = GetKey();
		if (Answer == 'д') {
			cout << endl << endl << "Подумайте еще раз, вы точно хотите удалить все данные?" << endl << "После того, как вы нажмете Д, вы не сможете их восстановить  Нажмите 'Д' или 'Н'";
			Answer = GetKey();
			if (Answer == 'д') {
				cout << endl << endl << "Вы хорошо подумали? Нажмите 'Д' или 'Н'";
				Answer = GetKey();
				if (Answer == 'д') {
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
	cout << endl << "ВЫБЕРИТЕ ДАЛЬНЕЙШЕЕ ДЕЙСТВИЕ" << endl;
	cout << "1. Добавить данные." << endl;
	cout << "2. Удалить данные." << endl;
	cout << "3. Редактировать данные." << endl;
	cout << "4. Сохранить данные." << endl;
	cout << "0. Вернуться в главное меню." << endl;
	char Answer = _getch();
	while (Answer != '0' && Answer != '1' && Answer != '2' && Answer != '3' && Answer != '4') {
		cout << "Неверный вариант ответа!" << endl;
		cout << "Выберите правильный вариант!" << endl;
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