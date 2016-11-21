//Program szyfrujacy tekst z pliku za pomoca szyfru Vigenere'a.
//Autor Justyna Orawska

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>


using namespace std;

vector<vector<char> > tabula_recta_duze()
{
    const int N = 26;
    vector<vector<char> > tabula(N, vector<char>(N));
    int pozycja, rzad, kolumna;

    for( rzad = 0; rzad < N; rzad++)
    {
        pozycja = 0;
        for( kolumna = 0; kolumna < N; kolumna++)
        {
            if('A' + rzad + kolumna > 'Z' && rzad > 0)
            {
                tabula[rzad][kolumna] = 'A'+ pozycja;
                pozycja++;
            }

            else if('A' + rzad + kolumna == 'Z')
            {
                tabula[rzad][kolumna] = 'Z';
            }

            else
            {
                tabula[rzad][kolumna] = 'A' + rzad + kolumna;
            }
        }
    }
    return tabula;
}

vector<vector<char> > tabula_recta_male()
{
    const int N = 26;
    vector<vector<char> > tabula(N, vector<char>(N));
    int pozycja, rzad, kolumna;

    for( rzad = 0; rzad < N; rzad++)
    {
        pozycja = 0;
        for( kolumna = 0; kolumna < N; kolumna++)
        {
            if('a' + rzad + kolumna > 'z' && rzad > 0)
            {
                tabula[rzad][kolumna] = 'a'+ pozycja;
                pozycja++;
            }

            else if('a' + rzad + kolumna == 'z')
            {
                tabula[rzad][kolumna] = 'z';
            }

            else
            {
                tabula[rzad][kolumna] = 'a' + rzad + kolumna;
            }
        }
    }
    return tabula;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << tabula[i][j] << " ";
        }
        cout << endl;
    }
}

string odczytanie(string nazwa_wejscie)
{
    fstream plik;
    plik.open(nazwa_wejscie.c_str(), ios::in);
    string wejscie;

    if( plik.good() == false)
       {
           cerr << "Nie udalo sie otworzyc pliku do zaszyfrowania" << endl;
       }
    else
        {
            while( !plik.eof())
            {
                getline(plik, wejscie);
            }
        }
    plik.close();
    return wejscie;
}

string szyfrowanie(string nazwa_wejscie, string klucz)
{
    string tekst = odczytanie(nazwa_wejscie);
	string zaszyfrowany = "";
	vector<vector<char> > tabula_duze = tabula_recta_duze();
	vector<vector<char> > tabula_male = tabula_recta_male();
	int dlugosc = tekst.length();
	string polskieZnaki = "πÊÍ≥ÛúÒøü•∆ £”å—Øè";
    string odpowiedniki = "acelosnzzACELOSNZZ";
    int znak = 0;
    for (int i = 0; i < dlugosc; i++)
    {
        if (tekst[i] == polskieZnaki[znak])
        {
            tekst[i] = odpowiedniki[znak];
            znak++;
        }
    }
	int iterator = 0;
	while (klucz.length() < dlugosc)        // sprawdzam czy klucz jest wystarczajaco dlugi
	{                                       // jezeli nie to powtarzam go tak dlugo, az bedzie minimum dlugosci tekstu
		klucz += klucz[iterator];
		iterator++;
	}

    int rozmiar = tabula_duze[0].size(); //rozmiar taki sam jest dla tabuli_duze jak i tabuli_male
    int a, b;
	//char c = ' ';


	for (int i = 0; i < dlugosc; i++)
    {
        if (isupper(tekst[i]))
        {
                for (int i = 0; i < dlugosc; i++)
                    {
                        for (int j = 0; j < rozmiar; j++)
                            {
                            if (tabula_duze[0][j] == tekst[i])
                                {
                                    a = j;
                                }
                            if (tabula_duze[j][0] == klucz[i])
                                {
                                    b = j;
                                }
                            }
                        zaszyfrowany += tabula_duze[a][b];
                    }
        }

        else if (islower(tekst[i]))
        {
             for (int i = 0; i < dlugosc; i++)
                    {
                        for (int j = 0; j < rozmiar; j++)
                            {
                            if (tabula_male[0][j] == tekst[i])
                                {
                                    a = j;
                                }
                            if (tabula_male[j][0] == klucz[i])
                                {
                                    b = j;
                                }
                            }
                        zaszyfrowany += tabula_male[a][b];
                    }
        }

        else if (ispunct(tekst[i]))
        {
            tekst [i] = tekst [i];
        }

        else if (isspace(tekst[i]))
        {
            tekst [i] = tekst [i];
        }

        else if (tekst[i] == '\n')
        {
            tekst[i] = '\n';
        }
        else if (isdigit(tekst[i]))
        {
            tekst[i] = tekst [i];
        }
        else
        {
            cerr << "W tekscie znajduja sie znaki inne niz duze badz male litery, znaki interpunkcyjne oraz spacje!"<<endl;

        }
    }

    return zaszyfrowany;
}



