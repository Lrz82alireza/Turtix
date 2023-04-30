CC_EXEC = g++
CC_FLASGS = -g

CC = ${CC_EXEC} ${CC_FLASGS}

SF_LIB = -lsfml-graphics -lsfml-window -lsfml-system

BUILD_DR = build


all: game.out


game.out: ${BUILD_DR}/main.o ${BUILD_DR}/Game.o ${BUILD_DR}/Map.o ${BUILD_DR}/Player.o
	${CC} ${BUILD_DR}/main.o ${BUILD_DR}/Game.o ${BUILD_DR}/Map.o ${BUILD_DR}/Player.o ${SF_LIB} -o game


${BUILD_DR}/main.o: main.cpp
	${CC} -c main.cpp -o ${BUILD_DR}/main.o

${BUILD_DR}/Game.o: Game.cpp Map.hpp Player.hpp
	${CC} -c Game.cpp -o ${BUILD_DR}/Game.o

${BUILD_DR}/Map.o: Map.cpp
	${CC} -c Map.cpp -o ${BUILD_DR}/Map.o

${BUILD_DR}/Player.o: Player.cpp
	${CC} -c Player.cpp -o ${BUILD_DR}/Player.o

clean:
	rm -rf build/ && mkdir -p build