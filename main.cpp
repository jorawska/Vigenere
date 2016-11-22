//Program szyfrujacy tekst z pliku za pomoca szyfru Vigenere'a.
//Autor Justyna Orawska


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>


using namespace std;


vector<vector<char> > tabula_recta()
{
	const int N = 26;
	vector<vector<char> > tabula(N, vector<char>(N));
	int pozycja, rzad, kolumna;

	for (rzad = 0; rzad < N; rzad++)
	{
		pozycja = 0;
		for (kolumna = 0; kolumna < N; kolumna++)
		{
			if ('a' + rzad + kolumna > 'z' && rzad > 0)
			{
				tabula[rzad][kolumna] = 'a' + pozycja;
				pozycja++;
			}

			else if ('a' + rzad + kolumna == 'z')
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
}

string odczytanie(string nazwa_wejscie)                         //funkcja odczytuje  dane z pliku
{
	fstream plik;
	plik.open(nazwa_wejscie.c_str(), ios::in);
	string wejscie;

	if (plik.good() == false)
	{
		return "blad";
	}


    while (getline(plik, wejscie))
    {        getline(plik, wejscie);
    }

	plik.close();
	return wejscie;
}

string szyfrowanie(string nazwa_wejscie, string klucz)
{
	string tekst = odczytanie(nazwa_wejscie);
	transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
	string zaszyfrowany = "";
	vector<vector<char> > tabula = tabula_recta();
	int dlugosc = tekst.length();
	int k = 0;
	while (klucz.length() < dlugosc)                 // sprawdzam czy klucz jest wystarczajaco dlugi
	{                                                // jezeli nie to powtarzam go tak dlugo, az bedzie minimum dlugosci tekstu
		klucz += klucz[k];
		k++;
	}

	transform(klucz.begin(), klucz.end(), klucz.begin(), ::tolower);
	int rozmiar = tabula[0].size();
	int a, b;
	int l = 0;



	for (int i = 0; i < dlugosc; i++)
	{
		if (isalpha(tekst[i]))
		{
			for (int j = 0; j < rozmiar; j++)
			{
				if (tabula[0][j] == tekst[i])       //sprawdzam gdzie w wierszu znajduje sie litera tekstu
				{
					a = j;
				}
				if (tabula[j][0] == klucz[i-l])       //sprawdzam gdzie w kolumnie znajduje sie  litera klucza
				{
					b = j;
				}
			}
			zaszyfrowany += tabula[a][b];
		}


		else
		{
			zaszyfrowany += tekst[i];
			l++;
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

	plik.close();
	return true;
}

void pomoc()
{
	cout << "Program szyfrujacy tekst przy pomocy szyfru Vigenere'a - pomoc" << endl
		<< "--------------------------------------------------------------" << endl
		<< "Aby wpisac klucz wedlug ktorego zaszfrowany zostanie tekst wpisz przelacznik -k a nastepnie podaj klucz." << endl
		<< "Aby podac nazwe pliku, ktory ma zostac zaszyfrowany wpisz przelacznik -i a nastepnie podaj nazwe (np. szyfr.txt)" << endl
		<< "Aby podac nazwe pliku, w ktorym zapisany zostanie zaszyfrowany tekst wpisz przelacznik -o a nastepnie podaj nazwe (np. zaszyfrowane.txt)" << endl
		<< "Aby uzyskac pomoc wpisz przelacznik -h" << endl
		<< "Pamietaj! Program nie szyfruje polskich znakow, liczb oraz znakow interpunkcyjnych!" << endl
		<< "Przyklad poprawnego wywolania programu: vigenere.exe -i wejscie.txt -o wyjscie.txt -k klucz" << endl;
}


int main(int argc, char* argv[])
{
    string arg, klucz, nazwa_wejscie, nazwa_wyjscie;


     if (argc == 2)                                                      //sprawdzenie, czy uzytkownik nie podaje za malo lub za duzo argumentow
        {
            if (argv[1] == "-h")
            {
                pomoc();
            }

            else
            {
                cout << endl << "Podano niewlasciwy przelacznik" << endl << endl;
                pomoc();
            }

            return 0;
        }


    else if (argc != 7)
        {
            cout << endl << "Podano niewlasciwa ilosc argumentow" << endl << endl;
            pomoc();
            return 0;
        }


                                                                        // badanie przelacznikow
	if (argc > 1)                                                       // pierwszym parametrem jest nazwa programu, sprawdzamy wiec kolejne
	{
		for (int i = 1; i < argc; i++)
		{
			arg = argv[i];

            if (arg == "-k")
			{
				klucz = argv[i + 1];
			}

			else if (arg == "-o")
			{
				nazwa_wyjscie = argv[i + 1];
			}

			else if (arg == "-i")
			{
				nazwa_wejscie = argv[i + 1];
			}
		}
	}


       if (odczytanie(nazwa_wejscie) == "blad")
        {
            cerr << "Nie udalo sie otworzyc pliku do zaszyfrowania";
            return 0;
        }
        odczytanie(nazwa_wejscie);
        szyfrowanie(nazwa_wejscie, klucz);
        zapisywanie(nazwa_wyjscie, nazwa_wejscie, klucz);

        if (zapisywanie(nazwa_wyjscie, nazwa_wejscie, klucz) == false)
        {
            cerr << "Nie udalo sie zapisac pliku" << endl;
            exit(EXIT_FAILURE);
        }

        else
        {
            cout << "Tekst zostal zaszyfrowany oraz zapisany do pliku!" << endl;
        }



	return 0;
}
