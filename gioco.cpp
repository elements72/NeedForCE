#include "gioco.h"
        gioco::gioco()
        {
            score = 10;
            battery = 100;
            batteryLose = 0.4;
            scoreGain = 0;
            punteggi = new punteggio;  //in punteggi vengono salvati per ciascun livello il loro goal.
            moltGoal = 2;              //indica quanti punti ci fornisce un livello
            lvl = 1;                   
            lvlMax = 0;
                                    //carico il livello 0
            punteggi->limit = 0;
            punteggi->lvl = 0;
            punteggi->next = NULL;

            inizializza();         //setto colori e opzioni di ncurses
            endGame = false;
            l = new livello();     
            azione = 1;            //azione = 1 si carica il livello corrente
                                   //azione = 2 livello successivo
                                   //azione = 3 livello precedente
                                   //azione = 4 reset livello  
            limit = 0;
            goal = 0;
        }
        void gioco::start(mappa *m)
        {
            char c = 'a';
            int row , col;
            int flag  = 0;
            int time_taken;
            int globy = 0;
            clock_t start, end;
            start = clock();
            start = start * 1000;
            listpntr l1;
           // menu men = menu();

            getmaxyx(stdscr, row, col);
            player p1  =  player((COLS - OFFSET_MENU)/2 - 1, LINES - 5);

            while(c != 'q')
            {
                end = clock();
                c = getch();
                if (ref(start))
                {    
                    clear();
                    m->stampa_strada(flag);
                    flag = (flag + 1) % 5;
                    m->move(globy);
                    m->stampa(globy);
                    m->checkCollision(score, battery, &p1, globy);
                    score = score + scoreGain;
                    battery = battery - batteryLose; 
                    p1.move(c, col, row);
                    p1.stampa();
                    stampa_laterale(battery, score);
                    globy++;
                    refresh();
                }
                if(c == 'w' || c == 'a' || c == 's' || c == 'd')
                {
                    clear();
                    m->stampa_strada(flag);
                    m->stampa(globy);
                    m->checkCollision(score, battery, &p1, globy);
                    p1.move(c, col, row);
                    p1.stampa();
                    stampa_laterale(battery, score);
                    refresh(); 
                }

                if(c == 27)
                {
                    pausa();
                }
                if(check_game_over())
                {
                    mvprintw(LINES / 2, COLS - OFFSET_MENU + 6 , "BATTERIA ESAURITA!!!");
                    mvprintw(LINES / 2 + 1 , COLS - OFFSET_MENU + 2, "PREMI SPAZIO PER CONTINUARE");
                    refresh();
                    while(c != ' ')
                        c = getch();
                    refresh();
                    lvl = 0;
                    return;
                }
                if(check_goal())
                {
                    mvprintw(LINES / 2, COLS - OFFSET_MENU + 6 , "LIVELLO COMPLETATO");
                    mvprintw(LINES / 2 + 1 , COLS - OFFSET_MENU + 2, "PREMI SPAZIO PER CONTINUARE");
                    while(c != ' ')
                    {
                        c = getch();
                    }
                    azione = 2;
                    lvl++;
                    return;
                }
                if(check_retrocedi())
                {
                    mvprintw(LINES / 2, COLS - OFFSET_MENU + 9 , "LIVELLO PERSO");
                    mvprintw(LINES / 2 + 1 , COLS - OFFSET_MENU + 2, "PREMI SPAZIO PER CONTINUARE");
                    while(c != ' ')
                    {
                        c = getch();
                    }
                    lvl--;
                    azione = 3;
                    return;
                }
                if(m->check_ricarica(globy))
                {
                    mvprintw(LINES / 2, COLS - OFFSET_MENU + 5 , "NON SEI RIUSCITO A");
                    mvprintw(LINES / 2 + 1, COLS - OFFSET_MENU + 3 , "RAGGIUNGERE LO SCORE!!!");
                    mvprintw(LINES / 2 + 2 , COLS - OFFSET_MENU + 1, "PREMI SPAZIO PER CONTINUARE");
                    while(c != ' ')
                    {
                        c = getch();
                    }
                    azione = 4;
                    return;
                }
            }

            this->endGame = true;
            return;
        }
        mappa *gioco::genera_mappa()
        {
            mappa *m1;
            int lunghezza;


            //new mappa ha bisogno della lista di oggetti, dello score per passare al livello successivo, dello score
            //sotto il quale si retrocede, e della lunghezza della mappa.
            limit = ricerca_limit();
            if (azione == 1)
            {
                m1 = new mappa(l->getLiv(lunghezza), (lunghezza * 10) + limit, limit, lunghezza);
            }
            else if(azione == 2)
            {
                m1 = new mappa(l->livelloSuccessivo(lunghezza), (lunghezza * 10) + limit, limit, lunghezza);
                
            }
            else if(azione == 3)
            {

                m1 = new mappa(l->livelloPrecedente(lunghezza), (lunghezza * 10) + limit, limit, lunghezza);
            }
            else
            {
                lunghezza = l->getLivLong();
                m1 = new mappa(l->resetLivello(), (lunghezza * 10) + limit, limit, lunghezza);
            }

            goal = (lunghezza * moltGoal); 
            goal = goal + limit;
            punteggi = push(goal);
            return m1;
        }
        bool gioco::check_game_over()
        {
            return battery <= 0;
        }

        void gioco::start_menu()
        {   
            char c = 'a';
            int sel = 10;
            int notSel = 6;
            int s1 = sel;
            int s2 = notSel;
            int s3 = notSel;
            int selezionato = 0;
            while(true)
            {
                clear();
                mvprintw(0 + 10, COLS / 2 - 10, "NEED FOR SPEED");
                mvprintw(1 + 10, COLS / 2 - 10, "CERIGNOLA EDITION");
                if(c == 's' )
                {
                    selezionato = (selezionato + 1) % 3;
                    if(selezionato == 0)
                    {
                        s1 = sel;
                        s2 = notSel;
                        s3 = notSel;
                    }
                    else if(selezionato == 1)
                    {
                        s1 = notSel;
                        s2 = sel;
                        s3 = notSel;
                    }
                    else if(selezionato == 2)
                    {
                        s1 = notSel;
                        s2 = notSel;
                        s3 = sel; 
                    }
                }
                if(c == 'w')
                {
                    selezionato = (selezionato - 1);
                    if (selezionato < 0)
                    {
                        selezionato = 2;
                    }

                    if(selezionato == 0)
                    {
                        s3 = notSel;
                        s1 = sel;
                        s2 = notSel;
                    }
                    else if(selezionato == 1)
                    {
                        s1 = notSel;
                        s2 = sel;
                        s3 = notSel;
                    }
                    else if(selezionato == 2)
                    {
                        s1 = notSel;
                        s2 = notSel; 
                        s3 = sel;
                    }
                }
                attron(COLOR_PAIR(s1));
                mvprintw(LINES / 2 - 2, COLS / 2 - 10, "START");
                attroff(COLOR_PAIR(s1));
                attron(COLOR_PAIR(s2));
                mvprintw(LINES / 2 - 1 , COLS / 2 - 10, "ISTRUZIONI");
                attroff(COLOR_PAIR(s2));
                attron(COLOR_PAIR(s3));
                mvprintw(LINES / 2 , COLS / 2 - 10, "ESCI");
                attroff(COLOR_PAIR(s3));
                
                mvprintw(LINES - 6, 0, "COMANDI:");
                mvprintw(LINES - 5, 0, "W:Avanti\nS:Indietro\nA:Sinistra\nD:Destra");
                //mvprintw(LINES - 8, COLS/2 - 10, "Supera i livelli raggiungendo ");
                //mvprintw(LINES - 7, COLS/2 - 10, "lo score necessario!!!");
                //mvprintw(LINES - 6, COLS/2 - 10, "Attento agli ostacoli e alla batteria della tua auto!!!:");
                refresh();
                c = getchar();
                if(selezionato == 0 && c == 13)
                {
                    load_level();
                    reset_game();
                }
                else if(selezionato == 1 && c == 13)
                {
                    stampa_istruzioni();
                }
                else if(selezionato == 2 && c == 13)
                {
                    return;
                }
            }
            
        }
        void gioco::stampa_laterale(int energy, int score)
        {
            int col, row;
            int color;
            getmaxyx(stdscr, row, col);
            int prm = (int)(row*0.1);

            //Nome del gioco
            mvprintw(prm+1,col-20," NEED FOR ");
            mvprintw(prm+2,col-20,"   SPEED  ");
            mvprintw(prm+4,col-20," Cerignola");
            mvprintw(prm+5,col-20,"  Edition ");

            mvprintw((prm*2)+6, col-18,"LV: %d" ,lvl);

            //Punteggio Score
            mvprintw((prm*2)+8,col-18,"SCORE:");
            mvprintw((prm*2)+9,col-24,"%.4d / %.4d / %d", limit, score, goal);

            //Livello batteria
            mvprintw((prm*2)+11,col-18,"ENERGY:");
            mvprintw((prm*2)+12,col-18,"%d /100", energy);

            //Barra Benzina
            mvprintw((prm*3)+13,col-16," - ");
            int a;
            for(a=(prm*3)+14;a<((prm*3)+14)+(10-energy/10);a++){
                mvprintw(a,col-16,"| |");
            }
            if(battery < 60 && battery > 25)
                color = 8;
            else if(battery <= 25)
                color = 9;
            else
                color = 7;

                for(a-=1;a<(prm*3)+24;a++){
                mvprintw(a,col-16,"|");
                attron(COLOR_PAIR(color));
                mvprintw(a,col-15," ");
                attroff(COLOR_PAIR(color));
                mvprintw(a,col-14,"|");
            }
            mvprintw((prm*3)+24,col-16," - ");
        }
        void gioco::load_level()
        {
            char c = 'a';
            mappa *m;
            while(!endGame)
            {
                m = genera_mappa();
                modScoreGain();
                start(m);
                delete(m);
                if(lvl <= 0)
                    {
                        clear();
                        endGame = true;
                        mvprintw(LINES / 2, COLS / 2 - 4 , "GAME OVER");
                        refresh();
                        while(c != ' ' && c != 'q')
                        {
                            c = getch();
                        }
                    }
                else
                    reset();      
            }
            endwin();
        }
        void gioco::reset()
        {
            if(lvl == 1)
                score = 0;
            else
                score = ricerca_limit();
            //battery = 100;
        }
        void gioco::stampa_istruzioni()
        {
                char c = 'a';
                clear();
                attron(COLOR_PAIR(6));
                mvprintw(0, COLS/2 - 5, "ISTRUZIONI");
                attroff(COLOR_PAIR(6));
                mvprintw(2, 6, "Non vi è alcuna fine, punta al punteggio più alto!!");
                mvprintw(5, 1, "Raggiungi lo score necessario     ---->\n per passare di livello!!!");
                mvprintw(8, 1, "Attenzione alla batteria!!!       ---->");
                mvprintw(11, 1, "Se scenderai sotto un certo punteggio tornerai indietro di livello!!");
                mvprintw(12, 1, "Se invece non raggiungi lo score necessario rimarrai nello stesso.");

                int prm = (int)(LINES*0.1);
                mvprintw(5,COLS-18,"SCORE:");
                mvprintw(6,COLS-24,"%.4d / %.4d / %d", 1000, 1400, 3500);

                mvprintw(8,COLS-18,"ENERGY:");
                mvprintw(9,COLS-18,"%d/100", 100);

                attron(COLOR_PAIR(6));
                mvprintw(15, COLS/2 - 3, "OGGETTI");
                attroff(COLOR_PAIR(6));

                attron(COLOR_PAIR(4));
                mvprintw(20, 5, "^^^^^");
                mvprintw(19, 5, "^^^^^");
                mvprintw(18, 5, "^^^^^");
                attroff(COLOR_PAIR(4));

                
                mvprintw(18, 20, "<----    Attenzione i fossi tolgono molti punti!!!");
                mvprintw(19, 20, "         (Anche toccando i guardrail perdi punti)");

                mvprintw(22, 20, "<----    Le batterie ti ricaricano!!!");
                attron(COLOR_PAIR(1));
                mvprintw(22, 7, "B");
                attroff(COLOR_PAIR(1));
                
                mvprintw(24, 20, "<----    Le bombe eliminano tutti gli ostacoli!!!");
                attron(COLOR_PAIR(2));
                mvprintw(24, 7, "@");
                attroff(COLOR_PAIR(2));
                
                mvprintw(27, 20, "<----    Il ghiaccio ti fa sbandare!!!");
                attron(COLOR_PAIR(5));
                mvprintw(26, 6, "///");
                mvprintw(27, 6, "///");
                mvprintw(28, 6, "///");
                attroff(COLOR_PAIR(5));

                mvprintw(31, 20, "<----    Le auto si muovono!!!");
                attron(COLOR_PAIR(3));
                mvprintw(30, 6, "o-o");
                mvprintw(31, 6, "|^|");
                mvprintw(32, 6, "\\_/");
                mvprintw(33, 6, "o-o");
                attroff(COLOR_PAIR(3));

                //Nome del gioco

                refresh();
            while(c != 13)
            {
                c = getchar();
            }
            return;
        }

        bool gioco::check_goal()
        {
            return score >= goal;
        }

        bool gioco::check_retrocedi()
        {
            return score < limit ;
        }


        bool gioco::ref(clock_t start) 
        {
            long long unsigned int modulo;
            int dif = 0;
            if (lvl >= 10)
                dif = 200;
            if(lvl > 15)
                dif = 250;
            if(lvl > 20)
                dif = 300;

            clock_t end;
            end = clock();                                                       
            modulo = ((double)(end - start) / (double) CLOCKS_PER_SEC) * 10000; //Calcolo i millisecondi passati dall'inizio del programma
            if (modulo % (1000 - dif) == 0)                                     //Moltiplico per 10.000 in quanto il valore restituitoci è dell'ordine dei Millisecondi
                return true;
            else 
                return false;
        }


        punteggio *gioco::push(int val)
        {
            punteggio *tmp;
            if(lvl > lvlMax)
            {
                tmp = new punteggio;
                tmp->lvl = lvl;
                tmp->limit = val;
                tmp->next = punteggi;
                lvlMax = lvl;
                return tmp;
            }
            else
                return punteggi;
        }

        int gioco::ricerca_limit()
        {
            punteggio *tmp;
            tmp = punteggi;
            bool trovato = false;
            while(tmp != NULL && !trovato)
            {
                if(lvl  > tmp->lvl)
                    trovato = true;
                else
                    tmp = tmp->next;
            }
            return tmp->limit;
        }

        void gioco::modScoreGain()
        {
                if(lvl < 5)
                    scoreGain = 15;
                else if(lvl < 10)
                {
                    scoreGain = 12;
                }
                else if(lvl < 15)
                {
                    scoreGain = 10;
                }
                else if(lvl <= 20)
                {
                    scoreGain = 8;
                }     
                else if(lvl <= 25)
                {
                    scoreGain = 4;
                }     
                else if(lvl <= 30)
                {
                    scoreGain = 2;
                }   

        }

        void gioco::pausa()
        {
            char c = 'a';
            clear();
            mvprintw(LINES/2 - 6, COLS/2 - 2, "PAUSA");
            mvprintw(LINES/2 - 4, COLS/2 - 16, "Premi spazio per tornare al gioco");
            refresh();
            while(c != ' ')
            {
                c = getch();
            }
            return;
        }

        void gioco::reset_game()
        {
            punteggio *tmp;
            score = 10;
            battery = 100;
            batteryLose = 0.4;
            scoreGain = 0;

            //Pulisco punteggi
            while (punteggi->next != NULL)
            {
                tmp = punteggi;
                while(tmp->next->next != NULL)
                    tmp = tmp->next;
                delete(tmp->next->next);
                tmp->next = NULL;
            }
            delete punteggi;
            delete l;

            punteggi = new punteggio;
            moltGoal = 2;
            lvl = 1;
            lvlMax = 0;
            punteggi->limit = 0;
            punteggi->lvl = 0;
            punteggi->next = NULL;
            endGame = false;
            l = new livello();
            azione = 1;
            limit = 0;
            goal = 0;
        }



        void gioco::inizializza()
        {
            //system("tilix --geometry=10x100");
            nodelay(stdscr, TRUE);
            initscr(); //Crea lo schermo
            start_color();
            nodelay(stdscr, TRUE);
            noecho();  //Impostazione per evitare la stampa di ciò che è premuto sulla tastiera
            curs_set(0);
            init_pair(1, COLOR_GREEN, COLOR_BLACK);
            init_pair(2, COLOR_YELLOW, COLOR_BLACK);
            init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
            init_pair(4, COLOR_RED, COLOR_BLACK);
            init_pair(5, COLOR_CYAN, COLOR_BLUE);
            init_pair(6, COLOR_YELLOW, COLOR_BLACK);
            init_pair(7, COLOR_GREEN, COLOR_GREEN);
            init_pair(8, COLOR_YELLOW, COLOR_YELLOW);
            init_pair(9, COLOR_RED, COLOR_RED);
            init_pair(10, COLOR_BLACK, COLOR_WHITE);
            //bkgd(COLOR_PAIR(1));
        }
