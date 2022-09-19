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


void PrintStats(int n, int& baseop,  int& supop, float time, int& mem)
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
void ShellSort(int* a, int n, int& baseop, int& supop, int& mem)/*шаг задается формулой h[t]=1, h[m]=3h[m+1]+2; t=log3(n)*/
{

	const int t = (int)(log(n) / log(3));
	int i, j, k, m, x;
	/* формирование массива шагов*/
	int* h = (int*)malloc(t * sizeof(int));
	h[t - 1] = 1;
	mem += 5 * sizeof(int) + 2 * sizeof(int*) + sizeof(t) + sizeof(h);
	
	for (m = t - 2; m >= 0; m--)
	{
		h[m] = h[m + 1] * 3 + 2;
		/*непосредственно сортировка*/
		supop += 2;
	}
	for (m = 0; m < t; m++) 	/*последовательно перебираем все расстояния*/
	{
		k = h[m];
		supop += 2;
		for (i = k; i < n; i++)	/*до конца цикла метод вставки с учетом шага h[m]*/
		{
			x = a[i]; j = i - k;
			while (j >= 0 && x < a[j])
			{
				a[j + k] = a[j];
				j -= k;
				supop += 1;
				baseop += 1;
			}
			a[j + k] = x;
			supop += 2;
			baseop += 2;
		}
	}
	free(h);
}
#pragma region TimSort
	void insertionSort(int arr[], int left, int right, int& baseop, int& supop, int& mem)
	{
		mem += 3 * sizeof(int);
		for (int i = left + 1; i <= right; i++)
		{
			int temp = arr[i];
			int j = i - 1;
			while (j >= left && arr[j] > temp)
			{
				supop++;
				arr[j + 1] = arr[j];
				baseop++;
				j--;
			}
			arr[j + 1] = temp;
			//baseop++;
		}
	}

	void merge(int arr[], int l, int m, int r, int& baseop, int& supop, int& mem)
	{

		int len1 = m - l + 1, len2 = r - m;
		int* left = new int[len1];
		int* right = new int[len2];
		int i = 0;
		int j = 0;
		int k = l;

		mem += 5 * sizeof(int) + 2 * sizeof(int*);

		for (i = 0; i < len1; i++)
		{
			left[i] = arr[l + i];
			//baseop++;
		}
		for (i = 0; i < len2; i++)
		{
			right[i] = arr[m + 1 + i];
			//baseop++;
		}

		while (i < len1 && j < len2)
		{
			if (left[i] <= right[j])
			{
				supop++;
				arr[k] = left[i];
				baseop++;
				i++;
			}
			else
			{
				arr[k] = right[j];
				//baseop++;
				j++;
			}
			k++;
		}

		while (i < len1)
		{
			arr[k] = left[i];
			//baseop++;
			k++;
			i++;
		}

		while (j < len2)
		{
			arr[k] = right[j];
			//baseop++;
			k++;
			j++;
		}

		delete[] left;
		delete[] right;
	}
	void NaturalMergeSort(int* a, int n, int& baseop, int& supop, int& mem)
	{
		int split;
		int last, end, i, * p = a, * tmp;
		char flag = 0, sorted = 0;
		int pos1, pos2, pos3;

		mem = 7 * sizeof(int) + 2 * sizeof(int*) + 2 * sizeof(char);
		//tmp = (int*)malloc(n * sizeof(int));
		tmp = new int[n];
		mem += n * sizeof(int);
		do
		{
			end = n; pos2 = pos3 = 0;
			do
			{
				p += pos2; end = n - pos3;
				for (split = 1; split < end && p[split - 1] <= p[split]; split++)
				{
					supop++;
				}
				if (split == n)
				{
					sorted = 1;
					break;
				}
				pos1 = 0; pos2 = split;
				while (pos1 < split && pos2 < end)
				{
					if (p[pos1] < p[pos2])
					{
						supop++;
						tmp[pos3++] = p[pos1++];
						baseop++;
					}
					else
					{
						tmp[pos3++] = p[pos2++];
						baseop++;
						if (p[pos2] < p[pos2 - 1])
						{
							supop++;
							break;
						}
					}
				}

				while (pos2 < end && tmp[pos3 - 1] <= p[pos2])
				{
					supop++;
					tmp[pos3++] = p[pos2++];
					baseop++;
				}
				while (pos1 < split)
				{
					tmp[pos3++] = p[pos1++];
					baseop++;
				}
			} while (pos3 < n);
			if (sorted) break;
			p = tmp;
			tmp = a;
			a = p;
			flag = !flag;
		} while (split < n);
		if (flag)
		{
			for (pos1 = 0; pos1 < n; pos1++)
				tmp[pos1] = a[pos1];

			baseop += n;
			delete[] a;
		}
		else
			delete tmp;
	}
	void TimSort(int arr[], int n, int& baseop, int& supop, int& mem)
	{


		for (int i = 0; i < n; i += RUN)
			insertionSort(arr, i, min((i + RUN - 1), (n - 1)), baseop, supop, mem);

		for (int size = RUN; size < n; size = 2 * size)
		{

			for (int left = 0; left < n; left += 2 * size)
			{

				int mid = left + size - 1;
				int right = min((left + 2 * size - 1), (n - 1));

				if (mid < right)
				{
					merge(arr, left, mid, right, baseop, supop, mem);
				}
			}
		}
	}
