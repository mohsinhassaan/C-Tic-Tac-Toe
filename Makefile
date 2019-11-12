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

tic_tac_toe: mkfolders
	$(CC) -o $(BINDIR)/$@ $(OBJ) $(CFLAGS) $(LIBS)

mkfolders:
	mkdir -p $(ODIR) $(BINDIR)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
