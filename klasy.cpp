#include "klasy.h"
using namespace std;

void Sterowanie::gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Sterowanie::ShowConsoleCursor(int showFlag)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = showFlag;
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

PracownikNaMiejscu::PracownikNaMiejscu(string i, string s, float st)
{
	imie = i;
	stano = s;
	stawka = st;
}

Kierowca::Kierowca(string i, string s, float st, float stW)
{
	imie = i;
	stano = s;
	stawka = st;
	stawkaZaWyjazd = stW;
}

void Pizzeria::dodajPracownika()
{
	system("cls");
	string s ="";
	string imie;
	float stawka;
	char war;
	int kod_znaku = 13;
	while (kod_znaku != 27)
	{
		cout << "Podaj imie pracownika: ";
		cin >> imie;
		cout << "Wybierz stanowisko [barman, kucharz, kierowca]: ";
		while (s == "")
		{
			cin >> s;
			if (s == "barman");
			else if (s == "kierowca");
			else if (s == "kucharz");
			else
			{
				s = "";
				cout << "Podaj poprawne stanowisko: " << ends;
			}
		}
		if (s == "barman")
		{
			cout << "Podaj stawke godzinowa dla barmana: ";
			cin >> stawka;
			Personel* pPrac;
			pPrac = new PracownikNaMiejscu(imie, s, stawka);
			personel.push_back(pPrac);
		}
		else if (s == "kucharz")
		{
			cout << "Podaj stawke godzinowa dla kucharza: ";
			cin >> stawka;
			Personel* pPrac;
			pPrac = new PracownikNaMiejscu(imie, s, stawka);
			personel.push_back(pPrac);
		}
		else if (s == "kierowca") 
		{
			cout << "Podaj stawke godzinowa dla kierowcy: ";
			cin >> stawka;
			int stawkaWyjazd;
			cout << "Podaj stawke za wyjazd dla kierowcy: ";
			cin >> stawkaWyjazd;
			Personel* pPrac;
			pPrac = new Kierowca(imie, s, stawka, stawkaWyjazd);
			personel.push_back(pPrac);
		}
		s = "";
		cout << "Wcisnij ENTER by kontynuowac lub ESC by wyjsc" << endl;
		war = _getch();
		kod_znaku = static_cast <int>(war);
	}
}

void Pizzeria::wypiszPracownikow()
{
	try
	{
		system("cls");
		list<Personel*> ::iterator it;
		cout << "Szef pizzerii: " << szef << endl;
		cout << "Lista pracownikow: " << endl;
		for (it = personel.begin(); it != personel.end(); it++)
		{
			cout << (*it)->getImie() << " - " << (*it)->getStanowisko() << endl;
		}
	}
	catch (runtime_error& error)
	{
		cout << "Runtime error: " << error.what() << "Wykryty blad" << endl;
	}
}

void PracownikNaMiejscu::obliczWyplate(float czasPracy, list<Personel*> ::iterator i)
{
	float dni;
	cout << (*i)->getImie() << " stawka: " << (*i)->getStawka() << "zl/h" << endl;
	cout << "Podaj ilosc przepracowanych dni: ";
	cin >> dni;
	cout << "Podaj premie dla pracownika: ";
	cin >> premia;
	cout << "Wyplata dla pracownika wynosi: " << (czasPracy * dni * stawka + premia)<< "zl" << endl;
}

void Kierowca::obliczWyplate(float czasPracy, list<Personel*> ::iterator i)
{
	float dni;
	int wyjazdy;
	cout << (*i)->getImie() << " stawka: " << (*i)->getStawka() << "zl/h" << endl;
	Kierowca* k1 = dynamic_cast<Kierowca*>(*i);
	cout << "stawka za wyjazd: " << k1->getStawkaZaWyjazd() <<"zl"<< endl; //dynamic cast
	cout << "Podaj ilosc przepracowanych dni: ";
	cin >> dni;
	cout << "Podaj ilosc wyjazdow kierowcy: ";
	cin >> wyjazdy;
	cout << "Wyplata dla pracownika wynosi: " << ((czasPracy * dni * stawka) + (wyjazdy*stawkaZaWyjazd)) << "zl" << endl;
}

void Pizzeria::generujWyplaty( float utarg)
{
	system("cls");
	bool znaleziony = false;
	string imie;
	if (personel.empty())
	{
		cout << "Brak personelu w bazie" << endl;
	}
	else
	{
		cout << "Pracownik dla ktorego generuje wyplate: ";
		cin >> imie;
		cout << endl;
		list<Personel*> ::iterator it;
		for (it = personel.begin(); it != personel.end(); it++)
		{
			if (imie == (*it)->getImie())
			{
				(*it)->obliczWyplate(czasPracy,it);
				znaleziony = true;
			}
			if (znaleziony)
				break;
		}
	}
}

