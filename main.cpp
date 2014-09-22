#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "kolejka.h"
#include "klient.h"

using namespace std;

Kolejka kolejka;

int main()
{
srand(time(NULL));

short ktora_minuta = 1;

char wybor='1';

cout << "\nSYMULATOR KOLEJKI DO BANKOMATU";
cout << "\n\naby rozpoczac wcisnij 't' lub 'y' - wybor zatwierdz klawiszem 'enter' : ";

cin >> wybor;

if (wybor != 't' && wybor != 'y')
{
    return 0;
}

while(ktora_minuta <= 120)
{
    cout << "czas: "<<ktora_minuta << endl;
    bool czy_p = kolejka.czy_przyjdzie_nowy();

    while(kolejka.czasy_odejscia.size()>0 && (kolejka.czasy_odejscia.at(0) == ktora_minuta) )
    {
        kolejka.odchodzi_obsluzony();
    }

    for(int i=0; i<kolejka.czasy_odejscia_max.size();i++)
    {
       if(kolejka.czasy_odejscia_max.at(i) == ktora_minuta)
       {
            kolejka.przesuniecie_kolejki(i, ktora_minuta);
            kolejka.odchodzi_zniecierpliwiony(i);
       }
    }

    if(kolejka.policz_klientow() == 10)
    {
        kolejka.jesli_pelna(kolejka.ile_klientow);
    }

    else if( kolejka.policz_klientow() < 10 && czy_p)
    {
        kolejka.dodaj_na_koniec(ktora_minuta);
        //kolejka.idz_na_koniec();
    }
//kolejka.czasy_odejscia_klientow();
cout << "\n -------> aktualnie w kolejce jest:  " << kolejka.policz_klientow() << "\n\n";
ktora_minuta++;
}

kolejka.statystyki();

return 0;
}