bool zapisywanie(string nazwa_wyjscie, string nazwa_wejscie, string klucz)
{
    string szyfrowane = szyfrowanie(nazwa_wejscie, klucz);
    fstream plik;
    plik.open(nazwa_wyjscie.c_str(), ios::out);
    plik << szyfrowane;
    if (plik.good() == false)
    {
        return false;
    }
    else
    {
        cout << "plik zapisano" <<endl;
        cout << szyfrowane <<endl;
    }

    plik.close();
    return true;
}

void pomoc()
{
    cout << "Program szyfrujacy tekst przy pomocy szyfru Vigenere'a - pomoc" << endl
    << "--------------------------------------------------------------"<< endl
    <<"Aby wpisac klucz wedlug ktorego zaszfrowany zostanie tekst wpisz przelacznik -k a nastepnie podaj klucz."<< endl
    <<"Aby podac nazwe pliku, ktory ma zostac zaszyfrowany wpisz przelacznik -i a nastepnie podaj nazwe (np. szyfr.txt)" << endl
    <<"Aby podac nazwe pliku, w ktorym zapisany zostanie zaszyfrowany tekst wpisz przelacznik -o a nastepnie podaj nazwe (np. zaszyfrowane.txt)" << endl
    <<"Aby uzyskac pomoc wpisz przelacznik -h"<<endl
    <<"Pamietaj! Szyfrowane sa tylko male oraz duze litery, wszelkie polskie znaki zostaja zastapione odpowiednikami. Liczby, znaki interpunkcyjne oraz znaki biale nie sa szyfrowane a jedynie przepisane w tekscie!" << endl
    <<"Przyklad poprawnego wywolania programu: vigenere.exe -i wejscie.txt -o wyjscie.txt -k klucz" <<endl;
}


int main (int argc, char* argv[])
{
    if (argc < 2 || argc > 8)           //sprawdzenie, czy uzytkownik nie podaje za malo lub za duzo argumentow
    {
        cout << "Podano niewlasciwa ilosc argumentow" << endl << endl;
        pomoc();
    }

    string klucz, nazwa_wejscie, nazwa_wyjscie, zaszyfrowane;
    if (argc > 1)                       // pierwszym parametrem jest nazwa programu, sprawdzamy wiec kolejne
    {
        for (int i = 1; i < argc; i++)
            {
                string arg = argv[i];
                if (arg == "-h")
                    {
                        pomoc();
                        return 0;
                    }

                else if (arg == "-k")
                    {
                        klucz = argv[i+1];
                       // cout << klucz <<endl;   //debug
                    }

                else if (arg == "-o")
                    {
                        nazwa_wyjscie = argv[i+1];
                       // cout << nazwa_wyjscie << endl;  //debug
                    }

                else if (arg == "-i")
                    {
                        nazwa_wejscie = argv[i+1];
                       // cout << nazwa_wejscie << endl;  //debug
                    }
                }


    }




    string tekst;
    tekst = odczytanie(nazwa_wejscie);
    cout << "tekst = " << tekst << endl;

    string szyfrem;
    szyfrem = szyfrowanie(nazwa_wejscie, klucz);
    cout << "szyfrowane = " << szyfrem << endl;

    zapisywanie(nazwa_wyjscie, nazwa_wejscie, klucz);


return 0;
}



