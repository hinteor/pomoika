#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct lib
{
    char surname[20];
    char title[20];
    char publish[14];
    int year;
    char theme[20];
};

typedef struct lib DataType;

struct node
{
    DataType data;
    struct node* next;
};

typedef struct node* list;

DataType input_book(void); //прием значений в функции 
list read_file(char* filename);
list new_node(list, DataType);
int write_file(char* filename, list);
void delete_list(list);
void edit(list);
void show(list);
void search(list begin);
list delete_node(list);

int main(void)
{
    setlocale(LC_ALL, "Rus");
    char filename[50];
    int menu;
    list book = NULL;
    cout << "Введи название файла" << endl;
    cin >> filename;
    book = read_file(filename);
    do
    {
        system("CLS");
        cout << "1. Добавление записи" << endl
            << "2. Просмотр записей" << endl
            << "3. Поиск" << endl
            << "4. Удаление записи" << endl
            << "5. Выход" << endl;
        menu = getchar();
        switch (menu)
        {
        case '1' :
            book = new_node(book, input_book());
            break;
        case '2' :
            show(book);
            break;
        case '3' :
            search(book);
            break;
        case '4' :
            book = delete_node(book);
        }
    } while (menu != '5');
    if (write_file(filename, book))
        cout << "File saved" << endl;
    else
        cout << "File not saved" << endl;
    delete_list(book);
    return 0;
}
/*заполнение одной записи (ввод данных о книге)*/
DataType input_book(void)
{
    DataType book;
    cout << "Фамилия" << endl;
    cin >> book.surname;
    cout << "Название" << endl;
    cin >> book.title;
    cout << "Издательство" << endl;
    cin >> book.publish;
    cout << "Тематика" << endl;
    cin >> book.theme;
    cout << "Год издательства" << endl;
    cin >> book.year;
    cin.get();
    return book;
}

list new_node(list begin, DataType the_book)//создание узла и выделение под него памяти 
{
    list tmp = (list)malloc(sizeof(struct node));//выделение памяти под структуру узла 
    tmp->data = the_book;//указатель на последний элемент, который присоединяется с конца списка и пинимает в себя значения поезда 
    tmp->next = begin;//указатель после первого элемента который приравнивает(присоединяет) новый элемент к концу списка 
    return tmp;
}

list read_file(char* filename)//чтение из файла
{
    FILE* f;
    DataType book;
    list begin = NULL, cur;
    if ((f = fopen(filename, "rb")) == NULL)//ошибка при создании файла (если не удалось прочитать файл или он не сущ.)
    {
        cout << "Error open file" << endl;
        cin.get();
        return begin;//возврат указателя на начало списка 
    }
    if (fread(&book, sizeof(book), 1, f))//создание пустого файла 
        begin = new_node(NULL, book);//та самая функция с созданием узла (нулл для бегина)(трайн для даты) 
    else
        return NULL;
    cur = begin;
    while (fread(&book, sizeof(book), 1, f))//заполнение файла
    {
        cur->next = new_node(NULL, book);//пока файл не кончился я могу создавать новые узлы
        cur = cur->next;
    }
    fclose(f);//закрыть файл
    return begin;
}

void search(list cur)//поиск
{
    double thisyear = 2000; 
    int k = 0; //счетчик
    char author[13];
    system("CLS");
    if (cur == NULL)
    {
        cout << "List is empty" << endl;//если список пуст 
        cin.get();
        return;
    }
    cout << "Print author surname" << endl;
    cin >> author;
    cin.get();
    cout << "       Founded books" << endl
        << "---------------------------" << endl;
    while (cur)//кур это бегин (указатель на первый элемент)
    {
        k++;
        if ((strcmp(cur->data.surname, author) == 0) && (cur->data.year > thisyear))
        {
            cout << cur->data.title << endl;
        }
        cur = cur->next;//проход по списку до нула 
    }
    if (k == 0)
        cout << "Not found" << endl;//если не найдено схожих вариантов  
    getchar();
    getchar();
}

void delete_list(list begin)
{
    list tmp = begin;
    while (tmp)
    {
        begin = tmp->next;//сохранение стрелки и удаление элемента(последующая замена укзателя бегин на сл.стрелку )
        free(tmp);
        tmp = begin;
    }
}

int write_file(char* filename, list begin)
{
    FILE* f;
    if ((f = fopen(filename, "wb")) == NULL)//ошибка создания если нулл (существует такой файл или нет доступа создавать файл тут)
    {
        cout << "Error create file" << endl;
        cin.get();
        return 0;
    }
    while (begin)
    {
        if (fwrite(&begin->data, sizeof(DataType), 1, f))//пока есть что писать происходит запись элементов в список 
            begin = begin->next;
        else
            return 0;
    }
    return 1;
}

void print_data(struct lib the_book)//вывод для поиска 
{
    cout << "found train: " << endl
        << the_book.surname << " - surname" << endl
        << the_book.title << " - title" << endl
        << the_book.publish << " - publisher" << endl
        << the_book.theme << " - theme" << endl
        << the_book.year << " - year" << endl;
}

void show(list cur)//вывод таблички 
{
    int k = 0;
    system("CLS");
    if (cur == NULL)
    {
        cout << "List is empty" << endl;
        cin.get();
        return;
    }
    cout << ("| N |       Surname       |        Title       |    Publish   |       Theme       | Year |") << endl
        << ("------------------------------------------------------------------------------------------") << endl;
    while (cur)
    {
        cout
            << "|" << setw(3) << ++k
            << "|" << setw(21) << cur->data.surname
            << "|" << setw(20) << cur->data.title
            << "|" << setw(14) << cur->data.publish
            << "|" << setw(19) << cur->data.theme
            << "|" << setw(6) << cur->data.year << "|" << endl;
        cur = cur->next;//переход к сл. элементу даты 
    }
    cout << "------------------------------------------------------------------------------------------" << endl;
    cin.get();
    cin.get();
}

list delete_node(list begin) /*удаление первого элемента*/
{
    struct node* tmp;
    if (begin) //если есть первый элемент 
    {
        tmp = begin; // присвоение временной переменной значения первого элемента 
        begin = begin->next; /*переставляем указатель на следующий элемент*/
        free(tmp);          //очистить первый элемент 
        puts("Deleted");
        getchar();
    }
    return begin;//теперь первый элемент это тот что был вторым
}