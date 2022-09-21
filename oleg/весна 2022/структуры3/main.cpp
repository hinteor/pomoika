#include <iostream>
#include <string.h>
#include <fstream>
#include <locale.h>
#include <chrono>

using namespace std;
const int RUN = 32;
const int n1 = 10000;
const int n2 = 30000;
const int n3 = 70000;
const int n4 = 100000;
int fs[n1], fs2[n2], fs3[n3] , fs4[n4];


void PrintStats(int n, long long unsigned int& baseop, long long unsigned int& supop, float time, int& mem)
{
	cout << "Для N = " << n << " элементов:" << endl;
	cout << "Кол-во базовых операций: " << baseop << endl;
	cout << "Кол-во вспомогательных операций (сравнения): " << supop << endl;
	cout << "Памяти выделено: " << mem << " байт" << endl;
	cout << "Затраченное время: " << time << " секунд" << endl;

	baseop = supop = mem = 0;
}

void Reverse(int* a, int n)
{
	int c = n / 2;
	for (int i = 0; i < c; i++)
		swap(a[i], a[n - i - 1]);
}

void QuickSort(int* a, int n, long long unsigned int& baseop, long long unsigned int& supop, int& mem)
{

	int x, temp, i, j;
	mem += 4 * sizeof(int);
	x = a[n / 2];
	i = 0; j = n - 1;
	do
	{
		while (a[i] < x)
		{
			i++;
			supop++;
		}

		while (x < a[j])
		{
			j--;
			supop++;
		}

		if (i <= j)
		{
			temp = a[i]; a[i] = a[j]; a[j] = temp;
			i++; j--;
			baseop += 3;
		}
	} while (i < j);
	if (j > 0)
		QuickSort(a, j + 1, baseop, supop, mem);
	if (i < n - 1)
		QuickSort(a + i, n - i, baseop, supop, mem);
}

void StraightSelection(int* a, int n, long long unsigned int& baseop, long long unsigned int& supop, int& mem)//+++
{
	int i, j, tmp, * min;
	mem += 3 * sizeof(int) + sizeof(int*);
	for (i = 0; i < n - 1; i++)
	{
		min = a + i;
		baseop += 1;
		for (j = i + 1; j < n; j++) {
			supop++;
			if (a[j] < *min) {
				min = a + j;
				baseop += 1;
			}

		}

		tmp = *min;
		*min = a[i];
		a[i] = tmp;
		baseop += 2;
	}
}

void BubbleSort(int* a, int n, long long unsigned int& baseop, long long unsigned int& supop, int& mem)//++
{
	int i, j, x;
	mem += 3 * sizeof(int);
	for (i = 1; i < n; i++) {
		supop++;
		for (j = n - 1; j >= i; j--) {
			supop++;
			if (a[j - 1] > a[j])
			{
				x = a[j - 1];
				a[j - 1] = a[j];
				a[j] = x;
				baseop += 3;
			}
		}

	}


}

void sift(int* a, int L, int R, long long unsigned int& baseop, long long unsigned int& supop, int& mem) /*Просеивание сквозь пирамиду (вспомогательная функция)*/
{
	int i = L, j = 2 * L + 1, x = a[L];
	mem += 3 * sizeof(int);
	if (j < R && a[j + 1] > a[j]) { /*если элемент j не последний в рассматр. последовательности*/
		j++;
		supop++;
	}/*и правый брат больше левого, переставляем указатель на него*/
	while (j <= R && a[j] > x)    /*просматриваем потомков до конца последовательности,*/
	{                             /*если они больше текущего (х) элемента, т.е. нарушена*/
		a[i] = a[j];              /*упорядоченность пирамиды, то восстанавливаем ее,*/
		baseop++;
		i = j;                    /*поднимая потомков на уровень выше*/
		j = 2 * j + 1;
		supop += 2;
		if (j < R && a[j + 1] > a[j]) { /*и каждый раз выбираем для анализа большего из*/
			j++;                      /*братьев*/
			supop++;
		}
	}
	a[i] = x;
	baseop++;
}

