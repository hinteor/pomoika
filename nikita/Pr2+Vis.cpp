#include <stdio.h>
#include <iostream>
#include <locale.h>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <math.h>
using namespace std;

class String // класс строка
{
public:
    char* s; //поле строка
    int n; //поле длина строки
    String()
    {
        //    cout << "Constructor" << endl;
    } //конструктор поумолчанию
    String(char* str) //конструктор с параметром си-строка
    {
        n = strlen(str);
        s = new char[n + 1];
        for (int i = 0; i < n; i++)
            s[i] = str[i];
        s[n] = '\0';
        //    cout << "Constructor with parameters" << endl;
    }
    String(char symbol) //конструктор с параметром символ
    {
        s = new char[2];
        s[0] = symbol;
        s[1] = '\0';
        n = 1;
        //    cout << "Constructor with parameter - symbol" << endl;
    }
    String(const String& str) //конструктор копирования
    {
        s = str.s;
        n = str.n;
        //    cout << "Constructor copy" << endl;
    }
    String& operator= (String s1) //перегрузка оператора присвоения
    {
        s = s1.s;
        n = s1.n;
        return *this;
        cout << "Перегразка оператора = " << endl;
    }
    int GetLength(String s1) //метод получения длины строки
    {
        cout << "Метод получения длины строки:" << endl;
        return s1.n;
    }
    ~String()
    {
        //     cout << "Destructor" << endl;
    } //деструктор
};

bool isId(char* str) //функция для определения является ли строка строкой-идентификатором
{
    const int n = 32;
    char keywords[][n] = { "auto", "break", "case","char","const", "continue", "default", "do",
            "double", "else", "enum", "extern", "float", "for", "goto", "if", "int", "long",
            "register", "return", "short", "signed", "sizeof", "static", "struct", "switch",
            "typedef", "union", "unsigned","void", "volatile", "while" };
    if (isdigit(*str)) //проверка на наличие цифры в начале строки
    {
        cout << "Строка не является индентификаторм" << endl;
        return false;
    }
    for (int i = 0; i < n; i++) //проверка на наличие ключевых слов
    {
        if (!strcmp(str, *(keywords + i)))
        {
            cout << "Строка не является индентификаторм" << endl;
            return false;
        }
    }
    while (isalnum(*str) || *str == '_') str++; //проверка являются ли все символы строки буквами, цифрами или нижними подчеркиваниями
    if (!str[0])
    {
        cout << "Строка является индентификаторм" << endl;
        return true;
    }
    else
    {
        cout << "Строка не является индентификаторм" << endl;
        return false;
    }
}

class IdString : public String //класс-наследник строка-идентификатор
{
public:
    IdString()
    {
        //    cout << "Constructor" << endl;
    }
    IdString(char* str)
    {
        if (isId(str))
        {
            n = strlen(str);
            s = new char[n + 1];
            for (int i = 0; i < n; i++)
                s[i] = str[i];
            s[n] = '\0';
        }
        else
        {
            s = new char[2];
            s[0] = '0';
            s[1] = '\0';
            n = 0;
        }
    }
    char operator[] (int i) //перегрузка оператора индексации (возвращает указанный символ)
    {
        return *(s + i);
    };
    void FirstOcc(const IdString ids, const char c) //метод поиска первого вхождения символа в строку
    {
        cout << "Метод поиска первого вхождения символа в строку:" << endl;
        int i = 0;
        while (*(ids.s + i) != '\0')
        {
            if (*(ids.s + i) == c)
            {
                cout << "Первое вхождение символа " << c << ": элемент " << i + 1 << endl;
                return;
            }
            i++;
        }
        cout << "Такого символа нет" << endl;
    }
    IdString(IdString const& str)
    {
        s = str.s;
        n = str.n;
    }
    IdString& operator= (const IdString& s1)
    {
        String::operator=(s1);
        return *this;
    }
    ~IdString()
    {
    }
    friend IdString operator- (const IdString ids1, const IdString ids2)
    {
        cout << "Перегрузка операции - " << endl;
        IdString ids3;
        char* s3;
        int k, i, j, n;
        for (k = 0; *(ids2.s + k) != '\0'; k++)
        {
            for (i = j = 0; *(ids1.s + i) != '\0'; i++)
                if (*(ids1.s + i) != *(ids2.s + k))
                    *(ids1.s + j++) = *(ids1.s + i);
            *(ids1.s + j) = '\0';
        }
        n = strlen(ids1.s);
        s3 = new char[n + 1];
        for (i = 0; i < n; i++)
            s3[i] = ids1.s[i];
        s3[n] = '\0';
        ids3.s = s3;
        ids3.n = n;
        return ids3;
    }
};


