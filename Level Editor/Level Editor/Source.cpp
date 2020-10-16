#include "App.h"

int main()
{
	App game("Level Editor", 800, 600, 32);

	if (!game.Init())
	{
		printf("Game could not be started");
		return 1;
	}

	else
	{
		game.Run();
	}
	return 0;
}

//~ is a deconstructor
// the framework needs to be split up into initialisation and definition