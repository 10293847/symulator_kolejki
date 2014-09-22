#include <iostream>
#include <cstdlib>
#include <vector>

#include "kolejka.h"
#include "klient.h"

using namespace std;

extern Kolejka kolejka;


////----------------------\/---------------------konstruktor klasy Klient

Klient::Klient()
{
    czas_operacji = rand()%4+1;

    ile_poczeka = rand()%7+1;

    identyfikator = rand()%9000+1000;

    nastepny = NULL;
}

////----------------------\/---------------------destruktor klasy Klient

Klient::~Klient()
{
    //cout << "*-*-*-*-*\n";
}




