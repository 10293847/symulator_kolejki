#pragma once

#include <iostream>
#include <vector>

#include "klient.h"

using namespace std;

struct Kolejka
{
    vector<short>czasy_odejscia;
    vector<short>czasy_odejscia_max;
    vector<short>identyfikatory;

    short ile_klientow;
    short ile_klientow_ok;
    short zniecierpliwieni;
    short stan_kolejki;
    short laczny_czas_obslugi;

    Klient *pierwszy;

    Kolejka();
    ~Kolejka();

    bool czy_przyjdzie_nowy();

    void dodaj_na_koniec(short ktora_minuta);
    void jesli_pelna(short ile_klientow);

    void usun_poczatek(); //"podfunkcja" usun_klienta_nr(int nr); w zasadzie nadmiarowa
    void usun_klienta_nr(int nr);
    void idz_na_koniec();

    int policz_klientow();

    void odchodzi_obsluzony();
    void odchodzi_zniecierpliwiony(int numer);
    void przesuniecie_kolejki(int numer,short ktora_minuta);
    void czasy_odejscia_klientow();

    void statystyki();
};
