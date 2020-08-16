#include "game.h"
#include <Windows.h>

//½ûÖ¹¿ØÖÆÌ¨
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

int main()
{
	Game game;
	game.start();
	return 0;
}
