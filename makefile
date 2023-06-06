Nqueens: Nqueens.o
	g++ Nqueens.o -o Nqueens

Nqueens.o: Nqueens.cpp
	g++ -c Nqueens.cpp

clean:
	rm *.o
	rm Nqueens

run: Nqueens
	./Nqueens
