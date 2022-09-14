#pragma once
#include <string>
#include "MyString.h"
class MyStringIdentifier :
	private MyString
{
private:
	bool IsKeyWord()
	{
		const char* key[16] = { "bool", "break", "case", "char", "class",
		"const", "continue", "default", "delete", "do", "double", "else", "enum",
		"explicit","auto","int" };
		char* NextToken = NULL;
		char* copy;
		bool ok = false;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = Str[i];
		}
		copy = strtok_s(Str2, ",", &NextToken);
		while (copy) {
			for (int i = 0; i < 16; i++) {
				if (!strcmp(copy, key[i]))
				{
					ok = true;
				}
			}
			if (!ok) {
				return false;
			}
			ok = false;
			copy = strtok_s(NULL, " ", &NextToken);
		}
		return true;
	}
public:
	MyStringIdentifier() : MyString() {};
	MyStringIdentifier(MyStringIdentifier& other) : MyString(other) {};
	MyStringIdentifier(const char* str) : MyString(Str)
	{
		if (!IsKeyWord() && Str[0] != '$' && Str[0] != '_')
		{
			SetEmptyString();
		}
	};
	void SetLowerCase() override
	{
		cout << "Вызвался метод перевода в нижний регистр" << endl;
		for (unsigned int i = 0; i < this->length; i++)
			if (Str[i] >= 65 && Str[i] <= 90)
				Str[i] += 32;
	}

	bool operator == (const MyStringIdentifier& other)
	{
		if (length == other.length)
		{
			for (unsigned int i = 0; i < length; i++) {
				if (Str[i] != other.Str[i]) {
					return false;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator != (const MyStringIdentifier& other)
	{
		if (length == other.length)
		{
			for (unsigned int i = 0; i < length; i++) {
				if (Str[i] != other.Str[i]) {
					return true;
				}
			}
			return false;
		}
		else
		{
			return true;
		}
	}
	const char operator[](unsigned int ind) {
		if (ind - 1 <= length && ind > 0) {
			return Str[ind - 1];
		}
		else {
			return NULL;
			cout << "Ошибка ! Обращение к недопустимому элементу массива !" << endl;
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
		if (!IsKeyWord() && Str[0] != '$' && Str[0] != '_')
		{
			SetEmptyString();
		}
	}

	int FindSymbol(const char symbol) {
		char* place = strchr(Str, symbol);
		if (place != NULL) {
			return place - Str + 1;
		}
		else
		{
			return -1;
		}
	}

	friend ostream& operator << (ostream& out, MyStringIdentifier& other)
	{
		out << other.Str << endl;
		return out;
	}
	friend istream& operator >> (istream& in, MyStringIdentifier& other) {
		string st;
		in >> st;
		other.set(st.c_str());
		return in;
	}
};