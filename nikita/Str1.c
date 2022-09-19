//C:\Users\Public\Progs\Progs\Str1\List.txt
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct cntry
{
       char country[30];
       char tovar[30];
       int k;
};

typedef struct cntry DataType;

struct node
{
       DataType data;
       struct node * next;
};

typedef struct node * list;

DataType input_country (void);
list read_file (char * filename);
list new_node (list, DataType);
int write_file (char * filename, list);
void delete_list (list);
void show (list);
void search (list begin);
list delete_node (list);

int main (void)
{
    setlocale (LC_ALL, "Russian");
    char file[50];
    char menu;
    list countries = NULL;
    puts ("Введите имя файла");
    gets (file);
    countries = read_file (file);
//данные из файла считываются в список, на экран выводится меню с допустимыми над списком действиями
    do
    {
       system ("CLS");
       puts ("1. Добавить запись");
       puts ("2. Просмотр записи");
       puts ("3. Поиск стран, в которые экспортируется данный товар");
       puts ("4. Удаление");
       puts ("5. Выйти");
       menu = getchar();
       getchar();
       switch (menu)
       {
              case '1': countries = new_node (countries, input_country());
              break;
              case '2': show (countries);
              break;
              case '3': search (countries);
              break;
              case '4': countries = delete_node (countries);
       }
    }
    while (menu!='5');
    if (write_file (file, countries))
        puts ("Файл сохранен");
//при выходе файл перезаписывается
    else
    	puts ("Файл не сохранен");
//иначе - соответствующее сообщение
    delete_list (countries);
//созданный в процессе работы список удаляется
    return 0;
}

DataType input_country (void)
{
//заполнение данных для новой записи
    DataType country;
    puts ("Страна");
    gets (country.country);
    puts ("Товар");
    gets (country.tovar);
    puts ("Кол-во экспортируемых товаров");
    scanf ("%d", &country.k);
	getchar();
    return country;
}

list new_node (list begin, DataType cntry)
{
//создание новой записи
    list temp = (list) malloc (sizeof(struct node));
//выделение памяти под новый узел списка во временную переменную
    temp->data = cntry;
//данные о новом элементе сохраняются в поле данных нового узла
    temp->next = begin;
//"связка" с уже существующим спском
    return temp;
}

list read_file (char * filename)
{
//функция считывания данных из файла в список
    FILE * f;
    DataType country;
    list begin = NULL, cur;
    if ((f = fopen (filename, "rb")) == NULL)
    {
        perror ("Ошибка открытия файла");
        getchar();
        return begin;
    }
    if (fread(&country, sizeof(country), 1, f))
        begin = new_node (NULL, country);
//если файл не пустой, создается первый узел списка
    else
        return NULL;
//иначе возвращается нулевое значение
    cur = begin;
    while (fread(&country, sizeof(country), 1, f))
    {
        cur->next = new_node (NULL, country);
//до тех пор, пока файл не пустой, создаются новые узлы списка
        cur = cur->next;
//создается "связка"
	}
    fclose(f);
    return begin;
//возвращается заполненный список
}

void delete_list (list begin)
{
//удаление списка
    list temp = begin;
    while (temp)
    {
        begin = temp->next;
//узлы списка удаляются последовательно
        free (temp);
        temp = begin;
    }
}

int write_file (char * filename, list begin)
{
//запись списка в файл
    FILE * f;
    if ((f = fopen (filename, "wb")) == NULL)
    {
        perror ("Ошибка создания файла");
        getchar();
        return 0;
    }
    while (begin)
    {
        if (fwrite (&begin->data, sizeof(DataType), 1, f))
            begin = begin->next;
//до тех пор, пока есть, что записывать, данные из элементов списка переносятся в файл
        else
        	return 0;
    }
    return 1;
}

void print_data (struct cntry cntry)
{
    printf ("Страна : %s\nТовар : %s\nКол-во : %d\n",
            cntry.country, cntry.tovar, cntry.k);
}

void show (list cur)
{
//функция вывода информации
     int k = 0;
     system ("CLS");
     if (cur == NULL)
     {
//если список пустой, выводится соответствующее сообщение
          puts ("Список пуст");
          getchar();
          return;
     }
     puts ("|  N |          Страна                 |    Товар   |   Кол-во   |");
     puts ("------------------------------------------------------------------");
     while (cur)
     {
        printf ("|%3d | %-31s |%11s |%11d |\n", ++k,
                 cur->data.country, cur->data.tovar, cur->data.k);
        cur = cur->next;
     }
     puts ("------------------------------------------------------------------");
     getchar();
}

void search (list cur)
{
//поиск необходимой записи
     char tovar [20];
     int k = 0;
     DataType country;
     system ("CLS");
     if (cur == NULL)
//если список пуст выводится соответствующее сообщение
     {
	    puts ("Список пуст");
	    getchar();
	    return;
     }
     puts ("Какой товар интересует?");
     scanf ("%s", &tovar);
     getchar();
     while (cur)
//до тех пор пока в списке есть элементы идет поиск
     {
        if (strcmp (cur->data.tovar, tovar) == 0)
        {
           k++;
           country = cur->data;
           print_data (country);
           printf ("\n");
//удовлетворяющая условия запись выводится на экран
        }
        cur = cur->next;
     }
     if (k == 0)
     {
         printf ("Товар не найден");
//если таких записей нет выводится соответствующее сообщение
     }
     getchar();
 }

list delete_node (list begin) /*удаление первого элемента*/
{
     struct node * temp;
     if (begin) /*если список не пуст*/
     {
           temp = begin;
           begin = begin->next; /*переставляем указатель на следующий элемент*/
           free (temp); /*первый удаляем*/
           puts ("Удалено");
           getchar();
     }
     return begin;
}
