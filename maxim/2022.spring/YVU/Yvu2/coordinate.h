#pragma once
#include "MyString.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
class coordinate :
	public MyString
{
private:
	double CountSqrtMod;
public:
	coordinate() :MyString() {};
	coordinate(coordinate& other) :MyString(other) {};
	coordinate(const char* str) :MyString(Str) {
		bool eror = false;
		double Ox = NULL, Oy = NULL;
		char* NextToken = NULL;
		char* copy = NULL;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = Str[i];
		}
		copy = strtok_s(Str2, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Ox = stoi(copy, 0, 10);
		if (Ox == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		copy = strtok_s(NULL, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Oy = stoi(copy, 0, 10);
		if (Oy == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		if (eror) {
			SetEmptyString();
		}
	}

	void set(const char* UserString) {
		double Ox, Oy;
		Str = new char[strlen(UserString) + 1];
		length = (strlen(UserString) + 1);
		for (long unsigned int i = 0; i < length; i++) {
			Str[i] = UserString[i];
		}
		Str[length - 1] = '\0';

		bool eror = false;
		double Ox = NULL, Oy = NULL;
		char* NextToken = NULL;
		char* copy = NULL;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = Str[i];
		}
		copy = strtok_s(Str2, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Ox = stoi(copy, 0, 10);
		if (Ox == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		copy = strtok_s(NULL, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Oy = stoi(copy, 0, 10);
		if (Oy == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		if (eror) {
			SetEmptyString();
		}

	}
	friend ostream& operator << (ostream& out, coordinate& other)
	{
		out << other.Str << endl;
		return out;
	}
	friend istream& operator >> (istream& in, coordinate& other) {
		string st;
		in >> st;
		other.set(st.c_str());
		return in;
	}

	void sqrtnum()
	{
		double alfa;
		double real;
		double image;
		double argz;
		int k;
		/*///////////*/
		bool eror = false;
		double Ox = NULL, Oy = NULL;
		char* NextToken = NULL;
		char* copy = NULL;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = Str[i];
		}
		copy = strtok_s(Str2, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Ox = stoi(copy, 0, 10);
		if (Ox == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		copy = strtok_s(NULL, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Oy = stoi(copy, 0, 10);
		if (Oy == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		if (eror) {
			SetEmptyString();
		}
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

	double korni()
	{
		/*///////////*/
		bool eror = false;
		double Ox = NULL, Oy = NULL;
		char* NextToken = NULL;
		char* copy = NULL;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = Str[i];
		}
		copy = strtok_s(Str2, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Ox = stoi(copy, 0, 10);
		if (Ox == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		copy = strtok_s(NULL, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Oy = stoi(copy, 0, 10);
		if (Oy == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		if (eror) {
			return NULL;
		}
		/*//////////*/
		CountSqrtMod = sqrt(pow(Ox, 2) + pow(Oy, 2));
		CountSqrtMod = sqrt(CountSqrtMod);
		if (Ox < 0)
			CountSqrtMod = CountSqrtMod * (-1);//починил корень
		return CountSqrtMod;
	}

	bool operator>(coordinate srav1)
	{

		bool eror = false;
		double Ox = NULL, Oy = NULL;
		char* NextToken = NULL;
		char* copy = NULL;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = Str[i];
		}
		copy = strtok_s(Str2, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Ox = stoi(copy, 0, 10);
		if (Ox == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		copy = strtok_s(NULL, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Oy = stoi(copy, 0, 10);
		if (Oy == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		if (eror) {
			return NULL;
		}

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
		bool eror = false;
		double Ox = NULL, Oy = NULL;
		char* NextToken = NULL;
		char* copy = NULL;
		char* Str2 = new char[length];
		for (long unsigned int i = 0; i < length; i++) {
			Str2[i] = Str[i];
		}
		copy = strtok_s(Str2, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Ox = stoi(copy, 0, 10);
		if (Ox == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		copy = strtok_s(NULL, "i", &NextToken);
		if (copy == NULL)
		{
			cout << "error !" << endl;
			eror = true;
		}
		Oy = stoi(copy, 0, 10);
		if (Oy == NULL) {
			cout << "error !" << endl;
			eror = true;
		}
		if (eror) {
			return NULL;
		}

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

};
