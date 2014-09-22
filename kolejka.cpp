#include <iostream>
#include <cstdlib>
#include <vector>

#include "kolejka.h"
#include "klient.h"

using namespace std;

extern Kolejka kolejka;

////----------------------\/---------------------konstruktor klasy Kolejka

Kolejka::Kolejka()
{
    czasy_odejscia.resize(0);
    czasy_odejscia_max.resize(0);
    identyfikatory.resize(0);

    ile_klientow = 0;
    ile_klientow_ok = 0;
    zniecierpliwieni = 0;
    stan_kolejki = 0;
    laczny_czas_obslugi = 0;

    Klient *pierwszy = NULL;

    cout << "\nbankomat wlaczony! \n";
}

////----------------------\/---------------------destruktor klasy Kolejka

Kolejka::~Kolejka()
{

    cout << "\nbankomat wylaczony\n";
    czasy_odejscia.resize(0);
    czasy_odejscia_max.resize(0);
    identyfikatory.resize(0);
}

////----------------------\/---------------------zdarzenie losowe: czy pojawi sie w danej minucie nowy klient

bool Kolejka::czy_przyjdzie_nowy()
{
    short a = rand()%1000;
    if (a <= 403)
    {
        cout << "\t[ " << a << " ]" << endl;
        return true;
    }
    else
    {
        cout << "\t[ " << a << " ]" << endl;
        return false;
    }
}

////----------------------\/---------------------dodanie klienta na koniec kolejki

void Kolejka::dodaj_na_koniec(short ktora_minuta)
{
    Klient * nowy = new Klient;

    if (pierwszy==NULL)
    {
        pierwszy = nowy;
    }

    else
    {
        Klient *temp = pierwszy;

        while (temp->nastepny)
        {
            temp = temp->nastepny;
        }

        temp->nastepny = nowy;
        nowy->nastepny = NULL;
    }

    (ile_klientow)++;
    (ile_klientow_ok)++;
    (stan_kolejki)++;

    identyfikatory.push_back(nowy->identyfikator);
    czasy_odejscia_max.push_back(ktora_minuta+(nowy->ile_poczeka));

    if (czasy_odejscia.size() == 0)
    {
        czasy_odejscia.push_back(ktora_minuta+(nowy->czas_operacji));
    }
    else
    {
        czasy_odejscia.push_back( czasy_odejscia.back() + (nowy->czas_operacji) );
    }

    cout <<"\n nowy:  "<< (nowy->identyfikator) << " - - - ";
    cout <<"  -> obsluga : " <<  (nowy->czas_operacji);
    cout <<"  -> odejscie:  [minuta]: ";
    cout << czasy_odejscia.back();
    cout <<"  -> odejscie_max:  " << (ktora_minuta+(nowy->ile_poczeka));
    cout <<"  -> bo_poczeka_max: " << (nowy->ile_poczeka) << " minut";
    //cout << "\n -------> aktualnie w kolejce jest:  " << policz_klientow() << endl;
    //cout << "\n ---**--> czasy_odejscia.size()   :  " << czasy_odejscia.size() << endl;
return;
}

////----------------------\/---------------------usuniecie z poczatku kolejki

void Kolejka::usun_poczatek()
{
    Klient * tmp = pierwszy;

    if (pierwszy==NULL)
    {
        cout << "\n_kolejka pusta! \n"<< endl;
        return;
    }
    else
    {
        pierwszy = tmp->nastepny;
        delete tmp;
        tmp = NULL;
    }
return;
}


void Kolejka::usun_klienta_nr(int nr)
{
    if (nr==0)
    {
        Klient *tmp = pierwszy;
        pierwszy = tmp->nastepny;
        delete tmp;
        tmp = NULL;
    }
    else
    {
        int i = 0;

        Klient *tmp = pierwszy;
        Klient *tmp1;

        while (tmp)
        {
            if ((i+1)==nr) break;
            tmp = tmp->nastepny;
            i++;
        }
        if (tmp->nastepny->nastepny==NULL)
        {
            delete tmp->nastepny;
            tmp->nastepny = NULL;
        }
        else
        {
            tmp1 = tmp->nastepny;
            tmp->nastepny = tmp->nastepny->nastepny;
            delete tmp1;
            tmp1 = NULL;
        }
    }
}


////----------------------\/---------------------###[kontrola] przejscie na poczatek kolejki

