CC_EXEC = g++
CC_FLASGS = -g

CC = ${CC_EXEC} ${CC_FLASGS}

SF_LIB = -lsfml-graphics -lsfml-window -lsfml-system

BUILD_DR = build


all: game.out


game.out: ${BUILD_DR}/main.o ${BUILD_DR}/Game.o
	${CC} ${BUILD_DR}/main.o ${BUILD_DR}/Game.o ${SF_LIB} -o game


${BUILD_DR}/main.o: main.cpp
	${CC} -c main.cpp -o ${BUILD_DR}/main.o

${BUILD_DR}/Game.o: Game.cpp
	${CC} -c Game.cpp -o ${BUILD_DR}/Game.o

clean:
	rm -rf build/ && mkdir -p build