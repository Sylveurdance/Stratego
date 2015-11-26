LIBS=-lsfml-graphics -lsfml-window -lsfml-system
CXX := g++

all: stratego

%.o: %.cpp
	$(CXX) -c $< -o $@

%.o: %.h
	$(CXX) -c $< -o $@

stratego: Position.o Piece.o Box.o Board.o GUI.o main.o
	@echo "** Building the game"
	$(CXX) -o stratego Position.o Piece.o Box.o Board.o GUI.o main.o $(LIBS)

clean:
	@echo "** Removing object files..."
	rm -f *.o

install:
	@echo '** Installing...'
	cp stratego /usr/bin/

uninstall:
	@echo '** Uninstalling...'
	$(RM) /usr/bin/stratego