void Kolejka::idz_na_koniec()
{
    Klient * i = pierwszy;

    cout << "\n";

    while(i)
    {
        cout << "  > "<<i->identyfikator << endl;
        i = i->nastepny;
    }
    cout << "\n";

return;
}

////----------------------\/---------------------licznik elementow w kolejce

int Kolejka::policz_klientow()
{
  int tmp=0;
  int licz =0;
    if (!pierwszy)
    {
        return 0;
    }
else
    {
    Klient *i = pierwszy;
        while (i)
        {
           i = (i->nastepny);
           licz++;
        }
        tmp=licz;
    }
return tmp;
}

////----------------------\/---------------------po losowaniu - brak nowego klienta w kolejce

void Kolejka::jesli_pelna(short ile_klientow)
{
    cout <<"przychodzi klient,   klient odchodzi. pelna kolejka !!" << endl;
    (ile_klientow)++;
return;
}

////----------------------\/---------------------odchodzi klient obsluzony

void Kolejka::odchodzi_obsluzony()
{
    cout << identyfikatory.at(0)<<" --- klient obsluzony, odchodzi!\n\n";
    laczny_czas_obslugi+=(pierwszy->czas_operacji);
    czasy_odejscia.erase(czasy_odejscia.begin());
    czasy_odejscia_max.erase(czasy_odejscia_max.begin());
    identyfikatory.erase(identyfikatory.begin());
    usun_poczatek();
    czasy_odejscia_klientow();

    stan_kolejki--;

}

////----------------------\/---------------------odchodzi klient zniecierpliwiony

void Kolejka::odchodzi_zniecierpliwiony(int numer)
{
    cout << identyfikatory.at(numer)<<" --- klient zniecierpliwiony odchodzi!\n\n";
    czasy_odejscia.erase(czasy_odejscia.begin()+numer);
    czasy_odejscia_max.erase(czasy_odejscia_max.begin()+numer);
    identyfikatory.erase(identyfikatory.begin()+numer);
    usun_klienta_nr(numer);
    czasy_odejscia_klientow();

    stan_kolejki--;
    zniecierpliwieni++;
    ile_klientow_ok--;
}

////----------------------\/---------------------###[kontrola] czasy_odejscia_klientow

void Kolejka::czasy_odejscia_klientow()
{

    if(stan_kolejki ==0 )
    {
        cout << "\n------------------kolejka pusta-----------------\n";
    }
    else
    {
        cout << "\n------------czasy_odejscia_klientow()-----------\n";
        cout << "[O] : - oczekiwane      [K] - krytyczne\n";

        for (int i=0; i<czasy_odejscia.size(); i++)
        {
            cout << i+1 << ". ->";
            cout << identyfikatory.at(i) << "\t";
            cout <<"[O] : " <<czasy_odejscia.at(i);
            cout <<"\t[K] : " <<czasy_odejscia_max.at(i) << endl;
        }
        cout << "\n";
    }


return;
}

////----------------------\/---------------------###przesuniecie kolejki po odejsciu zniecierpliwionego klienta

void Kolejka::przesuniecie_kolejki(int numer, short ktora_minuta)
{
    if(czasy_odejscia_max.size() == 1)
    {
        cout << "\n%%% brak przesuniecia, to byl jedyny klient\n";
    }
    else if(numer == czasy_odejscia_max.size() - 1)
    {
        cout << "%%% to byl ostatni klient w kolejce, nie ma przesuniecia\n";
    }
    else
    {
        cout << "%%% przesuniecie kolejki!\n";

        for (short i = numer+1; i<czasy_odejscia.size(); i++)
        {
            czasy_odejscia.at(i) = ( czasy_odejscia.at(i) - czasy_odejscia.at(i-1) + ktora_minuta );
        }
    }
}

////----------------------\/---------------------###[kontrola] statystyki

void Kolejka::statystyki()
{
    cout <<" \n\n------------Kolejka::statystyki()----------------\n\n";

    cout << "lacznie pojawilo sie: " << ile_klientow << "\n\n";

    cout << "zadowoleni klienci: " << ile_klientow_ok << "\n\n";

    cout << "klienci, ktorzy odeszli bedac w kolejce: " << zniecierpliwieni << "\n\n";

    cout << "laczny czas obslugi: " << laczny_czas_obslugi << "\n\n";
}