Skladnik::Skladnik(string n, float i)
{
	nazwa = n;
	ilosc = i;
}

void Skladnik::dodajIlosc(float n)
{
	this->ilosc = this->ilosc + n;
}

void Magazyn::dodajDoMagazynu(Skladnik s)
{
	if (licznik < pojemnosc)
	{
		if (licznik + s.sprawdzIlosc() < pojemnosc)
		{
			bool czyZnalazl = false;
			if (wektor.empty())
				wektor.push_back(s);
			else
			{
				vector<Skladnik> ::iterator it;
				for (it = this->wektor.begin(); it != this->wektor.end(); it++)
				{
					if (it->sprawdzNazwe() == s.sprawdzNazwe())
					{
						it->dodajIlosc(s.sprawdzIlosc());
						czyZnalazl = true;

					}
				}
				if (czyZnalazl == false)
					wektor.push_back(s);
			}
			licznik = licznik + s.sprawdzIlosc();
		}
		else cout << "Produkt nie zmiesci sie w magazynie" << endl;
	}
	else cout << "Brak miejsca w magazynie" << endl;
}

void Magazyn::dodajDostawe()
{
	system("cls");
	string skladnik = "";
	float ilosc;
	char war;
	int kod_znaku = 13;
	while (kod_znaku!=27)
	{
		skladnik = "";
		cout << "Podaj nazwe skladnika oraz jego ilosc" << endl;
		cout << "Skladnik: ";
		while (skladnik == "")
		{
			cin >> skladnik;
			if(skladnik != "sos" && skladnik != "ser" && skladnik != "szynka"
				&& skladnik != "papryka" && skladnik != "boczek" && skladnik != "salami"
				&& skladnik != "cebula" && skladnik != "sos czosnkowy" && skladnik != "czosnek"
				&& skladnik != "rukola" && skladnik != "pieczarki" && skladnik != "maka"
				&& skladnik != "drozdze" && skladnik != "przyprawy" && skladnik != "tunczyk")
			{
				skladnik = "";
				cout << "Podaj poprawny skladnik: " << ends;
			}
		}
		cout << "Ilosc: ";
		cin >> ilosc;
		Skladnik s(skladnik, ilosc);
		dodajDoMagazynu(s);
		cout << "Wcisnij ENTER by kontynuowac lub ESC by wyjsc" << endl;
		war = _getch();
		kod_znaku = static_cast <int>(war);
	}
}

void Magazyn::wypiszStanMagazynu()
{
	system("cls");
	cout << "Zapelnienie magazynu: " << licznik <<"/"<< pojemnosc << endl;
	vector<Skladnik> ::iterator it;
	cout << "Skladniki w magazynie: " << endl;
	for (it = this->wektor.begin(); it != this->wektor.end(); it++)
	{
		cout << it->sprawdzNazwe() << ": " << it->sprawdzIlosc() << endl;
	}
}

void Skladnik::odejmijIlosc(string r)
{
	if (r == "mala")
		ilosc = ilosc - 0.1;
	else ilosc = ilosc - 0.2;
}

void Magazyn::zmniejszIlosc(string s, string r)
{
	vector<Skladnik>::iterator it;
	for (it = wektor.begin(); it != wektor.end(); it++)
	{
		if (it->sprawdzNazwe() == s)
		{
			it->odejmijIlosc(r);
		}
	}
}

bool Magazyn::sprawdzIlosc(string s, string r)
{
	bool czyJest = false;
	vector<Skladnik>::iterator it;
	for (it = wektor.begin(); it != wektor.end(); it++)
	{
		
		if (it->sprawdzNazwe() == s)
		{
			if (r == "mala")
			{
				if (it->sprawdzIlosc() >= 0.1)
					czyJest = true;
				else
				{
					czyJest = false;
					cout << "Zbyt mala ilosc " << s << endl;
				}
			}
			else
			{
				if (it->sprawdzIlosc() >= 0.2)
					czyJest = true;
				else 
				{
					czyJest = false;
					cout << "Zbyt mala ilosc " << s << endl;
				}
			}
		}
		else
		{
			czyJest = false;
		}
		if (czyJest)
			break;
	}
	return czyJest;
}

Pizzeria::Pizzeria(string n, string s, int czas)
{
	nazwa = n;
	czasPracy = czas;
	szef = s;
}

Pizzeria::~Pizzeria()
{
	for (list<Personel*>::const_iterator it = personel.begin(); it != personel.end(); ++it)
	{
		delete* it;
	}
	personel.clear();
}

