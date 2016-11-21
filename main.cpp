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

	for (rzad = 0; rzad < N; rzad++)
	{
		pozycja = 0;
		for (kolumna = 0; kolumna < N; kolumna++)
		{
			if ('A' + rzad + kolumna > 'Z' && rzad > 0)
			{
				tabula[rzad][kolumna] = 'A' + pozycja;
				pozycja++;
			}

			else if ('A' + rzad + kolumna == 'Z')
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

vector<vector<char> > tabula_recta_male (vector<vector<char> > tabula_recta_duze())
{
	vector<vector <char> > tabula = tabula_recta_duze();                //przeksztalcanie tablicy z duzymi literami na druga, z malymi
	const int N = 26;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            tabula[i][j] = tolower(tabula[i][j]);
        }
    }


 for (int i = 0; i < N; i++) //debug
    {
        for (int j = 0; j < N; j++)
        {
           cout <<  tabula[i][j] <<" ";
        }
        cout << endl;
    }

	return tabula;
}

bool przelaczniki (int argc, char* argv[])
{
    if (argc < 2 || argc > 8)                                          //sprawdzenie, czy uzytkownik nie podaje za malo lub za duzo argumentow
	{
		cout << "Podano niewlasciwa ilosc argumentow" << endl << endl;
		return false;
	}


    string klucz, nazwa_wejscie, nazwa_wyjscie, zaszyfrowane;        // badanie przelacznikow
	if (argc > 1)                                                    // pierwszym parametrem jest nazwa programu, sprawdzamy wiec kolejne
	{
		for (int i = 1; i < argc; i++)
		{
			string arg = argv[i];
			if (arg == "-h")
			{
				return false;
			}

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


    return true;
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

	else
	{
		while (!plik.eof())
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
  	vector<vector<char> > tabula_male = tabula_recta_male (vector<vector<char> > tabula_recta_duze());

	int dlugosc = tekst.length();
	string polskieZnaki = "ąćęłóśńżźĄĆĘŁÓŚŃŻŹ";
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
	while (klucz.length() < dlugosc)                 // sprawdzam czy klucz jest wystarczajaco dlugi
	{                                                // jezeli nie to powtarzam go tak dlugo, az bedzie minimum dlugosci tekstu
		klucz += klucz[iterator];
		iterator++;
	}

	transform(klucz.begin(), klucz.end(), klucz.begin(), ::tolower);
	int rozmiar = tabula_duze[0].size();            //rozmiar taki sam jest dla tabuli_duze jak i tabuli_male
	int a, b;



	for (int i = 0; i < dlugosc; i++)
	{
		if (isupper(tekst[i]))
		{
			for (int j = 0; j < rozmiar; j++)
			{
				if (tabula_duze[0][j] == tekst[i])
				{
					a = j;
				}
				if (tabula_male[j][0] == klucz[i])
				{
					b = j;
				}
			}
			zaszyfrowany += tabula_duze[a][b];
		}

		else if (islower(tekst[i]))
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
		else
		{
			tekst[i] = tekst[i];
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
		<< "Pamietaj! Szyfrowane sa tylko male oraz duze litery, wszelkie polskie znaki zostaja zastapione odpowiednikami. Liczby, znaki interpunkcyjne oraz znaki biale nie sa szyfrowane a jedynie przepisane w tekscie!" << endl
		<< "Przyklad poprawnego wywolania programu: vigenere.exe -i wejscie.txt -o wyjscie.txt -k klucz" << endl;
}


int main(int argc, char* argv[])
{

    if (przelaczniki(int arc, char* argv[]) == false)
    {
        pomoc();
        return 0;
    }

    else
    {   if (odczytanie(nazwa_wejscie) == "blad")
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
    }


	return 0;
}
