#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

#include <cstdio>



using namespace std;

short* allokujTablice(short rozmiar);

void zwolnijPamiec(short* tab);

bool zapiszDoPliku(const char* nazwaPliku, short* tab, int rozmiar);

short* odczytTablicy(const char* nazwaPliku,int rozmiar);