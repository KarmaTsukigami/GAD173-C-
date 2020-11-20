#include <SFML/Graphics.hpp>
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

// TASK: create three rows of bricks 
// with vertical and horizontal separation, using one 2D array

