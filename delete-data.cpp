#include "header.h"

void DeleteDataMain() {
	system("cls");
	cout << endl << "\t\t\t\t\t\tУДАЛЕНИЕ ДАННЫХ" << endl << endl;
	HeadTable();
	DataAvailibility();
	PrintTree(Root);
	cout << endl << "Введите ФИО для удаления или введите 0, чтобы вернуться назад: ";
	string SearchStr;
	cin.clear();
	getline(cin, SearchStr);
	if (SearchStr[0] == '0') {
		return;
	}
	while (SearchStr[0] == '\0') {
		cout << endl << "Нет данных для считывания! Введите данные!" << endl;
		cout << "Введите ФИО для удаления: ";
		cin.clear();
		getline(cin, SearchStr);
	}
	while (!SearchName(Root, SearchStr)) {
		cout << "Объект " << SearchStr << " отсутствует в базе данных!" << endl;
		cout << "Повторить поиск? Нажмите 'Д' или 'Н'" << endl;
		char Answer = GetKey();
		if (Answer == 'н')
			MainMenu();
		else {
			cout << endl << "Введите ФИО для удаления: ";
			cin.clear();
			getline(cin, SearchStr);
		}
	}
	cout << "Вы точно хотите удалить объект " << SearchStr << "? Нажмите 'Д' или 'Н'" << endl;
	cin.clear();
	char Answer = GetKey();
	if (Answer == 'н') {
		cout << endl << "Отмена удаления!" << endl;
		Sleep(900);
		MainMenu();
	}
	else {
		if (DeleteData(SearchStr)) {
			Data_is_Saved = false;
			if (Root == NULL) {
				cout << endl << "Данные успешно удалены!" << endl;
				cout << endl << endl << "\tВ БАЗЕ НЕТ ДАННЫХ! ПОВТОРИТЕ ПОПЫТКУ ПОЗЖЕ!" << endl << endl;
				system("cls");
				MenuAfterOutput();
			}
			else {
				system("cls");
				cout << endl << "\t\t\t\t\t\tУДАЛЕНИЕ ДАННЫХ" << endl << endl;
				HeadTable();
				PrintTree(Root);
				cout << endl << "Данные успешно удалены!" << endl;
				cout << "Хотите еще удалить элемент? Нажмите Д или Н" << endl;
				cin.clear();
				char Answer = GetKey();
				if (Answer == 'н')
					MenuAfterOutput();
				else DeleteDataMain();
			}
		}
	}
}

