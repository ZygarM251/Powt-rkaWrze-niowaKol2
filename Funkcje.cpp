#include "Funkcje.h"

static int licznikTablic = 0;

short* allokujTablice(short rozmiar) 
{
	short* tab = new short [rozmiar + 1];
	if (tab == nullptr) {
		throw invalid_argument("B³¹d alokacji pamiêci");
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


bool zapiszDoPliku(const char* nazwaPliku, short* tab, int rozmiar)
{
	FILE* file = fopen(nazwaPliku, "w+b");
	if (file == nullptr) 
	{
		return false;
	}

	if (fwrite(&rozmiar, sizeof(rozmiar), 1, file) != 1) 
	{
		fclose(file);
		return false; 
	}

	if (fwrite(tab - 1, sizeof(short), rozmiar + 1, file) != rozmiar + 1) {
		fclose(file);
		return false; 
	}

	fclose(file);
	return true;
}

short* odczytTablicy(const char* nazwaPliku, int rozmiar)
{
	FILE* file = fopen(nazwaPliku, "rb");
	if (file == nullptr) {
		return nullptr;
	}

	if (fread(&rozmiar, sizeof(rozmiar), 1, file) != 1) {
		fclose(file);
		return nullptr; 
	}
	short* tab = new short[rozmiar + 1];
	if (tab == nullptr) {
		fclose(file);
		return nullptr; 
	}


	if (fread(tab, sizeof(short), rozmiar + 1, file) != rozmiar + 1) {
		delete[] tab;
		fclose(file);
		return nullptr; 
	}

	fclose(file);

	return tab + 1;
}