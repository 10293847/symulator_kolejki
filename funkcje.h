#pragma once

#include <iostream>
#include <vector>

using namespace std;




bool czy_przyjdzie_nowy();

void kolejka_nowy_nie(short &ile_klientow);
void kolejka_nowy_tak(short &ktora_minuta ,short &ile_klientow, short &ile_klientow_ok, short &stan_kolejki);