int DeleteData(string Search) {
	AUTOPARK_Tree** NeededElem = new AUTOPARK_Tree*;
	*NeededElem = SearchName(Root, Search);
	
	//Если указатель на найденый адрес памяти равен нуль, значит элемент найти не удалось,
	//поэтому возвращаем 0
	if (*NeededElem == NULL)
		return 0;
	//У найденого элемента нет потомков - Самый простой случай.
	if ((*NeededElem)->Right == NULL && (*NeededElem)->Left == NULL) {
		if ((*NeededElem) == Root) {
			Root = NULL;
		}
		else if ((*NeededElem)->Parent->Right == (*NeededElem)) {//Выясняем каким потомком - правым или левым, является найденый элемент
			(*NeededElem)->Parent->Right = NULL; //Говорим родителю, что теперь у него нет потомка.
		}
		else (*NeededElem)->Parent->Left = NULL; //Говорим родителю, что теперь у него нет потомка.
	}

	//У найденого элемента есть правый потомок
	else if ((*NeededElem)->Left == NULL) {
		if ((*NeededElem) == Root) {
			Root = Root->Right;
		}
		else {
			if ((*NeededElem)->Parent->Right == (*NeededElem)) { //Выясняем каким потомком - правым или левым, является найденый элемент
				(*NeededElem)->Right->Parent = (*NeededElem)->Parent; //Говорим потомку найденого элемента, что теперь его родитель - это родитель найденого элемента.
				(*NeededElem)->Parent->Right = (*NeededElem)->Right; //Говорим родителю, что теперь его потомок, это потомок потомка элемента
			}
			else {
				(*NeededElem)->Right->Parent = (*NeededElem)->Parent;
				(*NeededElem)->Parent->Left = (*NeededElem)->Right;
			}
		}
	}

	//У найденого элемента есть левый потомок
	else if ((*NeededElem)->Right == NULL) {
		if ((*NeededElem) == Root) {
			Root = Root->Left;
		}
		else {
			if ((*NeededElem)->Parent->Right == (*NeededElem)) {  //Выясняем каким потомком - правым или левым, является найденый элемент
				(*NeededElem)->Parent->Right = (*NeededElem)->Left; //Говорим родителю, что теперь его потомок, это потомок потомка элемента
				(*NeededElem)->Left->Parent = (*NeededElem)->Parent; //Говорим потомку найденого элемента, что теперь его родитель - это родитель найденого элемента.
			}
			else {
				(*NeededElem)->Parent->Left = (*NeededElem)->Left;  //Говорим родителю, что теперь его потомок, это потомок потомка элемента
				(*NeededElem)->Left->Parent = (*NeededElem)->Parent;  //Говорим потомку найденого элемента, что теперь его родитель - это родитель найденого элемента
			}
		}
	}

	//Самый сложный случай. У найденого элемента 2 потомка.
	else {
		AUTOPARK_Tree* MinRightElem = (*NeededElem)->Right; //Объявляем указатель на минимальный элемент правого поддерева
		while (MinRightElem->Left) {
			MinRightElem = MinRightElem->Left; //Ищем этот самый минимальный элемент
		}
		if (!MinRightElem->Right) { //Если у мин.элемента нет правого потомка
			if ((*NeededElem) == Root) {  // Если удаляемый элемент - корень дерева
				if (MinRightElem == (*NeededElem)->Right) { // Если минимальный элемент правого поддерева, это правый ребенок удаляемого элемента
					Root->Left->Parent = MinRightElem;  //Говорим потомку удаляемого элемента, что его родитель - это только что найденный мин.элемент
					MinRightElem->Left = Root->Left; //Делаем мин.эл-нт нашим корнем. Говорим, что левый потомок мин.эл-та, это левый потомок удаляемого элемента
					MinRightElem->Right = NULL;  //Говорим, что у нового корня нет правых детей, так как был новый элемен был единственным потомком
					MinRightElem->Parent = NULL; //Говорим, что родителя у него нет
					Root = MinRightElem; //И присваиваем указателю на корень адрес нового элемента
				}
				else { //Если мин.элемент не является правым потомком удаляемого элемента
					Root->Left->Parent = MinRightElem; //Говорим левому ребенку удаляемого элемента что его родитель - это мин.элемент, правого поддерева 
					Root->Right->Parent = MinRightElem;//Говорим правому ребенку удаляемого элемента что его родитель - это мин.элемент, правого поддерева 
					//Говорим родителю мин.элемента, что теперь у него нет потомка
					MinRightElem->Parent->Left = NULL; 
					//Сообщаем мин.элменту адреса его новых детей
					MinRightElem->Left = Root->Left; 
					MinRightElem->Right = Root->Right;
					//Говорим мин.элементу, что у него нет родителей
					MinRightElem->Parent = NULL; 
					//Присваиваем указателю на корень дерева новый адрес
					Root = MinRightElem; 
				}
			}
			else { //Если удаляемый элемент не корень, и мин.элемента правого поддерева нет правого потомка
				if (MinRightElem == (*NeededElem)->Right) {
					//Говорим потомку удаляемого элемента, что его родитель - это только что найденный мин.элемент
					(*NeededElem)->Left->Parent = MinRightElem; 
					//Говорим, что левый потомок мин.эл-та, это левый потомок удаляемого элемента
					MinRightElem->Left = (*NeededElem)->Left; 
					//Говорим, что правых потомков у мин.элемента теперь нет
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
					MinRightElem->Parent->Left = NULL; //Говорим родителю минимального элемента, что у него теперь нет потомка
					//Говорим левому потомку удаляемого элемента адрес нового родителя
					(*NeededElem)->Left->Parent = MinRightElem; 
					//Говорим правому потомку удаляемого элемента адрес нового родителя
					(*NeededElem)->Right->Parent = MinRightElem; 
					//Присваиваем мин.элементу адреса его новых потомков
					MinRightElem->Left = (*NeededElem)->Left; 
					MinRightElem->Right = (*NeededElem)->Right; 
					//Говрим мин.элементу адрес его нового родителя
					MinRightElem->Parent = (*NeededElem)->Parent; 

					if ((*NeededElem)->Parent->Right == (*NeededElem)) {
						//Если удаляемый элемент - правый потомок, то говорим родителю, что его правый потомок, это теперь мин.элемент
						(*NeededElem)->Parent->Right = MinRightElem;  
					}
					else {
						//Если удаляемый элемент - левый потомок, то говорим родителю, что его левый  потомок, это теперь мин.элемент
						(*NeededElem)->Parent->Left = MinRightElem; 
					}
				}
			}
		}
		else {  //Если у мин элменета есть правый потомок
			if ((*NeededElem) == Root) { // Если удаляемый элемент - это корень всего дерева
				if (MinRightElem == (*NeededElem)->Right) { // Если мин.элемент правого поддерева, это правый потомок, удаляемого элемента.
					//Сообщаем мин.элементу его адреса новых потомков
					MinRightElem->Left = Root->Left; 
					 //Говорим, мин.элементу что у него нет родителя
					MinRightElem->Parent = NULL;
					 //Связываем левый элемент с новым корнем
					Root->Left->Parent = MinRightElem;
					//Присваиваем указателю не корень дерева новый адрес
					Root = MinRightElem; 
				}
				else { //Если мин.элемент правого поддерева, не является правым потомком, удаляемого элемента.
					//Связываем правого потомка мин.элемента с родителем этого мин.элемента
					MinRightElem->Right->Parent = MinRightElem->Parent; 
					//Связываем родителя мин.элемента с правым потомком этого мин.элемента
					MinRightElem->Parent->Left = MinRightElem->Right; 
					//Сообщаем мин.элементу адреса его новых потомков
					MinRightElem->Left = Root->Left;
					MinRightElem->Right = Root->Right;
					//Говорим, что родителя у него нет
					MinRightElem->Parent = NULL;
					//Связываем потомков корня дерева с новым элементом
					Root->Left->Parent = MinRightElem;
					Root->Right->Parent = MinRightElem;
					//Присваиваем указателю не корень дерева новый адрес
					Root = MinRightElem;
				}
			}
			else {
				//По аналогии с предыдущим случаем делаем почти все тоже самое
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
	//Удаляем нужный элемент
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