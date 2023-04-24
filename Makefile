CC_EXEC = g++
CC_FLASGS = -g

CC = ${CC_EXEC} ${CC_FLASGS}

SF_LIB = -lsfml-graphics -lsfml-window -lsfml-system

BUILD_DR = build


all: game


game: ${BUILD_DR}/main.o 
	${CC} ${BUILD_DR}/main.o ${SF_LIB} -o game


${BUILD_DR}/main.o: main.cpp
	${CC} -c main.cpp -o ${BUILD_DR}/main.o


clean:
	rm -rf build/ && mkdir -p build