#include <iostream>
#include "Funkcje.h"


int main()
{
    int rozmiar = 10;
    short* tab = allokujTablice(rozmiar);

    if (tab == nullptr) {
        cerr << "Blad alokacji tablicy!" << endl;
        return 1;
    }

    // Wypełnianie tablicy przykładowymi danymi
    for (int i = 0; i < rozmiar; ++i) {
        tab[i] = static_cast<short>(i + 1);
    }

    // Zapis tablicy do pliku
    if (!zapiszDoPliku("test.txt", tab, rozmiar)) {
        cerr << "Blad zapisu tablicy do pliku!" << endl;
        zwolnijPamiec(tab);
        return 1;
    }

    zwolnijPamiec(tab);

    short* TablicazPliku = odczytTablicy("tab.bin", rozmiar);

    if (TablicazPliku == nullptr) {
        cerr << "Blad odczytu tablicy z pliku!" << endl;
        return 1;
    }

    for (int i = 0; i < rozmiar; ++i) {
        cout << TablicazPliku[i] << " ";
    }
    cout << endl;

    zwolnijPamiec(TablicazPliku);
}

