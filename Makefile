TARGETS = hello
CC = g++
FLAGS = -pedentic-error -std=c++11


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

utilities.o: utilities.cpp utilities.h
	$(CC) $(FLAGS) -c utilities.cpp