    BIN := prog

CFLAGS   :=
CXXFLAGS := -std=c++11 -Wno-deprecated
LDFLAGS  := -lCVC4solver -lcvc4 -lgmp -larmadillo

SRCDIR := src
OBJDIR := obj
BINDIR := bin
INCDIR := include
LIBDIR := lib
SHRDIR := shr

RPATH := -Wl,-rpath=./$(LIBDIR)/

CC    := gcc
CXX   := g++
MKDIR := mkdir -p
RM    := rm -f
RMDIR := rm -rf

SRC := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*.c)
SHR := $(wildcard $(SHRDIR)/*.cpp) $(wildcard $(SHRDIR)/*.c)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
LIB := $(patsubst $(SHRDIR)/%.cpp,$(LIBDIR)/lib%.so,$(SHR))
LIO := $(patsubst $(SHRDIR)/%.cpp,$(LIBDIR)/%.o,$(SHR))

rsubdir = $(foreach d,$1,$(shell find $d -type -d -print 2> /dev/null))
INCSUB := $(foreach i,$(INCDIR),$(call rsubdir,$i))

CLIBS  := $(patsubst %,-I%,$(INCDIR) $(INCSUB))
LDLIBS := $(patsubst %,-L%,./$(LIBDIR)/)

.PHONY: all
all: $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): $(OBJ) $(LIO) $(LIB) | $(BINDIR)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS) $(LDLIBS) $(RPATH)
	
$(OBJ): | $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIO): | $(LIBDIR)

$(LIBDIR)/%.o: $(SHRDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(LIBDIR)/lib%.so: $(LIBDIR)/%.o
	$(CXX) -shared -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR) $(OBJDIR) $(LIBDIR):
	$(MKDIR) $@

.PHONY: clean
clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(LIBDIR)

.PHONY: distclean
distclean: clean
	$(RMDIR) $(BINDIR)

.PHONY: dump
dump:
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(BIN)
	@echo $(SHR)
	@echo $(LIB)
	@echo $(LIO)
	@echo $(INCDIR)
	@echo $(INCSUB)
	@echo $(CLIBS)
	@echo $(call rsubdir,lib)