bool isBy(char* str) //дружественная функция для определения является ли строка бинарной
{
    while (*str == '1' || *str == '0') str++;
    if (!str[0])
    {
        cout << "Строка является бинароной" << endl;
        return true;
    }
    else
    {
        cout << "Строка не является бинароной" << endl;
        return false;
    }
}

class BiString : public String //класс-наследник бинарная строка
{
public:
    BiString()
    {
    }
    BiString(char* str)
    {
        bool k;
        if (k = isBy(str))
        {
            n = strlen(str);
            s = new char[n + 1];
            for (int i = 0; i < n; i++)
                s[i] = str[i];
            s[n] = '\0';
        }
        else
        {
            s = new char[2];
            s[0] = '0';
            s[1] = '\0';
            n = 0;
        }
    }
    void WhichSign(const BiString str) //метод определения знака хранимого в строке числа
    {
        if (*(str.s) == '0')
            cout << "Число положительно" << endl;
        else
            cout << "Число отрицательно" << endl;
    }
    BiString& operator= (const BiString& s1)
    {
        String::operator=(s1);
        return *this;
    }
    BiString(BiString const& str)
    {
        s = str.s;
        n = str.n;
    }
    ~BiString()
    {
    }
    friend BiString operator+ (const BiString bs1, const BiString bs2) //перегрузка оператора сложения (не учитывает знак)
    {
        cout << "Перегрузка операции + без учитывания знака" << endl;
        int i, num1, num2, sum, rem, n3;
        char* str;
        BiString bs3;
        if (bs1.n > bs2.n)
            bs3.n = bs1.n;
        else
            bs3.n = bs2.n;
        n3 = bs3.n;
        num1 = strtol(bs1.s, NULL, 2);
        num2 = strtol(bs2.s, NULL, 2);
        sum = num1 + num2;
        str = new char[n3 + 2];
        if (sum >= pow(2, n3))
            *(str + bs3.n + 1) = '\0';
        else
        {
            *(str + bs3.n) = '\0';
            n3--;
        }
        for (i = n3; i >= 0; i--)
        {
            rem = sum % 2;
            *(str + i) = rem + '0';
            sum /= 2;
        }
        bs3.s = str;
        return bs3;
    }
    friend BiString operator- (const BiString bs1, const BiString bs2) //перегрузка оператора вычитания (не учитывает знак)
    {
        cout << "Перегрузка операции - без учитывания знака" << endl;
        int i, num1, num2, sub, rem, n3;
        char* str;
        BiString bs3;
        if (bs1.n > bs2.n)
            bs3.n = bs1.n;
        else
            bs3.n = bs2.n;
        n3 = bs3.n;
        num1 = strtol(bs1.s, NULL, 2);
        num2 = strtol(bs2.s, NULL, 2);
        sub = num1 - num2;
        str = new char[n3 + 1];
        if (sub <= pow(2, n3))
            *(str + bs3.n) = '\0';
        else
        {
            *(str + (bs3.n - 1)) = '\0';
            n3--;
        }
        for (i = n3 - 1; i >= 0; i--)
        {
            rem = sub % 2;
            *(str + i) = rem + '0';
            sub /= 2;
        }
        *(str + bs3.n) = '\0';
        bs3.s = str;
        return bs3;
    }
};

char* GetString(char* s) //функция ввода строки с клавиатуры
{
    fgets(s, 100, stdin);
    s[strcspn(s, "\n")] = 0;
    fflush(stdin);
    return s;
}

int main()

