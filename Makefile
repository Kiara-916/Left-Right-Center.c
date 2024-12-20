HEADERS=strings.h game.h randi.h

lcr: lcr.o game.o randi.o
	clang lcr.o game.o randi.o -o lcr

lcr.o: lcr.c $(HEADERS)
	clang -c lcr.c

randi.o: randi.c $(HEADERS)
	clang -c randi.c
game.o: game.c $(HEADERS)
	clang -c game.c
clean:
	rm -f lcr.o game.o randi.o lcr