void HeapSort(int* a, int n, long long unsigned int& baseop, long long unsigned int& supop, int& mem)//+++
{
	int L = n / 2, R = n - 1, x;
	while (L > 0)
		sift(a, --L, R, baseop, supop, mem);
	while (R > 0)
	{
		x = a[0];
		a[0] = a[R];
		a[R] = x;
		sift(a, L, --R, baseop, supop, mem);
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	int str;
	long long unsigned int base = 0;
	long long unsigned int sup = 0;
	int mem = 0;


	string path = "1.txt";
	ifstream f;
	do
	{
		system("CLS");
		cout << "Введите название файла:" << endl;
		cin >> path;
		f.open(path);
		if (!f.is_open() && !f.good()) {
			cout << "Ошибка ! файл не найден !" << endl;
			return 0;
		}
	} while (!f.is_open() && !f.good());



#pragma region QSort 
	cout << " _______________________________________________________" << endl;
	cout << "|                  Быстрая сортировка                   |" << endl;
	cout << " _______________________________________________________" << endl << endl;

	for (int i = 0; i < n1; i++)
	{
		f >> str;
		fs[i] = str;
	}

	auto start = chrono::high_resolution_clock::now();
	QuickSort(fs, n1, base, sup, mem);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	QuickSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs, n1);
	start = chrono::high_resolution_clock::now();
	QuickSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n2; i++)
	{
		f >> str;
		fs2[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	QuickSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	QuickSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs2, n2);
	start = chrono::high_resolution_clock::now();
	QuickSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	//////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n3; i++)
	{
		f >> str;
		fs3[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	QuickSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	QuickSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs3, n3);
	start = chrono::high_resolution_clock::now();
	QuickSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	//////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n4; i++)
	{
		f >> str;
		fs4[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	QuickSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	QuickSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs4, n4);
	start = chrono::high_resolution_clock::now();
	QuickSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();
#pragma endregion

#pragma region BubbleSort

	cout << " _______________________________________________________" << endl;
	cout << "|                  Сортировка пузырьком                 |" << endl;
	cout << " _______________________________________________________" << endl << endl;

	for (int i = 0; i < n1; i++)
	{
		f >> str;
		fs[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	BubbleSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	BubbleSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs, n1);
	start = chrono::high_resolution_clock::now();
	BubbleSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n2; i++)
	{
		f >> str;
		fs2[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	BubbleSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	BubbleSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs2, n2);
	start = chrono::high_resolution_clock::now();
	BubbleSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	//////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n3; i++)
	{
		f >> str;
		fs3[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	BubbleSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	BubbleSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs3, n3);
	start = chrono::high_resolution_clock::now();
	BubbleSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	//////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n4; i++)
	{
		f >> str;
		fs4[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	BubbleSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	BubbleSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs4, n4);
	start = chrono::high_resolution_clock::now();
	BubbleSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

#pragma endregion

#pragma region StraightSelection

	cout << " _______________________________________________________" << endl;
	cout << "|                  Сортировка выбором                   |" << endl;
	cout << " _______________________________________________________" << endl << endl;

	for (int i = 0; i < n1; i++)
	{
		f >> str;
		fs[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	StraightSelection(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	StraightSelection(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs, n1);
	start = chrono::high_resolution_clock::now();
	StraightSelection(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n2; i++)
	{
		f >> str;
		fs2[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	StraightSelection(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	StraightSelection(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs2, n2);
	start = chrono::high_resolution_clock::now();
	StraightSelection(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	//////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n3; i++)
	{
		f >> str;
		fs3[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	StraightSelection(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	StraightSelection(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs3, n3);
	start = chrono::high_resolution_clock::now();
	StraightSelection(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	//////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n4; i++)
	{
		f >> str;
		fs4[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	StraightSelection(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	StraightSelection(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs4, n4);
	start = chrono::high_resolution_clock::now();
	StraightSelection(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();


#pragma endregion

#pragma region HeapSort

	cout << " _______________________________________________________" << endl;
	cout << "|                Сортировка триугольником               |" << endl;
	cout << " _______________________________________________________" << endl << endl;

	for (int i = 0; i < n1; i++)
	{
		f >> str;
		fs[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	HeapSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	HeapSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs, n1);
	start = chrono::high_resolution_clock::now();
	HeapSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n2; i++)
	{
		f >> str;
		fs2[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	HeapSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	HeapSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs2, n2);
	start = chrono::high_resolution_clock::now();
	HeapSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	//////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n3; i++)
	{
		f >> str;
		fs3[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	HeapSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	HeapSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs3, n3);
	start = chrono::high_resolution_clock::now();
	HeapSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	//////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n4; i++)
	{
		f >> str;
		fs4[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	HeapSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	HeapSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs4, n4);
	start = chrono::high_resolution_clock::now();
	HeapSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();


#pragma endregion
}
