#include "player.h"

        player::player(int x, int y)
        {
            posx = x;
            posy = y;
            offsetX = 3;
            offsetY = 4;
        }
        void player::move(char direzione, int bordoX, int bordoY)
        {
            if(direzione == 'w')
            {
                if(posy - offsetY > (1))
                    posy--;
            }
            else if(direzione == 's')   
            {          
                if(posy < (bordoY - 1))
                posy ++;    
            }
            else if(direzione == 'a')  
            {           
                if(posx > (0+1))
                posx --;
            }
            else if(direzione == 'd')
            {
                if(posx < (bordoX - offsetX - 1 - OFFSET_MENU))
                    posx ++;
            }
        }
        void player::stampa()
        {
            mvprintw(posy, posx, "***");    
            mvprintw(posy-2, posx, "/ \\");    
            mvprintw(posy-1, posx,"***");    
            mvprintw(posy-3, posx, "*_*");
        }
        int player::getPosx()
        {
            return posx;
        }
        int player::getPosy()
        {
            return posy;
        }
        int player::getOffsetx()
        {
            return offsetX;
        }
        int player::getOffsety()
        {
            return offsetY;
        }