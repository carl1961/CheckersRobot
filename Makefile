cc = g++ -std=c++17
cflag = -pthread -lwiringPi

all: clean build run

clean:
	clear
	find . -type f -name "*.o" -delete

build:	GRBLTranslator/GRBLTranslator.o CheckerMove/CheckerMove.o BoardPosition/BoardPosition.o \
		MoveQueue/MoveQueue.o CheckersRobotInterface/CheckersRobotInterface.o general/general.o
	$(cc) main.cpp  GRBLTranslator/GRBLTranslator.o CheckerMove/CheckerMove.o BoardPosition/BoardPosition.o \
	general/general.o CheckersRobotInterface/CheckersRobotInterface.o MoveQueue/MoveQueue.o -o api $(cflag)

translator:
	$(cc) -c GRBLTranslator/GRBLTranslator.cpp -o GRBLTranslator/GRBLTranslator.o

CheckersMove:
	$(cc) -c CheckerMove/CheckerMove.cpp -o CheckerMove/CheckerMove.o

BoardPosition:
	$(cc) -c BoardPosition/BoardPosition.cpp -o BoardPosition/BoardPosition.o

general:
	$(cc) -c general/general.cpp -o general/general.o

CheckersRobotInterface:
	$(cc) -c CheckersRobotInterface/CheckersRobotInterface.cpp -o CheckersRobotInterface/CheckersRobotInterface.o

MoveQueue:
	$(cc) -c MoveQueue/MoveQueue.cpp -o MoveQueue/MoveQueue.o

run:
	./api
