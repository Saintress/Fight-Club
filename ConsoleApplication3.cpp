// ConsoleApplication3.cpp: Okreœla punkt wejœcia dla aplikacji konsoli.
//
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;


class BodyPart {
	
	int health;
	int block;
	int damage;
	bool Active;

public:
	
	BodyPart() { health = rand()%5 + 1; block = rand() % 5 + 1; damage = rand() % 5 + 1 ; Active = true; }
	
	void checkStatus() { if (health <= 0) Active = false; }
	
	int getHealth() { return health; }
	
	int getDamage() { return damage; }
	
	int getBlock() { return block; }
	
	bool getStatus() { return Active; }

	int receiveDamage(int dmg) { return health-=dmg; }

};


class Fighter : public BodyPart {
	
	int bleedLimit;
	int bleedCounter;
	bool Alive;
	BodyPart Head;
	BodyPart leftArm;
	BodyPart rightArm;
	BodyPart leftLeg;
	BodyPart rightLeg;

public:
	
	BodyPart Body[5] = { Head, leftArm, rightArm, leftLeg, rightLeg };

	Fighter() { Alive = true; bleedCounter = 0; bleedLimit = rand() % 5 + 6; }
	
	void checkStatusFighter() {
	    
		Body[0].checkStatus();
	    
		if (Body[0].getStatus() == false)  Alive = false; //zawodnik ginie gdy staci glowe  
	    
		else if (bleedCounter >= bleedLimit) Alive = false; //lub straci za duzo krwi
	    
		else Alive = true;
	};
	
	int Bleeding() {
		
		for (int i = 1; i < 5; i++)   //pomijamy glowe bo nie ma znaczenia w przypadku krwawienia (jesli stracilismy glowe to i tak nie zyjemy)
		{
			Body[i].checkStatus();
			
			if (Body[i].getStatus() == false) bleedCounter++;
		}
		
		return bleedCounter;
	}

	bool getStatusFighter() { return Alive; }
	
};


class Battle : public Fighter {
	
	int target;
	int attackSource;

public:
	
	void Attack(Fighter Warrior1, Fighter Warrior2) {

				attackSource = rand() % 5; 
				
				while (Warrior1.Body[attackSource].getStatus() == false) //jesli czesc ciala jest niektywna losujemy tak dlugo az znajdziemy aktywna
				{
					attackSource = rand() % 5;
					if (Warrior1.Body[attackSource].getStatus() == true) break;
				}
				
				target = rand() % 5;  

				while (Warrior2.Body[target].getStatus() == false) //jesli czesc ciala jest niektywna losujemy tak dlugo az znajdziemy aktywna
				{
					target = rand() % 5;
					if (Warrior2.Body[target].getStatus() == true) break;
				}
				
				if (Warrior2.Body[target].getBlock() > rand() % 5 + 1) Warrior1.Body[attackSource].receiveDamage(Warrior1.Body[attackSource].getDamage()); //jesli blok sie powiedzie zostaje wyprowadzona kontra
				
				else if (Warrior2.Body[target].getBlock() == rand() % 5 + 1) Warrior2.Body[target].receiveDamage(ceil(Warrior1.Body[attackSource].getDamage() / 2)); //jesli blok powiedzie sie w polowie zawodnik blokujacy otrzyma polowe obrazen
				
				else Warrior2.Body[target].receiveDamage(Warrior1.Body[attackSource].getDamage()); //jesli blok sie nie powiedzie zawodnik otrzymuje pelne obrazenia
				
				Warrior1.Body[attackSource].checkStatus();
				Warrior2.Body[target].checkStatus();

	}

	void Match(Fighter Warrior1, Fighter Warrior2) {
		
		while (Warrior1.getStatusFighter() && Warrior2.getStatusFighter())
		{

			Warrior1.Bleeding(); // na poczatku tury zawodnik otrzymuje obrazenia od krwawienia

			Warrior1.checkStatusFighter(); //sprawdzamy czy przezyl

			if (Warrior1.getStatusFighter() == false) break;
			
			Attack(Warrior1, Warrior2);  //atak

			Warrior1.checkStatusFighter(); //sprawdzenie stanu w1
			
			if (Warrior1.getStatusFighter() == false) break;

			Warrior2.checkStatusFighter(); //sprawdzenie stanu w2
			
			if (Warrior2.getStatusFighter() == false) break;

		    Warrior2.Bleeding(); // krwawienie

			Warrior2.checkStatusFighter(); //status drugiego zawodnika po krwawieniu

			if (Warrior2.getStatusFighter() == false) break;
            
			Attack(Warrior2, Warrior1); //atak drugiego zawodnika
			
			Warrior1.checkStatusFighter(); //sprawdzenie statusów po ataku

			if (Warrior1.getStatusFighter() == false) break;
			
			Warrior2.checkStatusFighter();

			if (Warrior2.getStatusFighter() == false) break;
		}
	}
};

class Tournament : public Battle {
	
	Fighter Duelists[64][64];

public:

	Tournament() {
		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < 64; j++)
			{
				
			}
         
	    }
	}

};



int main()
{
	srand(time(NULL));
    return 0;
}

