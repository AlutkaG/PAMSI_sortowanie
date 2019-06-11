#include<iostream>
#include<cstdlib>
#include<ctime>

using namespace std;

int* pom; //tablica pomocnicza

/**************************************************/
/*Procedura scalania podtablic.                   */
/**************************************************/
template<class Typ>
void scal(Typ* tab, int lewy, int prawy)
{
	int w_l, w_p, w_r, sr;
	sr = (lewy + prawy) / 2;
	w_l = lewy;
	w_p = sr + 1;
	w_r = 0;
	while (w_l <= sr && w_p <= prawy) {
		if (tab[w_l] < tab[w_p]) {
			pom[w_r] = tab[w_l];
			w_l++;
		}
		else {
			pom[w_r] = tab[w_p];
			w_p++;
		}
		w_r++;
	}
	if (w_p > prawy)
		for (int i = sr; i >= w_l; i--) {
			tab[prawy] = tab[i];
			prawy--;
		}
	for (int i = 0; i < w_r; i++) {
		tab[lewy] = pom[i];
		lewy++;
	}
}

/**************************************************************/
/*Procedura sortowania przez scalanie.                        */
/**************************************************************/
template<class Typ>
void SortowaniePrzezScalanie(Typ* tab, int lewy, int prawy)
{
	if (lewy < prawy) {
		int srodek = (lewy + prawy) / 2;
		SortowaniePrzezScalanie(tab, lewy, srodek);
		SortowaniePrzezScalanie(tab, srodek + 1, prawy);
		scal(tab, lewy, prawy);
	}
}

/**************************************************************/
/*Procedura dzielenia tablicy na tablice jednoelementowe.     */
/**************************************************************/
template<class Typ>
Typ podzial(Typ * tab, int lewy, int prawy) {
	int pivot = tab[(lewy + prawy) / 2];
	int l, p, tmp;
	l = lewy;
	p = prawy;
	while (true)
	{
		while (tab[l] < pivot) l++;
		while (tab[p] > pivot) p--;
		if (l < p)
		{
			tmp = tab[l];
			tab[l] = tab[p];
			tab[p] = tmp;
			l++; p--;
		}
		else return p;
	}
}
/**************************************************************/
/*Procedura sortowania szybkiego.     */
/**************************************************************/
template<class Typ>
void quicksort(Typ * tab, int l, int n) // sortowanie szybkie
{

	int sr;
	if (l < n)
	{
		sr = podzial(tab, l, n); // dzielimy tablice na dwie czesci; q oznacza punkt podzialu
		quicksort(tab, l, sr); // wywolujemy rekurencyjnie quicksort dla pierwszej czesci tablicy
		quicksort(tab, sr + 1, n); // wywolujemy rekurencyjnie quicksort dla drugiej czesci tablicy
	}

}

/**************************************************************/
/*Procedura czesciowego sortowania kopca.                     */
/**************************************************************/
template<class Typ>
void Heapify(Typ * tab, int i, int n) {
	int j = i, lewy = i * 2 + 1, prawy = i * 2 + 2, tmp;
	if ((lewy < n) && (tab[i] < tab[lewy]))
		j = lewy;
	if ((prawy < n) && (tab[j] < tab[prawy]))
		j = prawy;
	if (i != j) {
		tmp = tab[i];
		tab[i] = tab[j];
		tab[j] = tmp;
		Heapify(tab, j, n);
	}
}

/**************************************************************/
/*Procedura budowania kopca.                                  */
/**************************************************************/
template<class Typ>
void Zbuduj(Typ * tab, int n) {
	for (int i = (n - 2) / 2; i >= 0; i--)
		Heapify(tab, i, n);
}

/**************************************************************/
/*Sortowanie przez kopcowanie.                                */
/**************************************************************/
template<class Typ>
void HeapSort(Typ * tab, int n) {
	int tmp;
	Zbuduj(tab, n);
	for (int i = n - 1; i > 0; i--) {
		tmp = tab[i];
		tab[i] = tab[0];
		tab[0] = tmp;
		Heapify(tab, 0, i);
	}
}

