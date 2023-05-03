CC_EXEC = g++
CC_FLASGS = -g

CC = ${CC_EXEC} ${CC_FLASGS}

SF_LIB = -lsfml-graphics -lsfml-window -lsfml-system

BUILD_DR = build


all: game.out


game.out: ${BUILD_DR}/main.o ${BUILD_DR}/Game.o ${BUILD_DR}/Map.o ${BUILD_DR}/Player.o ${BUILD_DR}/Person.o ${BUILD_DR}/Public_functions.o ${BUILD_DR}/Enemy.o ${BUILD_DR}/Die_hard.o ${BUILD_DR}/Shield_guy.o
	${CC} ${BUILD_DR}/main.o ${BUILD_DR}/Game.o ${BUILD_DR}/Map.o ${BUILD_DR}/Player.o ${BUILD_DR}/Person.o ${BUILD_DR}/Public_functions.o ${BUILD_DR}/Enemy.o ${BUILD_DR}/Die_hard.o  ${BUILD_DR}/Shield_guy.o ${SF_LIB} -o game


${BUILD_DR}/main.o: main.cpp Game.hpp
	${CC} -c main.cpp -o ${BUILD_DR}/main.o

${BUILD_DR}/Game.o: Game.cpp Map.hpp Player.hpp
	${CC} -c Game.cpp -o ${BUILD_DR}/Game.o

${BUILD_DR}/Enemy.o: Enemy.cpp Person.hpp 
	${CC} -c Enemy.cpp -o ${BUILD_DR}/Enemy.o
	
${BUILD_DR}/Map.o: Map.cpp Enemy.hpp Die_hard.hpp Shield_guy.hpp
	${CC} -c Map.cpp -o ${BUILD_DR}/Map.o

${BUILD_DR}/Player.o: Player.cpp Person.hpp
	${CC} -c Player.cpp -o ${BUILD_DR}/Player.o

${BUILD_DR}/Person.o: Person.cpp 
	${CC} -c Person.cpp -o ${BUILD_DR}/Person.o

${BUILD_DR}/Public_functions.o: Public_functions.cpp
	${CC} -c Public_functions.cpp -o ${BUILD_DR}/Public_functions.o

${BUILD_DR}/Enemy.o: Enemy.cpp Person.hpp 
	${CC} -c Enemy.cpp -o ${BUILD_DR}/Enemy.o

${BUILD_DR}/Die_hard.o: Die_hard.cpp Enemy.hpp
	${CC} -c Die_hard.cpp -o ${BUILD_DR}/Die_hard.o

${BUILD_DR}/Shield_guy.o: Shield_guy.cpp Enemy.hpp
	${CC} -c Shield_guy.cpp -o ${BUILD_DR}/Shield_guy.o

clean:
	rm -rf build/ && mkdir -p build