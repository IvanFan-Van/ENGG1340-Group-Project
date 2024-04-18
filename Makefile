CC = g++
FLAGS = -pedantic-errors -std=c++11

template: ./build/game.o

./build/game.o: ./src/battleship/game.cpp ./include/battleship/board.h ./include/battleship/constants.h ./include/battleship/utilities.h
	$(CC) $(FLAGS) -I ./include -c $< -o $@

./build/board.o: ./src/battleship/board.cpp
	$(CC) $(FLAGS) -I ./include -c $< -o $@

.PHONY: clean
clean:
	rm -f *.o *.a *.so *.out *.exe *.dll *.dylib *.app
	rm -rf *.dSYM
	rm -f $(TARGETS)
	rm -f $(TARGETS:%=%.exe)
	rm -f $(TARGETS:%=%.dll)
	rm -f $(TARGETS:%=%.dylib)
	rm -f $(TARGETS:%=%.app)
	rm -f $(TARGETS:%=%.out)
	rm -f $(TARGETS:%=%.dSYM)
	rm -f $(TARGETS:%=%.o)
	rm -f $(TARGETS:%=%.a)
	rm -f $(TARGETS:%=%.so)
	rm -f $(TARGETS:%=%.d)