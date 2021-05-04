all: game

game: main.c card_LList.c gameObjects.c gameFunctions.c
	gcc -Wall -std=c99 -o game main.c card_LList.c gameObjects.c gameFunctions.c

clean:
	rm -f game
