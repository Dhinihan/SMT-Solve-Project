all: dist/prog 

dist/prog: bin/main.o bin/Dictionary.o bin/Lemmatizator.o
	g++ -o dist/prog -std=c++11 bin/main.o bin/Dictionary.o bin/Lemmatizator.o

bin/Dictionary.o: src/classes/Lemmatizator.hpp   \
                  src/classes/Dictionary.cpp     \
                  src/classes/Dictionary.hpp
	g++ -o bin/Dictionary.o -c src/classes/Dictionary.cpp -std=c++11	

bin/Lemmatizator.o: src/classes/Lemmatizator.hpp \
                    src/classes/Lemmatizator.cpp
	g++ -o bin/Lemmatizator.o -c src/classes/Lemmatizator.cpp -std=c++11

bin/main.o: src/classes/Lemmatizator.hpp         \
            src/classes/Dictionary.hpp           \
            src/main.cpp
	g++ -o bin/main.o -c src/main.cpp -std=c++11

clean:
	rm -rf bin/*

distclean:
	rm -rf dist/*

mrproper: clean
	rm -rf tudo
