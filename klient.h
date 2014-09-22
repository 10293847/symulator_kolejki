#pragma once

#include <iostream>
#include <vector>


using namespace std;

struct Klient
{
    short czas_operacji;
    short identyfikator;
    short ile_poczeka;

    Klient *nastepny;

    Klient();
    ~Klient();
};
