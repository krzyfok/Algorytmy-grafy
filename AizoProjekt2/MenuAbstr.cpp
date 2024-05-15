#include<iostream>
#include"MenuAbstr.h"

using namespace std;

int** wsk = nullptr;
int liczba_kraw = 0;
int liczba_wierzcholkow = 0;
int obecna_liczba_krawedzi = 0;
void MenuAbstr::menu(MenuAbstr& obj)//menu g�owne
{

	while (true)
	{
		printf("MENU\n");
		printf("1.WCZYTAJ DANE Z PLIKU\n");
		printf("2.WYGENERUJ GRAF LOSOWO\n");
		printf("3.WYSWIETL GRAF\n");
		printf("4.ALGORYTM 1\n");
		printf("5.ALGORYTM 2\n");
		printf("6.ZMIANA TYPU\n");

		int x;
		cin >> x;
		switch (x)
		{
		case 2: wygeneruj(5, 50);
			break;
		case 3: wyswietlanie();
			break;
		default:
			break;
		}

	}

}
void MenuAbstr::wygeneruj(int liczba_wierzcholkow1, int gestosc)
{
	liczba_kraw = 0;
	obecna_liczba_krawedzi = 0;
	liczba_wierzcholkow = liczba_wierzcholkow1;
	int dostepna_liczba_krawedzi = 0;
	wsk = new int* [liczba_wierzcholkow];
	int** tab_pom = new int* [2];
	liczba_kraw = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) / 2 * gestosc / 100;//skierowany czy nie?? dla mst NIESKIEROWANA
	int liczba_kraw_wszystkich = (liczba_wierzcholkow * (liczba_wierzcholkow - 1)) / 2 ;
	dostepna_liczba_krawedzi = liczba_kraw_wszystkich;
	//generacja macierzy
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		wsk[i] = new int[liczba_kraw];
	}
	//wypelnienie zerami
	for (int i = 0; i < liczba_wierzcholkow; ++i) {
		for (int j = 0; j < liczba_kraw; ++j) {
			wsk[i][j] = 0;
		}

	}
	//geenracja tablicy pomocniczej do losowania krawedzi
	for (int i = 0; i < 2; i++)
	{
		tab_pom[i] = new int[liczba_kraw_wszystkich];
	}
	//generacja wszystkich mozliwych wierzcholkow
	int indeks = 0;
	int pom = 0;
	for (int i = 0; i < liczba_wierzcholkow; i++)
	{
		
		for (int k = pom+1; k < liczba_wierzcholkow; k++)
		{
			tab_pom[0][indeks] = pom;
			tab_pom[1][indeks] = k;
				indeks++;
		}
		pom++;
	}

	

	//generacja spojnego
	for (int i = 1; i < liczba_wierzcholkow; i++)
	{
		int wybrany_wierzcholek = rand() % (i);
		wsk[i][i - 1] = 1;
		wsk[wybrany_wierzcholek][i - 1] = 1;
		obecna_liczba_krawedzi++;
		dostepna_liczba_krawedzi--;
	}
	//usuwanie wierzcholkow spojnych z tab_pom --rozpoznanie usuni�tego przez 0 0 w tabeli pom
	for (int i = 0; i < obecna_liczba_krawedzi; i++)
	{
		int wierzch[2];
		int indeks = 0;
		for (int k = 0; k < liczba_wierzcholkow; k++)
		{
			if (wsk[k][i] == 1)
			{
				wierzch[indeks] = k;
				indeks++;
			}
			
		}
	
		for (int j = 0; j < liczba_kraw_wszystkich; j++)
		{
			if ((tab_pom[0][j] == wierzch[0] && tab_pom[1][j] == wierzch[1]) || (tab_pom[0][j] == wierzch[1] && tab_pom[1][j] == wierzch[0]))
			{
				
				tab_pom[0][j] = 0;
				tab_pom[1][j] = 0;
			}
		}


	}

	//losowanie wierzcholkow z tab_pom az do uzyskania zadanej gestosci
	for (int i = obecna_liczba_krawedzi; i < liczba_kraw; i++)
	{
		int wylosowany_ideks = rand() % dostepna_liczba_krawedzi;
		int indeks_dostepnych = 0;
	
		for (int k = 0; k < liczba_kraw_wszystkich; k++)
		{
		
			if ((tab_pom[0][k] != 0) || (tab_pom[1][k] != 0))
			{
				
				if (indeks_dostepnych == wylosowany_ideks)
				{
					wsk[tab_pom[0][k]][i] = 1;
					wsk[tab_pom[1][k]][i] = 1;
					tab_pom[0][k] = 0;
					tab_pom[1][k] = 0;
					dostepna_liczba_krawedzi--;
					obecna_liczba_krawedzi++;
					
				}
				indeks_dostepnych++;
				
			}
		}
	}
	delete[] tab_pom;
	
	

	printf("\nWYGENEROWANO\n");
	
}


void MenuAbstr::wyswietlanie()
{

	//wyswietlanie
	for (int i = 0; i < liczba_wierzcholkow; ++i) {
		for (int j = 0; j < liczba_kraw; ++j) {
			printf("%3d", wsk[i][j]);
		}
		cout << endl;
	}
	
}

