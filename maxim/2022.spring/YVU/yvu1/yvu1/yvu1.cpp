#include <iostream>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>
#include <windows.h>
#include "Header.h"
using namespace std;

class list
{

public:
    void printlist()
    {
        char menu = 0;
        coordinate startnum;
        double g, h, x, y, x1, y1, real, image;
        do
        {
            system("CLS");
            cout
                << "0. Создать/редактировать начальное число" << endl << endl
                << "1. Корень комплексного числа(начального)" << endl << endl
                << "2. Сравнение двух комплексных чисел (начального и заданного)" << endl << endl
                << "3. Вычитание комплексных чисел (начального и заданного)" << endl
                << "____________________________________________________________" << endl << endl << " " << startnum.GetX() << "+" << startnum.GetY() << "i" << "   <--- введенное вами число" << endl;
            cin >> menu;
            switch (menu)
            {
            case '0':
            {
                system("CLS");

                cin >> startnum;
                cout << "press enter to return to the menu" << endl;
                cin.get();
                cin.get();
            }
            break;
            case '1':
            {
                system("CLS");
                cout << "________\n";
                startnum.sqrtnum();
                cout << startnum.korni();
                cout << "\n";
                cout << "нажмите enter чтобы вернуться в меню" << endl;
                cin.get();
                cin.get();
            }
            break;

            case '2':
            {
                coordinate secondnum;
                cin >> secondnum;
                startnum == secondnum;
            }
            break;

            case '3':
            {
                system("CLS");
                coordinate B;
                cin >> B;
                real = startnum.GetX() - B.GetX();
                image = startnum.GetY() - B.GetY();
                cout << "(" << round(real * 100) / 100 << ")"
                    << "+"
                    << "(" << round(image * 100) / 100 << "i"
                    << ")" << endl;
                cout << "нажмите enter чтобы вернуться в меню" << endl;
                cin.get();
                cin.get();
            }
            break;
            default:
                break;
            }
        } while (menu != 5);
    }
};

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    list str;
    str.printlist();
}