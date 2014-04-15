BIN := prog

CFLAGS   :=
CXXFLAGS := -std=c++11 -Wno-deprecated
LDFLAGS  := -lcvc4 -lgmp

SRCDIR := src
OBJDIR := obj
BINDIR := bin
INCDIR := include
LIBDIR := 

CC    := gcc
CXX   := g++
MKDIR := mkdir -p
RM    := rm -f
RMDIR := rm -rf

SRC := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*.c)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

rsubdir = $(foreach d,$1,$(shell find $d -type -d -print 2> /dev/null))
INCSUB := $(foreach i,$(INCDIR),$(call rsubdir,$i))

CLIBS  := $(patsubst %,-I%,$(INCDIR) $(INCSUB))
LDLIBS := $(patsubst %,-L%,$(LIBDIR))

.PHONY: all
all: $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): $(OBJ) | $(BINDIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS)
	
$(OBJ): | $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR) $(OBJDIR):
	$(MKDIR) $@

.PHONY: clean
clean:
	$(RMDIR) $(OBJDIR)

.PHONY: distclean
distclean: clean
	$(RMDIR) $(BINDIR)

.PHONY: dump
dump:
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(BIN)
	@echo $(INCDIR)
	@echo $(INCSUB)
	@echo $(CLIBS)
	@echo $(call rsubdir,lib)

#dist/prog: bin/main.o bin/Dictionary.o bin/Lemmatizator.o
#	g++ -o dist/prog -std=c++11 bin/main.o bin/Dictionary.o bin/Lemmatizator.o

#bin/Dictionary.o: src/classes/Lemmatizator.hpp   \
#                  src/classes/Dictionary.cpp     \
#                  src/classes/Dictionary.hpp
#	g++ -o bin/Dictionary.o -c src/classes/Dictionary.cpp -std=c++11	

#bin/Lemmatizator.o: src/classes/Lemmatizator.hpp \
#                    src/classes/Lemmatizator.cpp
#	g++ -o bin/Lemmatizator.o -c src/classes/Lemmatizator.cpp -std=c++11

#bin/main.o: src/classes/Lemmatizator.hpp         \
#            src/classes/Dictionary.hpp           \
#            src/main.cpp
#	g++ -o bin/main.o -c src/main.cpp -std=c++11

#dist/prog2: bin/main2.o bin/Matrix.o bin/CVC.o
#	g++ -o dist/prog2 -std=c++11 bin/main2.o bin/Matrix.o bin/CVC.o

#bin/main2.o: src/main2.cpp src/classes/Matrix.hpp src/classes/CVC.hpp
#	g++ -o bin/main2.o -c src/main2.cpp -std=c++11

#bin/Matrix.o: src/classes/Matrix.cpp src/classes/Matrix.hpp
#	g++ -o bin/Matrix.o -c src/classes/Matrix.cpp -std=c++11
#	
#bin/CVC.o: src/classes/CVC.cpp src/classes/CVC.hpp \
#              src/classes/Matrix.cpp src/classes/Matrix.hpp
#	g++ -o bin/CVC.o -c src/classes/CVC.cpp -std=c++11	

#dist/prog3: bin/main3.o bin/CVC.o bin/Matrix.o
#	g++ -o dist/prog3 -std=c++11 bin/main3.o bin/CVC.o bin/Matrix.o

#bin/main3.o: src/main3.cpp src/classes/CVC.hpp
#	g++ -o bin/main3.o -c src/main3.cpp -std=c++11

