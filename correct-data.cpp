#include "header.h"

/*
	ФУНЦИЯ КОРРЕКТИРОВКИ ДАННЫХ
*/
void CorrectData() {
	system("cls");
	AUTOPARK_Tree *CorrectObj = NULL; // Объявляем указатель типа нашей структуры
	cout << "\t\t\t\t\tКОРРЕКТИРОВКА ДАННЫХ" << endl;
	HeadTable(); //Выводим шапку талицы
	DataAvailibility(); //Проверяем есть ли данные в нашем дереве
	PrintTree(Root); //Выводим эти данные, если они есть
	string SearchData; //Объявляем строку для поиска фамилии
	cout << endl << "Введите ФИО для корректировки или введите 0, чтобы вернуться назад:  ";
	cin.clear();
	getline(cin, SearchData); // Считываем эту строку
	if (SearchData[0] == '0') { //Если пользователь ввел 0, значит возвращаемся в главное меню
		return;
	}
	while (SearchData[0] == '\0') { //Если пользователь вводит Enter
		cout << "Нет данных для считывания!" << endl; // Выводим сообщение об ошибке
		cout << "Введите ФИО для корректировки: " << endl;
		cin.clear();
		getline(cin, SearchData); //и заново просим ввести данные
	}
	CorrectObj = SearchName(Root, SearchData); //Находим нужный нам элемент(функция возвращает указатель на нужный объект)
	cin.clear(); //Очищаемя поток
	while (CorrectObj == NULL) { //Если введенный элемент не найден
		cout << "В базе нет такого водителя!" << endl; //Выводим сообщение об ошибке
		cout << "Повторить попытку? Нажмите Д или Н" << endl;
		char Answer = GetKey();
		if (Answer == 'н') {
			return;
		}
		cout << endl << "Введите ФИО для корректировки, или введите 0, чтобы вернуться назад: ";
		cin.clear();
		getline(cin, SearchData);
		if (SearchData[0] == '0') { //Если пользователь ввел 0, значит возвращаемся в главное меню
			return;
		}
		while (SearchData[0] == '\0') { //Если пользователь вводит Enter
			cout << "Нет данных для считывания!" << endl;
			cout << "Введите ФИО для корректировки: " << endl;
			getline(cin, SearchData);
		}
		cin.clear();
		CorrectObj = SearchName(Root, SearchData);
	}
	//Даем пользователю возможность выбрать поле корректировки
	cout << "Выберите поле корректировки" << endl;
	cout << "1. Имя водителя." << endl;
	cout << "2. Количество нарушений водителя." << endl;
	cout << "3. Номер автобуса." << endl;
	cout << "4. Номер маршрута автобуса." << endl;
	cout << "5. Присутствие в парке." << endl;
	cout << "0. Отменить и вернуться назад." << endl;
	char Answer = _getch();
	while (Answer < '0' && Answer > '5') {
		cout << "Нет такого варианта ответа!" << endl;
		cout << "Выберите правильный вариант!" << endl;
		Answer = _getch();
		if (Answer == '0')
			return;
	}
	AUTOPARK_Tree* Temp = new AUTOPARK_Tree; //Объявляем указатель типа структуры, выделяем под него память. Эта память будет использоваться как временное хранилище
	
	Temp->Name = CorrectObj->Name;//Копируем поля найденого объекта в наше временное хранилище
	Temp->AmountValutation = CorrectObj->AmountValutation;
	Temp->NumberBus = CorrectObj->NumberBus;
	Temp->NumberWay = CorrectObj->NumberWay;
	Temp->Presense = CorrectObj->Presense;

	string TempStr; //Объявляем строку, в которую будем заносить временные данные, для проверок и т.п.
	switch (Answer) {
	case '1':
		cout << "Введите новое имя водителя: ";
		cin.clear();
		getline(cin, Temp->Name); //Считываем данные
		//Проверяем, чтобы пользователь не ввел в поле имени цифры, или какие-то другие символы, кроме букв
		while (CheckExistence(Root, *Temp, 1) 
			&& (CorrectObj->Name != Temp->Name) 
			|| !CheckStringToNumb(Temp->Name) 
			|| Temp->Name[0] == '\0') 
		{
			if (CheckExistence(Root, *Temp, 1) && (CorrectObj->Name != Temp->Name)) {
				cout << endl << "В базе уже есть водитель с таким именем!" << endl;
			}
			else if (Temp->Name[0] == '\0') {
				cout << endl << "Нет данных для считывания! Введите данные!" << endl;
			}
			else {
				cout << "В имени не может быть никаких символов, кроме букв!" << endl;
			}
			cout << "Введите новое имя водителя: ";
			cin.clear();
			getline(cin, Temp->Name);
		}
		cin.clear();
		break;
	case '2':
		cout << "Введите количество нарушений водителя: ";
		cin.clear();
		getline(cin, TempStr); //Считываем в строку введенные данные
		while (!CheckInt(TempStr) || TempStr[0] == '\0' || StringToInt(TempStr) >= 1000) { //Проверяем, чтобы в строке не было никаких символов, кроме цифр
			if (TempStr[0] == '\0') {
				cout << endl << "Нет данных для считывания! Введите данные!" << endl;
			}
			else if (StringToInt(TempStr) >= 1000) {
				cout << endl << "Слишком большое число! Введит значение меньше 1000" << endl;
			}
			else {
				cout << endl << "Введите корректное значение! (только цифры)" << endl;
			}
			cout << "Введите количество нарушений водителя: ";
			cin.clear();
			getline(cin, TempStr);
		}
		Temp->AmountValutation = StringToInt(TempStr); //Если пользователь ввел только цифры, то преобразовываем строку в число типа int
		cin.clear();
		break;
	case '3':
		cout << "Введите номер автобуса: ";
		cin.clear();
		getline(cin, Temp->NumberBus); //Считываем номер автобуса
		//Делаем проверку, чтобы пользоваетель не ввел другие символы, кроме цифр или букв, чтобы не ввел Enter или 0
		while (Temp->NumberBus.size() > 8 || //Чтобы колличество символов было не больше 6
			   Temp->NumberBus[0] == '\0' || //Чтобы не был введем Enter
			   !CheckForNotLetter(Temp->NumberBus) || //Чтобы не пользователь не ввел другие символы, кроме цифр или букв
			   StringToInt(Temp->NumberBus) == 0) { //И чтобы пользоваетель не ввел 0

			if (Temp->NumberBus[0] == '\0') {
				cout << endl << "Нет данных для считывания! Введите данные!" << endl;
			}
			else if (StringToInt(Temp->NumberBus) == 0) {
				cout << "Номер не может быть 0!" << endl;
			}
			else if (!CheckForNotLetter(Temp->NumberBus)) {
				cout << "В номере не могут присутствовать другие символы, кроме  букв и цифр!" << endl;
			}
			else {
				cout << endl << "Максимальное количество символов 8!" << endl;
			}
			cout << "Введите номер автобуса: ";
			cin.clear();
			getline(cin, Temp->NumberBus);
		}
		cin.clear();
		break;
	case '4':
		cout << "Введите номер маршрута: ";
		cin.clear();
		getline(cin, TempStr);
		//Проверяем, чтобы пользователь не ввел буквы, или чтобы не ввел 0, или чтобы не ввел Enter, и чтобы значение было не больше 4
		while (!CheckInt(TempStr)
			|| TempStr[0] < (1 - '0')
			|| TempStr[0] == '\0'
			|| StringToInt(TempStr) > 2000
			|| StringToInt(TempStr) == 0)
		{
			if (TempStr[0] == '\0') {
				cout << endl << "Нет данных для считывания! Введите данные!" << endl;
			}
			else if (StringToInt(TempStr) > 2000) {
				cout << endl << "Слишком большое число! Введит значение меньше 2000" << endl;
			}
			else if (StringToInt(TempStr) == 0) {
				cout << "Номер не может быть 0!" << endl;
			}
			else {
				cout << endl << "Введите корректное значение!" << endl;
			}
			cout << "Введите номер маршрута: ";
			cin.clear();
			getline(cin, TempStr);
		}
		Temp->NumberWay = StringToInt(TempStr);
		cin.clear();
		break;
	case '5':
		cout << "Автобус находиться в парке?  Нажмите 'Д' или 'Н'" << endl;
		Temp->Presense = GetKey(); //Присваиваем присутствие автобуса в парке
		break;
	case '0':
		return;
		break;
	}
	TempStr = CorrectObj->Name;
	cout << endl << "Вы точно хотите изменить данные о водителе " << CorrectObj->Name << "? Нажмите 'Д' или 'Н'" << endl;
	if ((Answer = GetKey()) == 'н') { //Если нет, то просто выводим сообщение, что данные не было удалены
		cout << "Отмена редактирования";
	}
	else {							  //Если пользоваетель нажал "да", 
		DeleteData(CorrectObj->Name); //сперва удаляем редактируемый объект
		PushData(&Root, NULL, *Temp); //А потом заново заносим измененный объект
		cout << endl << "Данные о " << TempStr << " успешно изменены!" << endl;
		Data_is_Saved = false;
	}
	delete Temp; // Удаляем временное хранилище
	system("cls");
	MenuAfterOutput(); //Возвращаемся в главное меню
}
