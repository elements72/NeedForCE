#ifndef MAPPA_H

#define MAPPA_H

#include "player.h"
#include "livello.h"

class mappa
{
    protected:
        int goal;
        int limit;
        int lunghezza;
        listpntr listaOggetti;
        public:
            mappa(listpntr l1, int goal, int lim, int l);
            void checkCollision(int &score, double &battery, player *p1, int globy );
            void move(int globy);
            void stampa(int globy);
            void stampa_strada(int flag);
            bool check_ricarica(int globy);
            int getGoal();
};

#endif