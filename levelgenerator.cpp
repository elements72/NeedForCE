#include <time.h>
#include <stdlib.h>
#include "levelgenerator.h"
#include "player.h"
#include "oggetto.h"

using namespace std;

listpntr item_creator(int &n_obj, int level, int &lev_lenght)
{	
	listpntr l1 = NULL;
	listpntr l2 = NULL;
    listpntr l3 = NULL;
    listpntr l4 = NULL;
	srand(time(NULL));
	//Numero di corsie larghe 4 caratteri l'una (come la macchina)
	int ncas = (COLS - OFFSET_MENU - 4) / 4;
	//vettore che serve per dei controlli che devo ancora implementare (false=nessuna minaccia/true=minaccia)
	bool flag[ncas];
	//variabile per far s� che ci sia almeno una corsia vuota
	int last;
	last = rand() % ncas;
	for(int k=0; k<ncas; k++)
	{
		if(last != k)
		{
			flag[k] = true ;
		}
	}
	//probabilit� batterie e ostacoli
	float per_bat = min(92 + 0.2 * level, 98.0) ;
	float per_ost = max(85 - 0.2 * level, 70.0) ;
	float per_mac = max(85 - 0.5 * level, 70.0) ;
	int cont_mac = 0 ;
	if(level < 5) per_mac = 101;
    int salti = (10 - (level / 2));
    salti = max(salti, 5);
	//questo for fa s� che ogni x caratteri della mappa si creino ostacoli e/o batterie
	for (int j = 0; j < 500; j = j + salti)
	{
		//possibile creazione di un oggetto in ogni corsia
		for (int i = 0; i < ncas; i++)
		{
			
			//BATTERIE (1x1)
			//calcolo della probabilit� di generarsi della batteria
			if (rand() % 101 >= per_bat)
			{
				//i indica la corsia (partendo da 0) quindi moltiplicandola per 4 e sommando 2 abbiamo il carattere esatto della sua x (il +1 � per far s� che la batteria sia pi� centrale)
				l2 = new lista;
				l2->val = objGenerator(1, (i*4+2+1), j);
				l1 = push(l1, l2);
				flag[i] = false;
				n_obj++;
			}
            else if(rand()%501>=500)
            {
                l2 = new lista;
                l2->val = objGenerator(2, (i*4+2), j);
				l1 = push(l1, l2);
				flag[i] = false;
				n_obj++;
			}
        
			//BUCHE (4x3) e AUTO
			else 
			{
				//controllo per non creare buche nella corsia che deve essere libera
				if(last != i)
				{
					//calcolo della probabilit� di generarsi della buca (20%%)
					if (rand() % 101 >= per_ost)
					{
						//il rand � per la possibile generazione di un auto (2=BUCA 3=AUTO)
						l2 = new lista;
						l2->val = objGenerator((rand() % 2 + 4), (i*4+2), j);
						l1 = push(l1, l2);
						flag[i] = true;
						n_obj++;
					}
                    else
                    {
						if(cont_mac == 0)
						{

                        	if (rand() % 101 >= per_mac)
					    	{
							    //il rand � per la possibile generazione di un auto (2=BUCA 3=AUTO)
							    l4 = new lista;
						   		l4->val = objGenerator(3, (i*4+2), j);
							    l3 = push(l3, l4);
		    					flag[i] = true;
			    				n_obj++;
								cont_mac++;
				    		}
                        	else flag[i] = false;
						}
						else flag[i] = false;
                    }
				}
			}
			cont_mac++;
			if (cont_mac == 3) cont_mac = 0 ;
		}
		cont_mac == 0 ;
		//percorso libero
		if(last!= 4 && last != 0)
		{
			
			if(flag[last + 1] == false)
			{
				if(flag[last - 1] == false)
				{
					if(rand() % 3 == 1) last = last + 1;
					else if(rand() % 3 == 2) last = last - 1;
				}
				else
				{
					if(rand() % 2 == 1) last = last + 1;
				}
			}
		}
		else if(last == 4)
		{
			if(flag[last - 1] == false)
			{
				if(rand() % 2 == 0) last = last - 1;
			}
		}
		else
		{
			if(flag[last + 1] == false)
			{
				if(rand() % 2 == 0) last = last + 1;
			}
		}
	}
    l1 = accoda(l3, l1);
    lev_lenght = l1->val->getGloalY();
	return l1;
}

listpntr push(listpntr l1, listpntr l2)
{
	l2->next = l1;
	return l2;
}

listpntr accoda(listpntr l3, listpntr l1)
{
    listpntr tmp = l1;
    while(tmp->next != NULL) tmp = tmp->next;
    tmp->next = l3;
    return l1;
}