#ifndef LIVELLO_H

#define LIVELLO_H

#include "oggetto.h"

class livello {
protected:
	FILE* file;
	const char nomefile[15] = { "mappa.txt" };
	int livAtt, livMax, livLong;
	listpntr liv;

public:
	livello();

	void chiudi(); //libera la memoria occupata dalla lista di oggetti e chiude il file

	listpntr livelloSuccessivo(int &lung); //ritorna il livello successivo legendolo da file o generandolo se necessario

	listpntr livelloPrecedente(int &lung); //ritorna il livello precedente leggendolo da file, in caso di lettura del livello ritorna puntatore nullo

	listpntr getLiv(int &lung); //ritorna il puntatore alla lista livello e la sua lunghezza tramite parametro

	int getLivAtt(); //ritorna il umero del livello attualmente caricato

	int getLivMax(); //ritorna il il numero del livello massimo generato

	int getLivLong(); //ritorna la lunghezza del livello

	listpntr resetLivello(); //resetta lo stato dei vari oggetti
	
private:

	void cancellaLivello(); //libera la memoria occupata dalla lista contenente gli oggetti

	void caricaLivello(); //legge il livello di numero livAtt

	void generaLivello(); //genera livello con difficolta livMax

	void objListGenerator(int nObj); //genera la lista di oggetti a partire dalla stringa letta su file

	void livStringGeneator(int nObj); //traduce la lista liv nella stringa da stampare su file

};

#endif