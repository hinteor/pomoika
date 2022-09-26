#include <iostream>
#include "deque.h"
using namespace std;

void INTQ();
void Unsigned_Int();
int main()
{
	setlocale(LC_ALL, "Rus");
	char menu;
	do
	{
		system("CLS");
		fflush(stdin);
		cout << "Выберетe тип Дека:" << endl;
		cout << "1.Int" << endl;
		cout << "2.Unsigned Int" << endl;
		cout << "Q.Выход" << endl;
		cin >> menu;
		switch (menu)
		{
		case '1': INTQ(); break;
		case '2': Unsigned_Int(); break;
		}
	} while (menu != 'q' && menu != 'Q');
	return 0;
}
void INTQ()
{
	deque<int> id;
	deque<int> id2;
	char menu;
	do
	{
		system("CLS");
		fflush(stdin);
		cout << "1.Ввести очередь" << endl;
		cout << "2.Посмотреть элементы очепреди" << endl;
		cout << "3.Добавить элемент в очередь" << endl;
		cout << "4.Достать первый элемент из очерерди" << endl;
		cout << "5.Присвоить очереди значение другой очереди" << endl;
		cout << "6.Очистить очередь" << endl;
		cout << "7.Проверить не пустая ли очередь" << endl;
		cout << "8.Нормирование элементов массива вычитанием из каждого из них минимального элемента этого массива." << endl;
		cout << "Q.Вернуться назад" << endl;
		cin >> menu;
		switch (menu)
		{
		case '1':
			cin >> id;
			system("pause");
			break;
		case '2':
			cout << id;
			system("pause");
			break;
		case '3':
			cout << "Введите элемент, который хотите добавить: " << endl;
			int item;
			cin >> item;
			id.push_back(item);
			cout << id << endl;
			system("pause");
			break;
		case '4':
			cout << "1 элемент очереди: " << id.pop_back() << endl;
			cout << "Очередь стала :\n" << id << endl;
			system("pause");
			break;
		case '5':
			cout << "Введите очередь значение, которой вы хотите присвоить" << endl;
			cin >> id2;
			id = id2;
			cout << "Очередь приняла занчение\n" << id << endl;
			system("pause");
			break;
		case '6':
			id.clear();
			cout << "Очерердь очищена" << endl;
			system("pause");
			break;
		case '7':
			if (id.IsEmpty() == 1) {
				cout << "Очередь пустая" << endl;

			}
			else { cout << "Очередь не пустая" << endl; };
			system("pause");
			break;
		case '8': cout << "Очередь до: \n" << id;
			id.sort();
			cout << "Очередь после:\n" << id;
			system("pause");
			break;
		}
	} while (menu != 'q' && menu != 'Q');
}
void Unsigned_Int()
{
	deque<unsigned int> uid;
	deque<unsigned int> uid2;
	char menu;
	do
	{
		system("CLS");
		fflush(stdin);
		cout << "1.Ввести очередь" << endl;
		cout << "2.Посмотреть элементы очепреди" << endl;
		cout << "3.Добавить элемент в очередь" << endl;
		cout << "4.Достать первый элемент из очерерди" << endl;
		cout << "5.Присвоить очереди значение другой очереди" << endl;
		cout << "6.Очистить очередь" << endl;
		cout << "7.Проверить не пустая ли очередь" << endl;
		cout << "8.Нормирование элементов массива вычитанием из каждого из них минимального элемента этого массива." << endl;
		cout << "Q.Вернуться назад" << endl;
		cin >> menu;
		switch (menu)
		{
		case '1':
			cin >> uid;
			system("pause");
			break;
		case '2':
			cout << uid;
			system("pause");
			break;
		case '3':
			cout << "Введите элемент, который хотите добавить: " << endl;
			unsigned int item;
			cin >> item;
			uid.push_back(item);
			cout << uid << endl;
			system("pause");
			break;
		case '4':
			cout << "1 элемент очереди: " << uid.pop_back() << endl;
			cout << "Очередь стала :\n" << uid << endl;
			system("pause");
			break;
		case '5':
			cout << "Введите очередь значение, которой вы хотите присвоить" << endl;
			cin >> uid2;
			uid = uid2;
			cout << "Очередь приняла занчение\n" << uid << endl;
			system("pause");
			break;
		case '6':
			uid.clear(); cout << "Очерердь очищена" << endl;
			system("pause");
			break;
		case '7':
			if (uid.IsEmpty() == 1) {
				cout << "Очередь пустая" << endl;
			}
			else { cout << "Очередь не пустая" << endl; };
			system("pause");
			break;
		case '8':
			cout << "Очередь до: \n" << uid; uid.sort();
			cout << "Очередь после:\n" << uid;
			system("pause");
			break;
		}
	} while (menu != 'q' && menu != 'Q');

}
