#include "livello.h"
#include "levelgenerator.h"

	livello::livello() {
		file = fopen(nomefile, "w+");
		if (file == NULL)
			exit(1);
		livAtt = 1;
		livMax = 1;
		generaLivello(); // comprende anche la salvaLivello
	}

	void livello::chiudi()
	{
		cancellaLivello();
		fclose(file);
	}

	void livello::cancellaLivello() { //libera la lista livello e azzera la sua lunghezza
		while (liv != NULL) {
			listpntr temp=liv;
			liv = liv->next;
			delete temp->val; //cancella l'oggetto
			delete temp;	//cancella la struct lista di oggetti;
		}
		livLong=0;
	}

	listpntr livello::livelloSuccessivo(int &lung) { //carica o genera e carica il livelo successivo
		livAtt++;
		if (livAtt > livMax) {
			livMax = livAtt;
			cancellaLivello();
			generaLivello(); 
			lung = livLong;
			return liv;
		}
		else {
			cancellaLivello();
			caricaLivello();
			lung = livLong;
			return liv;
		}
	} 

	listpntr livello::livelloPrecedente(int &lung) { //carica il livello precedente, se non esiste restituisce NULL
		livAtt--;
		if (livAtt == 0) {
			return NULL;
		}
		else {
			cancellaLivello();
			caricaLivello();
			lung = livLong;
			return liv;
		}
	}

	void livello::caricaLivello() { //legge i livello di numero livAtt, scrive direttamete su liv
		rewind(file);
		int livello, nObj;
		fscanf(file, "%d=%d_%d:", &livello, &livLong, &nObj);
		while (livello != livAtt) {
			char c;
			do {
				c = fgetc(file);
			} while (c != '\n');
			fscanf(file, "%d=%d_%d:", &livello, &livLong, &nObj);
		}
		objListGenerator(nObj);
	}

	void livello::generaLivello(){  //genera livello con difficolta livMax
		int nObj = 0;
		liv = item_creator(nObj, livMax, livLong);
		livStringGeneator(nObj);
	}

	void livello::objListGenerator(int nObj) { //legge dal file gli oggetti e ne crea una lista in liv
		listpntr ris = NULL;
		listpntr punt = NULL;
		for (int i = 0; i < nObj; i++) {
			int type, posx, globaly;
			fscanf(file, "%d@%d|%d#", &type, &posx, &globaly);
			if (punt == NULL) {
				ris = new lista;
				punt = ris;
				punt->val = objGenerator(type, posx, globaly);
				punt->next = NULL;
			}
			else {
				punt->next = new lista;
				punt = punt->next;
				punt->val = objGenerator(type, posx, globaly);
				punt->next = NULL;
			}
		}
		fgetc(file); //smalticso la \n
		liv = ris;
	}

	void livello::livStringGeneator(int nObj) { //traduce l'attribuo liv in una stringa stampata su file
		fprintf(file, "%d=%d_%d:", livMax, livLong, nObj);
		listpntr temp = liv;
		while (temp != NULL) {
			oggetto* obj = temp->val;
			fprintf(file, "%d@%d|%d#", obj->getType(), obj->getPosX(), obj->getGloalY());
			temp = temp->next;
		}
		fprintf(file, "\n");
	}

	listpntr livello::getLiv(int  &lung)
	{
		lung = livLong;
		return liv; 
	}

	int livello::getLivAtt()
	{
		return livAtt;
	}

	int livello::getLivMax()
	{
		return livMax;
	}

	int livello::getLivLong()
	{
		return livLong;
	}

	listpntr livello::resetLivello(){
		listpntr temp = liv;
		while(temp != NULL){
			temp->val->reset(); //resetto lo stato degli oggetti
			temp = temp->next;
		}
		return liv;
	}