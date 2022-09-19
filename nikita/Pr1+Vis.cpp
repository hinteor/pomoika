#include <stdio.h>
#include <iostream>
#include <math.h>
#include <locale.h>
#include <algorithm>

using namespace std;

class triangle
    //создаем класс треугольник
{
private:
    double a, b, c;
    //стороны треугольника
public:
    double GetA()
    {
        cout << "a = " << a << endl;
        return a;
    }
    double GetB()
    {
        cout << "b = " << b << endl;
        return b;
    }
    double GetC()
    {
        cout << "c = " << c << endl;
        return c;
    }
    void SetA(double valueA)
    {
        a = valueA;
    }
    void SetB(double valueB)
    {
        b = valueB;
    }
    void SetC(double valueC)
    {
        c = valueC;
    }
    triangle()
        //конструктор по умолчанию
    {
        a = 3;
        b = 4;
        c = 5;
        cout << "Конструктор по умолчанию" << endl;
        getchar();
    }
    triangle(double x, double y, double z)
        //конструктор с параметрами
    {
        cout << "Конструктор с параметрами" << endl;
        a = x; b = y; c = z;
        getchar();
    }
    triangle(const triangle& other)
        // конструктор копирования
    {
        a = other.a;
        b = other.b;
        c = other.c;
        cout << "Конструктор копирования" << endl;
        getchar();
    }
    int area()
        //функция находения площади треугольника
    {
        double per = (a + b + c) / 2, s = sqrt(per * (per - a) * (per - b) * (per - c));
        //формула нахождения площади
        return s;
    }
    double angleAL()
    {
        double alpha;
        alpha = acos((a * a + c * c - b * b) / (2 * a * c)) * 180 / 3.14;
        return alpha;
    }
    double angleBE()
    {
        double beta;
        beta = acos((a * a + b * b - c * c) / (2 * a * b)) * 180 / 3.14;
        return beta;
    }
    double angleGA()
    {
        double gamma;
        gamma = acos((b * b + c * c - a * a) / (2 * b * c)) * 180 / 3.14;
        return gamma;
    }
    int height()
        //функция нахождения высоты
    {
        int n;
        double per = (a + b + c) / 2, s = sqrt(per * (per - a) * (per - b) * (per - c)), h;
        cout << "\nвыберите угол для подсчета высоты:\n1. Альфа\n2. Бета\n3. Гамма\n" << endl;
        cin >> n;
        switch (n)
            //срабатывает определенный кейс в зависимости от того, какой угол мы выбрали
        {
        case 1:
            //1-ый угол
            h = 2 * s / a;
            break;
        case 2:
            //2-ой угол
            h = 2 * s / b;
            break;
        case 3:
            //3-ий угол
            h = 2 * s / c;
            break;
        default:
            //если введено некорректное число
            cout << "Неверное значение" << endl;
            break;
        }
        return h;
        //выводим значение высоты
    }
    int median()
        //функция вывода медианы
    {
        double m;
        if (a > b && a > c)
            m = sqrt(2 * c * c + 2 * b * b - a * a) / 2;
        if (b > a && b > c)
            m = sqrt(2 * c * c + 2 * a * a - b * b) / 2;
        if (c > a && c > b)
            m = sqrt(2 * a * a + 2 * b * b - c * c) / 2;
        else
            m = sqrt(2 * c * c + 2 * b * b - a * a) / 2;
        return m;
        //вывоим значения медианы
    }
    friend istream& operator >> (istream& input, triangle& triangleZ)
        //перегрузка оператора cin
    {
        double arr[3];
        cout << "Перегрузка cin" << endl;
        cout << "Сторона a" << endl;
        cin >> arr[0];
        cout << "Сторна b" << endl;
        cin >> arr[1];
        cout << "Сторона c" << endl;
        cin >> arr[2];
        sort(arr, arr + 3);
        triangleZ.a = arr[0];
        triangleZ.b = arr[1];
        triangleZ.c = arr[2];
        //передача аргументов
        getchar(); getchar();
        return cin;
    }
    friend ostream& operator << (ostream& output, triangle& triangleZ)
        //перегрузка cout
    {
        cout << "Перегрузка cout" << endl;
        cout << "a = " << triangleZ.a << " b = " << triangleZ.b << " c = " << triangleZ.c << endl;
        //получение аргументов
        getchar(); getchar();
        return cout;
    }
    friend int operator^ (triangle& tA, triangle& tB)
        //перегрузка операции ^ для обозначения операции определения подобия двух треугольников
    {
        return (tA.a / tB.a == tA.b / tB.b && tA.b / tB.b == tA.c / tB.c);
    }

    ~triangle()
        //деструктор
    {
        cout << "Деструктор" << endl;
        getchar();
    }
};


int main()
{
    setlocale(LC_ALL, "Russian");
    int menu;
    int k;
    double a1 = 3, b1 = 4, c1 = 5, pl, med, hei, aA, aB, aG;
    triangle triangleA(a1, b1, c1);
    triangle triangleB;
    triangle triangleCpy(triangleB);
    do
    {
        system("CLS");
        cout << "1:Вычисление площади треугольника А" << endl;
        cout << "2:Вычисление углов треугольника А" << endl;
        cout << "3:Вычисление высоты треугольника А" << endl;
        cout << "4:Вычисление медианы треугольника Б" << endl;
        cout << "5:Показать стороны треугольника А" << endl;
        cout << "6:Показать стороны треугольника Б (Get)" << endl;
        cout << "7:Изменить стороны треугольника А" << endl;
        cout << "8:Изменить стороны треугольника Б (Set)" << endl;
        cout << "9:Сравнить треугольники" << endl;
        cout << "0:Выход" << endl;
        cin >> menu;
        switch (menu)
        {
        case 1:
        {
            pl = triangleA.area();
            cout << "Площадь: " << pl << endl;
            getchar(); getchar();
            break;
        }
        case 2:
            aA = triangleA.angleAL();
            aB = triangleA.angleBE();
            aG = triangleA.angleGA();
            cout << "Углы:\n   Альфа: " << aA << "\n   Бета: " << aB << "\n   Гамма: " << aG << endl;
            getchar(); getchar();
            break;
        case 3:
            hei = triangleA.height();
            cout << "Высота: " << hei << endl;
            getchar(); getchar();
            break;
        case 4:
            med = triangleA.median();
            cout << "Медиана: " << med << endl;
            getchar(); getchar();
            break;
        case 5:
            cout << triangleA;
            break;
        case 6:
            cout << "Геттер" << endl;
            triangleB.GetA();
            triangleB.GetB();
            triangleB.GetC();
            getchar(); getchar();
            break;
        case 7:
            cin >> triangleA;
            break;
        case 8:
            double arrs[3];
            cout << "Сеттер" << endl;
            cout << "Сторона a" << endl;
            cin >> arrs[0];
            cout << "Сторна b" << endl;
            cin >> arrs[1];
            cout << "Сторона c" << endl;
            cin >> arrs[2];
            sort(arrs, arrs + 3);
            triangleB.SetA(arrs[0]);
            triangleB.SetB(arrs[1]);
            triangleB.SetC(arrs[2]);
            break;
        case 9:
        {
            k = triangleA ^ triangleB;
            if (k)
                cout << "треугольники А и Б подобны" << endl;
            else
                cout << "треуголькик А и Б отличны" << endl;
            getchar(); getchar();
        }
        }
    } while (menu != 0);
    return 0;
}