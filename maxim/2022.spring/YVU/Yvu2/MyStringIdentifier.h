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
			Str2[i] = str[i];
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
	MyStringIdentifier(const char* str) : MyString(str)
	{
		if (!IsKeyWord() && str[0] != '$' && str[0] != '_')
		{
			SetEmptyString();
		}
	};
	void SetLowerCase() override
	{
		cout << "Вызвался метод перевода в нижний регистр" << endl;
		for (unsigned int i = 0; i < this->length; i++)
			if (str[i] >= 65 && str[i] <= 90)
				str[i] += 32;
	}

	bool operator == (const MyStringIdentifier& other)
	{
		if (length == other.length)
		{
			for (unsigned int i = 0; i < length; i++) {
				if (str[i] != other.str[i]) {
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
				if (str[i] != other.str[i]) {
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
			return str[ind - 1];
		}
		else {
			return NULL;
			cout << "Ошибка ! Обращение к недопустимому элементу массива !" << endl;
		}
	}
	void Print()
	{
		cout << str << endl;
	}
	void set(const char* UserString) {
		str = new char[strlen(UserString) + 1];
		length = (strlen(UserString) + 1);
		for (long unsigned int i = 0; i < length; i++) {
			str[i] = UserString[i];
		}
		str[length - 1] = '\0';
		if (!IsKeyWord() && str[0] != '$' && str[0] != '_')
		{
			SetEmptyString();
		}
	}

	int FindSymbol(const char symbol) {
		char* place = strchr(str, symbol);
		if (place != NULL) {
			return place - str + 1;
		}
		else
		{
			return -1;
		}
	}

	friend ostream& operator << (ostream& out, MyStringIdentifier& other)
	{
		out << other.str << endl;
		return out;
	}
	friend istream& operator >> (istream& in, MyStringIdentifier& other) {
		string st;
		in >> st;
		other.set(st.c_str());
		return in;
	}
};

