#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <iterator>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;

static int nr_zam = 1;

class Sterowanie
{
public:
	void ShowConsoleCursor(int showFlag);
	void gotoxy(int x, int y);
};

class Personel 
{
protected:
	string stano;
	string imie;
	float stawka;
public:
	float getStawka() { return stawka; }
	string getStanowisko() { return stano; }
	string getImie() { return imie;  }
	virtual void obliczWyplate(float czasPracy, list<Personel*> ::iterator i) = 0;
};

class PracownikNaMiejscu : public Personel
{
	float premia;
public:
	PracownikNaMiejscu(string imie, string s, float st);
	virtual void obliczWyplate(float czasPracy, list<Personel*> ::iterator i);
};

class Kierowca : public Personel
{
	float stawkaZaWyjazd;
public:
	Kierowca(string imie, string s, float st, float stW);
	float getStawkaZaWyjazd() { return stawkaZaWyjazd; }
	virtual void obliczWyplate(float czasPracy, list<Personel*> ::iterator i);
};

class Skladnik
{
	float ilosc = 0;
	string nazwa;
public:
	Skladnik(string n, float i);
	float sprawdzIlosc() { return ilosc; }
	void dodajIlosc(float n);
	void odejmijIlosc(string r);
	string sprawdzNazwe() { return nazwa; }
};

class Magazyn
{
	float pojemnosc = 50;
	float licznik = 0;
	vector<Skladnik> wektor;
public:
	void dodajDoMagazynu(Skladnik s);
	void dodajDostawe();
	void zmniejszIlosc(string s, string r);
	void wypiszStanMagazynu();
	bool sprawdzIlosc(string s, string r);
};

class Pizza
{
	string nazwaPizzy;
	int nr;
	float cena;
	vector<string> sklad;
public:
	Pizza(string n, vector<string>, int _nr, float c);
	string getNazwaPizzy() { return nazwaPizzy; }
	vector<string>& getSklad() {return sklad;}
	void wypiszSklad();
	float getCena() { return cena; }
	int getNr() { return nr; }
};

class Menu
{
	vector<Pizza> menu;
public:
	void wypiszMenu();
	bool wczytajMenu();
	vector<Pizza>& getMenu() { return menu; };
};

class Zamowienie
{
	int nr;
	float kwota;
	string rozmiar;
	vector<Pizza> pizza;
public:
	Zamowienie(int n, vector<Pizza> p, float k, string r);
	int getNr() { return nr; }
	float getKwota() { return kwota; }
	string getRozmiar() { return rozmiar; }
	vector<Pizza>& getPizza() { return pizza; };
};

class Pizzeria
{
	string nazwa;
	string szef;
	list<Personel*> personel; 
	vector<Zamowienie> zam;
	float utarg = 0;
	float czasPracy;
public:
	Pizzeria(string n, string s, int czas);
	~Pizzeria();
	Magazyn magazyn;
	Menu menu;
	string nazwaPizzerii() { return nazwa; }
	float getUtarg() { return utarg; }
	void dodajZamowienie(Magazyn& m, Menu menu);
	void wypiszZamowienia();
	void generujWyplaty(float utarg);
	void dodajPracownika();
	void wypiszPracownikow();
};













