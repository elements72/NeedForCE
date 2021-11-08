#ifndef GIOCO_H

#define GIOCO_H

#include "mappa.h"

struct punteggio
{
    int lvl;
    int limit;
    punteggio *next;
};



class gioco
{
    protected:
        int score;
        double battery; // Batteria del giocatore
        double batteryLose; //Consumo di batteria
        int scoreGain;
        int lvl;
        int azione; // Indica se si deve ricaricare, passare, o retrocedere di livello;
        int initialGoal = 0; // Punteggio iniziale
        bool endGame;
        int limit;
        int lvlMax;
        int moltGoal;
        int goal;
        punteggio *punteggi;
        livello *l;
    public:
        gioco();
        void start(mappa *m);
        mappa *genera_mappa();
        void start_menu();
        void stampa_laterale(int energy, int score);
        void load_level();
        void reset();
        void pausa();
        void stampa_istruzioni();
        void reset_game();
        bool check_goal();
        bool check_retrocedi();
        bool check_game_over();
        void modScoreGain();
        void inizializza();
        bool ref(clock_t start);
        punteggio *push(int val);
        int ricerca_limit();
};  

#endif