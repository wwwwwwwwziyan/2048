#include "Game.h"
#include <ctime>

int main() {
	srand(unsigned int(time(0)));
	Game g(4);
	g.play();
}