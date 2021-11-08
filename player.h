#ifndef PLAYER_H

#define PLAYER_H

#include "header.h"


class player
{
    protected:
        int posx, posy;
        int offsetX, offsetY;
    public:
        player(int x, int y);
        void move(char direzione, int bordoX, int bordoY);
        void stampa();
        int getPosx();
        int getPosy();
        int getOffsetx();
        int getOffsety();
};

#endif