Pizza::Pizza(string n, vector<string> s , int _nr, float c)
{
	nazwaPizzy = n;
	sklad = s;
	cena = c;
	nr = _nr;
}

bool Menu::wczytajMenu()
{
	ifstream odczyt;
	odczyt.open("menu.txt");

	if (!odczyt.good())
	{
		odczyt.close();
		return false;
	}

	while (true)
	{
			int nr;
			string nazwa;
			string skladnik = "";
			string linia;
			vector <string> sklad;
			float cena;

			odczyt >> nr >> nazwa;

			while (skladnik != "-" && !odczyt.fail())
			{
				odczyt >> skladnik;
				if (skladnik != "-")
				{
					sklad.push_back(skladnik);
				}
			}
			odczyt >> cena;

			if (odczyt.fail())
				break;

			Pizza p(nazwa, sklad, nr, cena);
			menu.push_back(p);
	}
	odczyt.close();
	return true;
}

void Menu::wypiszMenu()
{
	system("cls");
	cout << "===MENU===" << endl;
	cout << "[Pizza - skladniki - mala duza]" << endl;
	vector<Pizza> ::iterator it;
	for (it = menu.begin(); it < menu.end(); it++)
	{
		cout << it->getNr() << ". ";
		cout << it->getNazwaPizzy() << " - ";
		it->wypiszSklad();
		cout << "- ";
		cout << it->getCena() << "zl ";
		cout << it->getCena() * 1.5 << "zl" << endl;
	}
}

void Pizza::wypiszSklad()
{
	for (int i = 0; i < sklad.size(); i++)
		cout << sklad[i] << " ";
}

Zamowienie::Zamowienie(int n, vector<Pizza> p, float k, string r)
{
	nr = n;
	pizza = p;
	kwota = k;
	rozmiar = r;
}

void Pizzeria::dodajZamowienie(Magazyn &m, Menu menu)
{
	vector<Pizza> pizza;
	float kwota;
	int nr_pizzy;
	bool odpRozm;
	string rozmiar;
	char war;
	int kod_znaku = 13;
	while (kod_znaku!=27)
	{
		odpRozm = true;
		cout << "Podaj numer pizzy: ";
		cin >> nr_pizzy;
		vector<Pizza>::iterator it;
		for (it = menu.getMenu().begin(); it < menu.getMenu().end(); it++)
		{
			if (it->getNr() == nr_pizzy)
			{
				cout << "Podaj rozmiar[mala, duza]: ";
				while (odpRozm)
				{
					cin >> rozmiar;
					if (rozmiar == "duza")
					{
						kwota = it->getCena() * 1.5;
						odpRozm = false;
					}
					else if (rozmiar == "mala")
					{
						kwota = it->getCena();
						odpRozm = false;
					}
					else
					{
						cout << "Podaj prawidlowy rozmiar: ";
					}
				}

				bool czyJest = false;
				vector<string> ::iterator it3;
				for (it3 = it->getSklad().begin(); it3 < it->getSklad().end(); it3++)
				{
					czyJest = m.sprawdzIlosc(*it3, rozmiar);
					if (!czyJest)
						break;
				}
				if (!czyJest)
				{
					cout << "Brak skladnikow" << endl;
					break;
				}
				pizza.push_back(*it);
				vector<string> ::iterator it2;
				for (it2 = it->getSklad().begin(); it2 < it->getSklad().end(); it2++)
				{
					m.zmniejszIlosc(*it2, rozmiar);
				}

				Zamowienie zamow(nr_zam, pizza, kwota, rozmiar); 
				zam.push_back(zamow);
				utarg = utarg + kwota;

				cout << "Dodano do rachunku" << endl;
				pizza.clear();
				nr_zam++;
			}
		}
		cout << "Wcisnij ENTER by kontynuowac lub ESC by wyjsc" << endl;
		war = _getch();
		kod_znaku = static_cast <int>(war);
	}
}

void Pizzeria::wypiszZamowienia()
{	
	system("cls");
	if (!zam.empty())
	{
		vector<Zamowienie> ::iterator it;
		for (it = zam.begin(); it < zam.end(); it++)
		{
			
			cout << "Numer zamowienia: " << it->getNr() << endl;
			cout << "Zawartosc zamowienia: ";
			vector<Pizza> ::iterator it2;
			for (it2 = it->getPizza().begin(); it2 < it->getPizza().end(); it2++)
			{
				cout << it2->getNazwaPizzy() << " - ";
				cout << it->getRozmiar() << " - ";
				it2->wypiszSklad();
			}
			cout << endl << "Kwota: " << it->getKwota() << endl << endl;
		}
		cout << "Utarg pizzerii: " << getUtarg() << endl;
	}
	else cout << "Brak zamowien" << endl;
}

