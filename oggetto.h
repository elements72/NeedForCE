#ifndef OGGETTO_H

#define OGGETTO_H 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "player.h"

const int BATTERY = 15;
const char BATTERYTXTR[10][10] = {  "B        ", 
									"         ", 
									"         ", 
									"         ", 
									"         ", 
									"         ", 
									"         ", 
									"         ", 
									"         ", 
									"         ", };

const int BUCA = 400;
const char BUCATXTR[10][10] = { "^^^^     ", 
								"^^^^     ", 
								"^^^^     ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         " };

const int AUTO = 250;
const char AUTOTXTR[10][10] = { "o-o      ", 
								"\\_/      ", 
								"|^|      ", 
								"o-o      ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         " };

const char ICETXTR[10][10] = {  "///      ", 
								"///      ", 
								"///      ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         " };
const char BOMBTXTR[10][10] = { "@        ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         ", 
								"         " };

class oggetto {
protected:
	int posx, posy, globaly;
	int offsetX, offsetY;
	int  type, score;
	double battery;
	bool enable, disappearOnContact;
	char texture[10][10];

public:

	oggetto(int type, int x, int y, int offx, int offy, int score, const double battery, const char txtr[10][10], bool disappear);

	void move();

	void stampa();

	bool effect(int& score, double& battery, player *p);

	void abilita();

	int getPosX();

	int getGloalY();

	int getType();

	int getPosY();

	int getOffsetx();

	int getOffsety();

	void reset();

};

struct lista {
	oggetto* val;
	lista* next;
};

typedef lista* listpntr;

oggetto* objGenerator(int type, int posx, int globaly);

#endif
