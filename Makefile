CC = g++

CompileParms = -c -Wall -std=c++11

OBJS = standaard.o rooster.o docent.o vak.o main.o

Opdr: $(OBJS)
	$(CC) $(OBJS) -o Rooster

standaard.o: standaard.cc standaard.h
	$(CC) $(CompileParms)  standaard.cc

rooster.o: rooster.cc standaard.h constantes.h docent.h vak.h rooster.h 
	$(CC) $(CompileParms)  rooster.cc

docent.o: docent.cc constantes.h docent.h
	$(CC) $(CompileParms)  docent.cc

vak.o: vak.cc constantes.h vak.h
	$(CC) $(CompileParms)  vak.cc

main.o: main.cc standaard.h rooster.h docent.h vak.h
	$(CC) $(CompileParms)  main.cc

