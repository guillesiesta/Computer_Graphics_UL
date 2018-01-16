CC = clang++
OPT = -O2
LDD = -lSDL -lGL -lGLU -lglut
FILENAME = empty

all : $(FILENAME).cpp
	$(CC) $(OPT) $< $(LDD) -o $(FILENAME)

# PHONY rule
.PHONY: all
