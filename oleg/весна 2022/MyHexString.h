#pragma once
#include <string>
using namespace std;
#include "MyString.h"
class MyHexString :
	public MyString
{
public:
	MyHexString() :MyString() {};
	MyHexString(MyHexString& other) :MyString(other) {};
	MyHexString(const char* str) :MyString(Str) {
		bool error = false;
		for (long unsigned int i = 0; i < length; i++)
		{
			if (i == 0 && Str[i] == '+')
			{
				break;
			}
			if (i == 0 && Str[i] == '-') {
				break;
			}
			switch (Str[i]) {
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;
			case '6':
				break;
			case '7':
				break;
			case '8':
				break;
			case '9':
				break;
			case '0':
				break;
			case 'a':
				break;
			case 'b':
				break;
			case 'c':
				break;
			case 'd':
				break;
			case 'f':
				break;
			case 'A':
				break;
			case 'B':
				break;
			case 'C':
				break;
			case 'D':
				break;
			case 'F':
				break;
			default:
				error = true;
				break;
			}
		}
		if (error) {
			SetEmptyString();
			cout << "В строке встречен символ отличный от 16 ричной цыфр и + или - в начале ! Зануление строки !" << endl;
		}
	}
	void SetLowerCase() override
	{
		cout << "Вызвался метод перевода в нижний регистр" << endl;
		for (unsigned int i = 0; i < this->length; i++)
			if (Str[i] >= 65 && Str[i] <= 90)
				Str[i] += 32;
	}
	bool CanBeConverted() {
		long int LongT;
		int T;
		LongT = stoi(Str, 0, 16);
		T = LongT;
		if (T == LongT) {
			return true;
		}
		else
		{
			return false;
		}
	}

	bool operator > (const MyHexString& other) {
		long int Size;
		long int OtherSize;
		Size = stoi(Str, 0, 16);
		OtherSize = stoi(other.Str, 0, 16);
		if (Size > OtherSize) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator >= (const MyHexString& other) {
		long int Size;
		long int OtherSize;
		Size = stoi(Str, 0, 16);
		OtherSize = stoi(other.Str, 0, 16);
		if (Size >= OtherSize) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator < (const MyHexString& other) {
		long int Size;
		long int OtherSize;
		Size = stoi(Str, 0, 16);
		OtherSize = stoi(other.Str, 0, 16);
		if (Size < OtherSize) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator <= (const MyHexString& other) {
		long int Size;
		long int OtherSize;
		Size = stoi(Str, 0, 16);
		OtherSize = stoi(other.Str, 0, 16);
		if (Size <= OtherSize) {
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator == (const MyHexString& other) {
		long int Size;
		long int OtherSize;
		Size = stoi(Str, 0, 16);
		OtherSize = stoi(other.Str, 0, 16);
		if (Size == OtherSize) {
			return true;
		}
		else
		{
			return false;
		}
	}

	void Print()
	{
		cout << Str << endl;
	}
	void set(const char* UserString) {
		Str = new char[strlen(UserString) + 1];
		length = (strlen(UserString) + 1);
		for (long unsigned int i = 0; i < length; i++) {
			Str[i] = UserString[i];
		}
		Str[length - 1] = '\0';
		bool error = false;
		for (long unsigned int i = 0; i < length - 1; i++)
		{
			if (i == 0 && Str[i] == '+')
			{
				break;
			}
			if (i == 0 && Str[i] == '-') {
				break;
			}
			switch (Str[i]) {
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;
			case '6':
				break;
			case '7':
				break;
			case '8':
				break;
			case '9':
				break;
			case '0':
				break;
			case 'a':
				break;
			case 'b':
				break;
			case 'c':
				break;
			case 'd':
				break;
			case 'f':
				break;
			case 'A':
				break;
			case 'B':
				break;
			case 'C':
				break;
			case 'D':
				break;
			case 'F':
				break;
			default:
				error = true;
				break;
			}
		}
		if (error) {
			SetEmptyString();
			cout << "В строке встречен символ отличный от 16 ричной цыфр и + или - в начале ! Зануление строки !" << endl;
		}
	}

	friend ostream& operator << (ostream& out, MyHexString& other)
	{
		out << other.Str << endl;
		return out;
	}
	friend istream& operator >> (istream& in, MyHexString& other) {
		string st;
		in >> st;
		other.set(st.c_str());
		return in;
	}
};