CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: all
	./cardtest1 &> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov cardtest1.c -b >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	gcov cardtest2.c -b >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	gcov cardtest3.c -b >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	gcov cardtest4.c -b >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	gcov unittest1.c -b >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	gcov unittest2.c -b >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	gcov unittest3.c -b >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	gcov unittest4.c -b >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	gcov dominion.c -b >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

randomtestresults.out: all
	./randomtestadventurer &> randomtestresults.out
	./randomtestcard1 >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	gcov randomtestadventurer.c -b >> randomtestresults.out
	cat randomtestadventurer.c.gcov >> randomtestresults.out
	gcov randomtestcard1.c -b >> randomtestresults.out
	cat randomtestcard1.c.gcov >> randomtestresults.out
	gcov randomtestcard2.c -b >> randomtestresults.out
	cat randomtestcard2.c.gcov >> randomtestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestadventurer randomtestcard1 randomtestcard2

clean:
	rm -f *.o playdom.exe playdom player player.exe *.exe *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe badTestDrawCard badTestDrawCard.exe cardtest1 cardtest2 cardtest3 cardtest4 unittest1 unittest2 unittest3 unittest4 randomtestcard1 randomtestcard2 randomtestadventurer