template<class Typ>
void IntroSort(Typ* tab, int N, int M)
{
	int i;
	if (M <= 0)
	{
		HeapSort(tab, N);
		return;
	}
	i = podzial(tab, 0, N);
	if (i > N / 2 - 1)
		IntroSort(tab, i, M - 1);
	if (N - 1 - i > N / 2 - 1)
		IntroSort(tab + i + 1, N - 1 - i, M - 1);
}

//Tworzenie tablicy n elementowej
template<class Typ>
int StworzTablice(Typ * *tab, int n) {
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < n; j++)
			tab[i][j] = rand();
	return **tab;
}

//Wypisywanie elementow tablicy 
template<class Typ>
void PokazTablice(Typ * *tab, int n) {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < n; j++)
			cout << tab[i][j] << " ";
		cout << endl;
	}
}

int main()
{
	int** tab;
	int	n, ilosc_procent; //liczba elementów tablicy
	double czas, calkowity_czas = 0;
	clock_t start, stop;
	cout << "Podaj liczbe elementow:" << endl;
	cin >> n;
	int M = int(2 * log2(n));
	tab = new int* [100]; //przydzielenie pamiêci na tablicê liczb
	for (int k = 0; k < 100; k++)
		tab[k] = new int[n];
	pom = new int[n]; //przydzielenie pamiêci na tablicê pomocnicz¹

	StworzTablice<int>(tab, n); //tworzenie tablicy
	cout << endl;
	ilosc_procent = 0.997 * n; //ilosc procentowa posortowanej tablicy

	//sortowanie przez scalanie
	/*cout << "Sortowanie przez scalanie: " << endl;
	for (int l = 0; l < 100; l++) {
		SortowaniePrzezScalanie<int>(tab[l], 0, ilosc_procent - 1);
	}
	start = clock();
	for (int l = 0; l < 100; l++) {
		SortowaniePrzezScalanie<int>(tab[l], 0, n - 1);
	}
	stop = clock();
	czas = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu sortowania:" << czas << endl;

	StworzTablice<int>(tab, n);
	cout << endl;
	*/
	//sortowanie szybkie
	/*cout << "Sortowanie szybkie:" << endl;
	for (int l = 0; l < 100; l++) {
		quicksort<int>(tab[l], 0, ilosc_procent - 1);
	}
	start = clock();
	for (int l = 0; l < 100; l++) {
		quicksort<int>(tab[l], 0, n - 1);
	}
	stop = clock();
	czas = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu sortowania:" << czas << endl;


	StworzTablice<int>(tab, n);
	cout << endl;
	*/
	//sortowanie przez kopcowanie
	/*cout << "Sortowanie przez kopcowanie: " << endl;
	for (int l = 0; l < 100; l++) {
		HeapSort<int>(tab[l], ilosc_procent);
	}
	start = clock();
	for (int l = 0; l < 100; l++) {
		HeapSort<int>(tab[l], n);
	}
	stop = clock();
	czas = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu sortowania:" << czas << endl;


	StworzTablice<int>(tab, n);
	cout << endl;
	*/
	//sortowanie przez kopcowanie
	cout << "Sortowanie introspektywne: " << endl;
	for (int l = 0; l < 100; l++) {
		IntroSort<int>(tab[l], ilosc_procent-1,M);
	}
	start = clock();
	for (int l = 0; l < 100; l++) {
		IntroSort<int>(tab[l], n-1,M);
	}
	stop = clock();
	czas = (double)(stop - start) / CLOCKS_PER_SEC;
	cout << "Czas wykonania algorytmu sortowania:" << czas << endl;
	//wypisanie wyników
	/*for (int i = 0; i < 100; i++) {
		for (int j = 0; j < n; j++)
			cout << tab[i][j] << " ";
		cout << endl;
	}*/

	system("pause");
	return 0;
}