#pragma endregion
#pragma region MergeSort

	void Merge(int* a, int split, int n, int& baseop, int& supop, int& mem)
	{
		int pos1 = 0;
		int pos2 = split;
		int pos3 = 0;

		mem += 3 * sizeof(int);

		//int* temp = (int*)malloc(sizeof(int) * n);
		int* temp = new int[n];
		mem += n * (sizeof(int));
		while (pos1 < split && pos2 < n)
		{
			if (a[pos1] < a[pos2])
			{
				supop++;
				temp[pos3++] = a[pos1++];
				baseop++;
			}
			else
			{
				temp[pos3++] = a[pos2++];
				baseop++;
			}
		}

		while (pos2 < n)
		{
			temp[pos3++] = a[pos2++];
			baseop++;
		}
		while (pos1 < split)
		{
			temp[pos3++] = a[pos1++];
			baseop++;
		}


		for (pos3 = 0; pos3 < n; pos3++)
			a[pos3] = temp[pos3];

		baseop += n;

		delete temp;
		//free(temp);
	}

	void MergeSortRecursive(int* a, int n, int& baseop, int& supop, int& mem)
	{
		int split;
		mem += sizeof(int);

		if (n > 1)
		{
			split = n / 2;
			MergeSortRecursive(a, split, baseop, supop, mem);
			MergeSortRecursive(a + split, n - split, baseop, supop, mem);
			Merge(a, split, n, baseop, supop, mem);
		}
	}

#pragma endregion
	void StraightInsertion(int* a, int n, int& baseop, int& supop, int& mem)
	{
		int i, j, x;
		mem += 3 * sizeof(int);

		for (i = 1; i < n; i++)

		{
			baseop += 2;
			supop += 1;
			x = a[i];
			for (j = i; j && x < a[j - 1]; j--) /* находим место вставки, попутно сдвигая элементы */
			{
				a[j] = a[j - 1];
				baseop += 1;
				supop += 1;
			}
				
			a[j] = x;
		}
	}
int main()
{
	setlocale(LC_ALL, "Russian");
	int str;
	int base = 0;
	 int sup = 0;
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
	} while (!f.is_open() || !f.good());
#pragma region TimSort
	cout << " _______________________________________________________" << endl;
	cout << "|                Сортировка TimSort                     |" << endl;;
	cout << " _______________________________________________________" << endl << endl;

	f.open(path);

	for (int i = 0; i < n1; i++)
	{
		f >> str;
		fs[i] = str;
	}

	auto start = chrono::high_resolution_clock::now();
	TimSort(fs, n1, base, sup, mem);
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<float> time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	TimSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs, n1);
	start = chrono::high_resolution_clock::now();
	TimSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n2; i++)
	{
		f >> str;
		fs2[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	TimSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	TimSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs2, n2);
	start = chrono::high_resolution_clock::now();
	TimSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n3; i++)
	{
		f >> str;
		fs3[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	TimSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	TimSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs3, n3);
	start = chrono::high_resolution_clock::now();
	TimSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();
	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n4; i++)
	{
		f >> str;
		fs4[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	TimSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	TimSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs4, n4);
	start = chrono::high_resolution_clock::now();
	TimSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();
#pragma endregion
#pragma region MergeSortRecursive
	cout << " _______________________________________________________" << endl;
	cout << "|            Сортировка естественным слиянием           |" << endl;;
	cout << " _______________________________________________________" << endl << endl;

	f.open(path);

	for (int i = 0; i < n1; i++)
	{
		f >> str;
		fs[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs, n1);
	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n2; i++)
	{
		f >> str;
		fs2[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs2, n2);
	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n3; i++)
	{
		f >> str;
		fs3[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs3, n3);
	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();
	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n4; i++)
	{
		f >> str;
		fs4[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs4, n4);
	start = chrono::high_resolution_clock::now();
	NaturalMergeSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();
#pragma endregion
#pragma region ShellSort
	cout << " _______________________________________________________" << endl;
	cout << "|                Сортировка ShellSort                   |" << endl;;
	cout << " _______________________________________________________" << endl << endl;

	f.open(path);

	for (int i = 0; i < n1; i++)
	{
		f >> str;
		fs[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	ShellSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	ShellSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs, n1);
	start = chrono::high_resolution_clock::now();
	ShellSort(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n2; i++)
	{
		f >> str;
		fs2[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	ShellSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	ShellSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs2, n2);
	start = chrono::high_resolution_clock::now();
	ShellSort(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n3; i++)
	{
		f >> str;
		fs3[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	ShellSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	ShellSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs3, n3);
	start = chrono::high_resolution_clock::now();
	ShellSort(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();
	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n4; i++)
	{
		f >> str;
		fs4[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	ShellSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	ShellSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs4, n4);
	start = chrono::high_resolution_clock::now();
	ShellSort(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();
#pragma endregion
#pragma region StraightInsertion
	cout << " _______________________________________________________" << endl;
	cout << "|                Сортировка StraightInsertion                     |" << endl;;
	cout << " _______________________________________________________" << endl << endl;

	f.open(path);

	for (int i = 0; i < n1; i++)
	{
		f >> str;
		fs[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs, n1);
	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs, n1, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n1, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n2; i++)
	{
		f >> str;
		fs2[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs2, n2);
	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs2, n2, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n2, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();

	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n3; i++)
	{
		f >> str;
		fs3[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs3, n3);
	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs3, n3, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n3, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();
	/////////////////////////////////////////////////////////////////////////

	f.open(path);

	for (int i = 0; i < n4; i++)
	{
		f >> str;
		fs4[i] = str;
	}

	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В неотсортированном массиве" << endl << endl;

	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В отсортированном массиве" << endl << endl;

	Reverse(fs4, n4);
	start = chrono::high_resolution_clock::now();
	StraightInsertion(fs4, n4, base, sup, mem);
	end = chrono::high_resolution_clock::now();
	time = end - start;
	PrintStats(n4, base, sup, time.count(), mem);
	cout << "В массиве, отсортированном в обратном порядке" << endl << endl;

	f.close();
#pragma endregion
}