{
    int n = 0, menu, men, me; char* s; char c;
    setlocale(LC_ALL, "Russian");
    s = new char[100];
    do 
    {
        system("CLS");
        cout << "1:Строка" << endl;
        cout << "2:Строка-индетификатор" << endl;
        cout << "3:Бинарная строка" << endl;
        cout << "0.Выход" << endl;
        cin >> menu;
        cin.get();
        switch (menu)
        {
        case 1:
        {
            bool flag;
            puts("Введите строку: ");
            s = GetString(s);
            String str(s); //создание объекта класса строка
            puts("Провести определение длины строки?");
            puts("1/0");
            cin >> flag;
            if (flag)
            {
                n = str.GetLength(str); //проверка метода определения длины строки
                cout << n << endl;
                cin.get(); getchar();
            }
            break;
        }
        case 2:
        {
            do
            {
                system("CLS");
                cout << "1:Проверка метода поиска первого вхождения символа в строку" << endl;
                cout << "2:Проверка перегруженного оператора вычитания" << endl;
                cout << "0:Пропуск" << endl;
                cin >> men;
                cin.get();
                switch (men)
                {
                case 1:
                {
                    puts("Введите строку-индетификатор: ");
                    s = GetString(s);
                    IdString id1(s); //создание объекта класса строка-идентификатор
                    puts("Введите символ: ");
                    cin >> c;
                    fflush(stdin);
                    id1.FirstOcc(id1, c); //проверка метода поиска первого вхождения символа в строку
                    cin.get(); getchar();
                    break;
                }
                case 2:
                    puts("Введите 1-ую строку-индетификатор: ");
                    s = GetString(s);
                    IdString id1(s); //создание объекта класса строка-идентификатор                
                    puts("Введите 2-ую строку-индетификатор: ");
                    s = GetString(s);
                    IdString id2(s); //создание второго объекта класса строка-идентификатор
                    puts("1-ая строка индетификатор - 2-ая строка идентификатор = ");
                    IdString id3;
                    id3 = id1 - id2; //проверка перегруженного оператора вычитания
                    puts(id3.s);
                    cin.get(); getchar();
                    break;
                }

            } while (men != 0);
            break;
        }
        case 3:
        {          
            do
            {
                system("CLS");
                cout << "1: Определение знака у двоичного числа" << endl;
                cout << "2: Проверка перегруженного оператора вычитания" << endl;
                cout << "3: Проверка перегруженного оператора сложения" << endl;
                cout << "0: Пропуск" << endl;
                cin >> me;
                cin.get();
                switch (me)
                {
                case 1:
                {
                    puts("Введите бинарную строку ");
                    s = GetString(s);
                    BiString bi1(s); //создание объекта класса бинарная строка
                    bi1.WhichSign(bi1); //проверка метода определения знака у двоичного числа
                    cin.get(); getchar();
                    break;
                }
                case 2:
                {
                    puts("Введите 1-ую бинарную строку ");
                    s = GetString(s);
                    BiString bi1(s); //создание объекта класса бинарная строка
                    puts("Введите 2-ую бинарную строку: ");
                    s = GetString(s);
                    BiString bi2(s); //создание второго объекта класса бинарная строка
                    puts("1-ая бинарная строка - 2-ая бинарная строка = ");
                    BiString bi3;
                    bi3 = bi1 - bi2; //проверка перегруженного оператора вычитания
                    puts(bi3.s);
                    cin.get(); getchar();
                    break;
                }
                case 3:
                    puts("Введите 1-ую бинарную строку ");
                    s = GetString(s);
                    BiString bi1(s); //создание объекта класса бинарная строка
                    puts("Введите 2-ую бинарную строку: ");
                    s = GetString(s);
                    BiString bi2(s); //создание второго объекта класса бинарная строка
                    puts("1-ая бинарная строка + 2-ая бинарная строка = ");
                    BiString bi3;
                    bi3 = bi1 + bi2; //проверка перегруженного оператора сложения
                    puts(bi3.s);
                    cin.get(); getchar();
                    break;
                }
            } while (me != 0);
            break;

        }
        }
    } while (menu != 0);
    return 0;
}
