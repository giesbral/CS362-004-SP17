CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.c rngs.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest1.c rngs.c -o unittest1 -lm -g

	./unittest1 &> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest2.c rngs.c -o unittest2 -lm -g

	./unittest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest3.c rngs.c -o unittest3 -lm -g

	./unittest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c unittest4.c rngs.c -o unittest4 -lm -g

	./unittest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest1.c rngs.c -o cardtest1 -lm -g

	./cardtest1 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest2.c rngs.c -o cardtest2 -lm -g

	./cardtest2 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest3.c rngs.c -o cardtest3 -lm -g

	./cardtest3 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c cardtest4.c rngs.c -o cardtest4 -lm -g

	./cardtest4 >> unittestresults.out
	gcov -b -f dominion.c >> unittestresults.out

randomtests: randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.c rngs.c
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard1.c rngs.c -o randomtestcard1 -lm -g
	./randomtestcard1 &> randomtests1.out
	gcov -b -f dominion.o >> randomtests1.out

	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard2.c rngs.c -o randomtestcard2 -lm -g
	./randomtestcard2 &> randomtestsadventurer.out
	gcov -b -f dominion.o >> randomtestadventurer.out

	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.c randomtestcard3.c rngs.c -o randomtestcard3 -lm -g
	./randomtestcard3 &> randomtests2.out
	gcov -b -f dominion.o >> randomtests2.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out randomtestcard1 randomtestcard2 randomtestcard3 randomtests.out *.gcov *.gcda *.gcno *.so
