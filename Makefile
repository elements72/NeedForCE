main: NeedForCerignola.cpp player.o levelgenerator.o oggetto.o livello.o mappa.o gioco.o header.h
	g++ -o NeedForCerignola NeedForCerignola.cpp player.o levelgenerator.o mappa.o gioco.o livello.o oggetto.o -lncurses

player.o: player.cpp player.h
	g++ -c player.cpp

oggetto.o: oggetto.cpp oggetto.h
	g++ -c oggetto.cpp

livello.o: livello.cpp livello.h
	g++ -c livello.cpp

mappa.o: mappa.cpp mappa.h
	g++ -c mappa.cpp

gioco.o: gioco.cpp gioco.h
	g++ -c gioco.cpp
  
levelgenerator.o: levelgenerator.cpp levelgenerator.h
	g++ -c levelgenerator.cpp

clean:
	rm -f *.o

avvio: 
	tilix --geometry=72x34 --command=./NeedForCerignola
