#include "Funkcje.h"

static int licznikTablic = 0;

short* allokujTablice(short rozmiar) 
{
	short* tab = new short [rozmiar + 1];
	if (tab == nullptr) {
		throw invalid_argument("B��d alokacji pami�ci");
	}
	tab[0] = (static_cast<short>(rozmiar) << 8) | (licznikTablic & 0xFFFF);

	for (int i = 1; i < rozmiar; ++i)
	{
		tab[i] = 0;
	}
	licznikTablic++;

	return tab+1;
}

void zwolnijPamiec(short* tab) 
{
	if (tab != nullptr) 
	{
		delete[](tab - 1);
	}
}


void zapiszTabliceDoPliku(const char* nazwaPliku, short* tablica) {
    // Przesuwamy wskaźnik na początek tablicy (żeby mieć dostęp do rozmiaru i numeru)
    short* tablicaDoZapisu = tablica - 1;

    // Otwieramy plik w trybie binarnym do zapisu
    FILE* plik = fopen(nazwaPliku, "wb");
    if (plik) {
        // Zapisujemy całą tablicę do pliku
        size_t rozmiar = (tablicaDoZapisu[0] >> 8) & 0xFF;
        fwrite(tablicaDoZapisu, sizeof(short), rozmiar + 1, plik);
        fclose(plik);
    } else {
        cerr << "Nie można otworzyć pliku do zapisu.\n";
    }
}

short* odczytTablicy(const char* nazwaPliku, int rozmiar)
{
	FILE* plik = fopen(nazwaPliku, "rb");
    if (plik) {
        // Odczytujemy najpierw pierwszy element, aby poznać rozmiar tablicy
        short pierwszyElement;
        fread(&pierwszyElement, sizeof(short), 1, plik);

        // Wyciągamy rozmiar tablicy z pierwszego elementu
        size_t rozmiar = (pierwszyElement >> 8) & 0xFF;

        // Alokujemy pamięć na całą tablicę (łącznie z elementem 0)
        short* tablica = new short[rozmiar + 1];
        tablica[0] = pierwszyElement;

        // Odczytujemy pozostałą część tablicy
        fread(tablica + 1, sizeof(short), rozmiar, plik);
        fclose(plik);

        // Zwracamy wskaźnik do początku właściwej tablicy
        return tablica + 1;
    } else {
        cerr << "Nie można otworzyć pliku do odczytu.\n";
        return nullptr;
    }
}