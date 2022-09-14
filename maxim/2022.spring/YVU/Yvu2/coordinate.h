#pragma once
#include "MyString.h"
#include <iostream>
using namespace std;
class coordinate : public MyString
{
private:
	//double Ox;
	//double Oy;
	double CountSqrtMod;
public:
	coordinate() : MyString() {};
	coordinate(coordinate& other) : MyString(other) {};
	/*coordinate(const char* str) : MyString(str)
	{
		
	};*/
	/*void SetOx(double startOx)
	{
		Ox = startOx;
	}//сеттер реальной части
	/void SetOy(double startOy)
	{
		Oy = startOy;
	}//сеттер мнимой части
	//double GetX()
	{
		return Ox;
	}//геттер реально части
	//double GetY()
	{
		return Oy;
	}//геттер мнимой части
	coordinate()
	{
		Ox = 1;
		Oy = 1;
	}//конструктор поумолчанию*/
	void set(const char* UserString) {
		double Ox, Oy;
		str = new char[strlen(UserString) + 1];
		length = (strlen(UserString) + 1);
		for (long unsigned int i = 0; i < length; i++) {
			str[i] = UserString[i];
		}
		str[length - 1] = '\0';
	}
	void sqrtnum()
	{
		double alfa;
		double real;
		double image;
		double argz;
		int k;
		/*///////////*/
		double Ox, Oy;
		char* NextToken = NULL;
		char* copy;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = str[i];
		}
		copy = strtok_s(Str2, "i", &NextToken);
		Ox = stoi(copy, 0, 10);
		copy = strtok_s(NULL, "i", &NextToken);
		Oy = stoi(copy, 0, 10);
		/*//////////*/
		argz = Ox + Oy;
		CountSqrtMod = sqrt(pow(Ox, 2) + pow(Oy, 2));
		alfa = atan(Oy / Ox);
		CountSqrtMod = sqrt(CountSqrtMod);
		for (k = 0; k < 2; k++)
		{
			const double PI = 3.141592653589793;
			real = (cos((alfa + 2 * PI * k) / 2));
			image = (sin((alfa + 2 * PI * k) / 2));
			cout << CountSqrtMod * real << endl;
			cout << CountSqrtMod * image << endl;
			cout << "________\n";
		}
	}
	//coordinate(const coordinate& other) : Ox(other.Ox), Oy(other.Oy) {}
	//coordinate(double X, double Y) :Ox(X), Oy(Y) {} //теперь 2 значения беру
	void createnum()
	{
		/*///////////*/
		double Ox, Oy;
		char* NextToken = NULL;
		char* copy;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = str[i];
		}
		copy = strtok_s(Str2, "i", &NextToken);
		Ox = stoi(copy, 0, 10);
		copy = strtok_s(NULL, "i", &NextToken);
		Oy = stoi(copy, 0, 10);
		/*//////////*/
		cout << Ox << "+" << Oy << "i" << endl;
	}

	double korni()
	{
		/*///////////*/
		double Ox, Oy;
		char* NextToken = NULL;
		char* copy;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = str[i];
		}
		copy = strtok_s(Str2, "i", &NextToken);
		Ox = stoi(copy, 0, 10);
		copy = strtok_s(NULL, "i", &NextToken);
		Oy = stoi(copy, 0, 10);
		/*//////////*/
		CountSqrtMod = sqrt(pow(Ox, 2) + pow(Oy, 2));
		CountSqrtMod = sqrt(CountSqrtMod);
		if (Ox < 0)
			CountSqrtMod = CountSqrtMod * (-1);//починил корень
		return CountSqrtMod;
	}
	~coordinate() {}
	bool operator>(coordinate srav1)
	{
		double h, g;
		system("CLS");
		sqrtnum();
		g = korni();
		cout << "\n"
			<< g << "\n"
			<< endl;
		srav1.sqrtnum();
		h = srav1.korni();
		cout << "\n"
			<< h << "\n"
			<< endl;
		if (g > h)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator==(coordinate srav1)//перегрузка ==
	{
		double h, g;
		system("CLS");
		sqrtnum();
		g = korni();
		cout << "\n"
			<< g << "\n"
			<< endl;
		srav1.sqrtnum();
		h = srav1.korni();
		cout << "\n"
			<< h << "\n"
			<< endl;
		if (g == h)
		{
			return true;
		}
		else
			return false;
	}
	coordinate operator + (const coordinate& other)
	{
		cout << "Вызвалась перегрузка оператора + для конкатенации строк"
			<< endl;
		coordinate result;
		delete result.str;
		result.length = length + other.length;
		result.str = new char[result.length + 1];
		strcpy(result.str, str);
		strcpy(result.str + length, other.str);
		return result;
	}
	friend ostream& operator << (ostream& out,coordinate& other)
	{
		out << other.str << endl;
		return out;
	}
	friend istream& operator >> (istream& in, coordinate& other) {
		string st;
		in >> st;
		other.set(st.c_str());
		return in;
	}
};

