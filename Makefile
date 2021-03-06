IDIR = include
CC = gcc
CFLAGS = -I$(IDIR)
ODIR = obj
BINDIR = bin
SRCDIR = src


DEPS = $(widcard include/*.h)

_OBJ = $(patsubst src/%.c, %.o, $(wildcard src/*.c))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build: mkobj mkbin tic_tac_toe

mkobj:
	mkdir -p $(ODIR)

mkbin:
	mkdir -p $(BINDIR)

tic_tac_toe: $(OBJ)
	$(CC) -o $(BINDIR)/$@ $< $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 

