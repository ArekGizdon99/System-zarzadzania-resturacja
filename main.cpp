#include <iostream>
#include <conio.h>
#include "Debug/mem-leak-detect.h"
#include "klasy.h"
#define TURN_ON_MEM_LEAK_DETECTION

using namespace std;


int main()
{
	Pizzeria pizzeria("Pizza z Pieca", "Jan Kowalski", 8);
	Sterowanie ster;
	ster.ShowConsoleCursor(1);
	ster.gotoxy(0, 0);
	pizzeria.menu.wczytajMenu();
	int y = 0;
	int x = 0;

	
	while (true) 
	{
		bool warunek = true;
		int c;
		cout << "SYSTEM ZARZADZANIA PIZZERIA" << endl;	
		cout << "------"<<pizzeria.nazwaPizzerii()<<"------" << endl<<endl;
		cout << "WYBIERZ OPCJE:" << endl;	
		cout << "1.ZAMOWIENIA" << endl;
		cout << "2.MAGAZYN" << endl;
		cout << "3.PRACOWNICY" << endl;
		cout << "4.WYJSCIE" << endl;

		while (warunek)
		{
			if (y < 4)
				y = 4;

			ster.gotoxy(x, y);
			
			c = _getch();
			switch (c)
			{
			case 0x48:
				--y;
				break;
			case 0x50:
				++y;
				break;

			case 13:
				if (y == 4)
				{
					system("cls");
					cout << "1. DODAJ ZAMOWIENIE" << endl;
					cout << "2. HISTORIA ZAMOWIEN" << endl;
					cout << "3. POWROT" << endl;
					x = 0;
					y = 0;

					while (warunek)
					{
						
						ster.gotoxy(x, y);
						c = _getch();
						switch (c)
						{
						case 0x48:
							--y;
							break;
						case 0x50:
							++y;
							break;
						case 13:
							if (y == 2)
							{
								warunek = false;
								system("cls");
								break;
							}
							else if (y == 0)
							{
								pizzeria.menu.wypiszMenu();
								pizzeria.dodajZamowienie(pizzeria.magazyn, pizzeria.menu);
								warunek = false;
								system("cls");
								break;
							}
							else if (y == 1)
							{
								pizzeria.wypiszZamowienia();
								cout << endl << "Wcisnij dowolny przycisk aby wrocic" << ends;
								_getch();
								system("cls");
								warunek = false;
								break;
							}
						}	
					}
				}

				if (y == 5)
				{
					system("cls");
					cout << "1. STAN MAGAZYNU" << endl;
					cout << "2. DODAJ DOSTAWE" << endl;
					cout << "3. POWROT" << endl;
					x = 0;
					y = 0;

					while (warunek)
					{

						ster.gotoxy(x, y);
						c = _getch();
						switch (c)
						{
						case 0x48:
							--y;
							break;
						case 0x50:
							++y;
							break;
						case 13:
							if (y == 2)
							{
								warunek = false;
								system("cls");
								break;
							}
							else if (y == 1)
							{
								pizzeria.magazyn.dodajDostawe();
								warunek = false;
								system("cls");
								break;
							}
							else if (y == 0)
							{
								pizzeria.magazyn.wypiszStanMagazynu();
								cout << endl << "Wcisnij dowolny przycisk aby wrocic" << ends;
								_getch();
								warunek = false;
								system("cls");
								break;
							}
						}
					}
				}

				if (y == 6)
				{
					system("cls");
					cout << "1. DODAJ PRACOWNIKA" << endl;
					cout << "2. WYPISZ PERSONEL" << endl;
					cout << "3. GENERUJ WYPLATY" << endl;
					cout << "4. POWROT" << endl;
					x = 0;
					y = 0;

					while (warunek)
					{
						ster.gotoxy(x, y);
						c = _getch();
						switch (c)
						{
						case 0x48:
							--y;
							break;
						case 0x50:
							++y;
							break;
						case 13:

							if (y == 3)
							{
								warunek = false;
								system("cls");
								break;
							}
							else if (y == 0)
							{
								pizzeria.dodajPracownika();
								warunek = false;
								system("cls");
								break;
							}
							else if (y == 2)
							{
								pizzeria.generujWyplaty(pizzeria.getUtarg());
								warunek = false;
								cout << endl << "Wcisnij dowolny przycisk aby wrocic" << ends;
								_getch();
								system("cls");
								break;
							}
							else if (y == 1)
							{
								pizzeria.wypiszPracownikow();
								warunek = false;
								cout << endl << "Wcisnij dowolny przycisk aby wrocic" << ends;
								_getch();
								system("cls");
								break;
							}
						}
					}
				}

				if (y == 7)
				{
					system("cls");
					cout << "---------" << endl;
					cout << "DO ZOBACZENIA!" << endl;
					cout << "---------" << endl;
					return 0;
				}
			}
		}

	}
}