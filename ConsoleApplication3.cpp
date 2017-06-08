// ConsoleApplication3.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#define N 64

using namespace std;

class BodyPart {
private:
	int health;
	int block;
	int damage;
	bool Active;

public:
	BodyPart()
	{
		health = rand() % 5 + 10000;
		block = rand() % 5 + 1;
		damage = rand() % 5 + 1;
		Active = true;
	}

	int getHealth()
	{
		return health;
	}

	int getDamage()
	{
		return damage;
	}

	int getBlock()
	{
		return block;
	}

	bool getStatus()
	{
		return Active;
	}

	void receiveDamage(int dmg)
	{
		health -= dmg;
		if (health <= 0)
			Active = false;
	}

};

class Fighter : public BodyPart {
private:
	int bleedLimit; //ilosc krwi jaka zwodnik moze stracic
	int bleedCounter; //licznik utracownej krwi
	bool Alive;

public:
	BodyPart Body[5];
	
	Fighter()
	{
		Alive = true;
		bleedCounter = 0;
		bleedLimit = rand() % 5 + 6;
	}

	void checkStatusFighter()
	{
		if (!Body[0].getStatus())
			Alive = false; //zawodnik ginie gdy staci glowe
		else if (bleedCounter >= bleedLimit)
			Alive = false; //lub straci za duzo krwi
		else
			Alive = true;
	}

	int Bleeding() {

		for (int i = 1; i < 5; i++)   //pomijamy glowe bo nie ma znaczenia w przypadku krwawienia (jesli stracilismy glowe to i tak nie zyjemy)
		{
			if (!Body[i].getStatus()) bleedCounter++; //krwawienie wzmaga sie wraz z utrata kolejnych czesci ciala
		}
		return bleedCounter;
	}

	bool getStatusFighter()
	{
		return Alive;
	}

};

class Battle : public Fighter {
public:
	static void Attack(Fighter* Warrior1, Fighter* Warrior2)
	{
		int attackSource = rand() % 5;

		while (!Warrior1->Body[attackSource].getStatus()) //jesli czesc ciala jest niektywna losujemy tak dlugo az znajdziemy aktywna
			attackSource = rand() % 5;

		int target = rand() % 5;

		while (!Warrior2->Body[target].getStatus()) //jesli czesc ciala jest niektywna losujemy tak dlugo az znajdziemy aktywna
			target = rand() % 5;

		if (Warrior2->Body[target].getBlock() > rand() % 5 + 1) //jesli blok sie powiedzie zostaje wyprowadzona kontra
			Warrior1->Body[attackSource].receiveDamage(Warrior1->Body[attackSource].getDamage());
		else if (Warrior2->Body[target].getBlock() == rand() % 5 + 1) //jesli blok powiedzie sie w polowie zawodnik blokujacy otrzyma polowe obrazen
			Warrior2->Body[target].receiveDamage(ceil(Warrior1->Body[attackSource].getDamage() / 2));
		else //jesli blok sie nie powiedzie zawodnik otrzymuje pelne obrazenia
			Warrior2->Body[target].receiveDamage(Warrior1->Body[attackSource].getDamage());
	}

	static void Match(Fighter* Warrior1, Fighter* Warrior2)
	{
		while (true)
		{
			Warrior1->Bleeding(); // na poczatku tury zawodnik otrzymuje obrazenia od krwawienia

			Warrior1->checkStatusFighter(); //sprawdzamy czy przezyl
			if (!Warrior1->getStatusFighter())
				break;

			Attack(Warrior1, Warrior2);  //atak

			Warrior1->checkStatusFighter(); //sprawdzenie stanu w1
			if (!Warrior1->getStatusFighter())
				break;

			Warrior2->checkStatusFighter(); //sprawdzenie stanu w2
			if (!Warrior2->getStatusFighter())
				break;

			Warrior2->Bleeding(); // krwawienie

			Warrior2->checkStatusFighter(); //status drugiego zawodnika po krwawieniu
			if (!Warrior2->getStatusFighter())
				break;

			Attack(Warrior2, Warrior1); //atak drugiego zawodnika

			Warrior1->checkStatusFighter(); //sprawdzenie statusów po ataku
			if (!Warrior1->getStatusFighter())
				break;

			Warrior2->checkStatusFighter();
			if (!Warrior2->getStatusFighter())
				break;
		}
	}
};

class Tournament : public Battle {
public:
	static Fighter StartFight64(Fighter Duelists[])
	{
		for (int k = 0; k < 6; k++)
		{
			int i = 0;
			int j = N - 1;

			cout << endl << endl << k << ":" << endl << endl;

			while (true)
			{
				while (true)         //szukamy pierwszego zywego zawodnika od lewej strony
				{                                        
					if (Duelists[i].getStatusFighter())
						break;
					else
						i++;
					if (i >= j)
						break;
				}

				while (true)     //szukamy pierwszego zywego zawodnika od prawej strony
				{
					if (Duelists[j].getStatusFighter())
						break;
					else
						j--;
					if (j <= i)
						break;
				}

				if (i >= j)     
					break;

				Match(&(Duelists[i]), &(Duelists[j]));    //zawodnicy ci walcza ze soba

				cout << "i, j: " << i << " - " << Duelists[i].getStatusFighter() << ",   " << j << " - " << Duelists[j].getStatusFighter() << endl; //wypisujemy wynik
				i++;
				j--;
			}
		}
		for (int t = 0; t < N; t++)
		{
			if (Duelists[t].getStatusFighter())
			{
				cout << "\n\nZWYCIEZYL NUMER " << t << endl;
				return Duelists[t];
			}
		}
	}
};

int main()
{
	srand(time(NULL));

	Fighter Winners[N]; //tworzymy pusta tablice na zwyciezcow pomniejszych turniejow

	for (int i = 0; i < N; i++)
	{
		Fighter Duelists[N]; //tworzymy tablice malego turnieju
		Winners[i] = Tournament::StartFight64(Duelists); //zwyciezca kazdego z malych turneiju trafia do wielkiego turnieju
	}

	cout << "LET THE SHIT BEGIN!" << endl;

	Tournament::StartFight64(Winners);

	return 0;
}
