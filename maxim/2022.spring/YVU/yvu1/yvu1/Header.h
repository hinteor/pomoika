#define _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
using namespace std;
class coordinate
{
private:
	double Ox;
	double Oy;
	double CountSqrtMod;

public:
	void SetOx(double startOx)
	{
		Ox = startOx;
	}//сеттер реальной части 
	void SetOy(double startOy)
	{
		Oy = startOy;
	}//сеттер мнимой части 
	double GetX()
	{
		return Ox;
	}//геттер реально части
	double GetY()
	{
		return Oy;
	}//геттер мнимой части
	coordinate()
	{
		Ox = 1;
		Oy = 1;
	}//конструктор поумолчанию
	void sqrtnum()
	{
		double alfa;
		double real;
		double image;
		double argz;
		int k;
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
	coordinate(const coordinate& other) : Ox(other.Ox), Oy(other.Oy) {}
	coordinate(double X, double Y) :Ox(X), Oy(Y) {} //теперь 2 значения беру
	void createnum()
	{

		cout << "print Ox " << endl;
		cin >> Ox;
		cout << "print Oy " << endl;
		cin >> Oy;
		cout << Ox << "+" << Oy << "i" << endl;
	}

	double korni()
	{
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
};
istream& operator>>(istream& in, coordinate& tr)
{
	double val2, val3;
	val2 = 0;
	val3 = 0;
	system("cls");
	cout << "введите реальную часть числа " << endl;
	in >> val2;
	tr.SetOx(val2);
	cout << "введите мнимую числа " << endl;
	in >> val3;
	tr.SetOy(val3);
	return in;
}
ostream& operator<<(ostream& os, coordinate& tr) //перегрузка оператора >> теперь он передаёт значения в мой класс
{
	return os
		<< "длины сторон" << endl
		<< "сторона A : " << tr.GetX() << endl
		<< "сторона B : " << tr.GetY() << endl
		<< endl;
}
/*StringIdentificator operator + (const StringIdentificator& other)
{
	cout << "Вызвалась перегрузка оператора + для понкатенации строк"
		<< endl;
	StringIdentificator result;
	delete result.str;
	result.length = length + other.length;
	result.str = new char[result.length + 1];
	strcpy(result.str, str);
	strcpy(result.str + length, other.str);
	return result;
}*/
