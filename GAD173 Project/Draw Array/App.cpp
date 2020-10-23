#include "App.h"

//constuctor
App::App(const char* title, int screenWidth, int screenHeight, int screenBpp)
{
	window.create(sf::VideoMode(screenWidth, screenHeight, screenBpp), title);
	window.setFramerateLimit(0);
	view = window.getDefaultView();
}

//destructor
App::~App()
{
	//release memory
}

bool App::Init()
{
	brickWidth = 60;
	brickHeight = 30;

	xGap = 10;
	yGap = 20;

	xEdgeGap = (window.getSize().x - COLS * brickWidth - (COLS - 1) * xGap) / 2;
	yEdgeGap = 40;

	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			bricks[row][col].setSize(sf::Vector2f(brickWidth, brickHeight));
			bricks[row][col].setPosition(xEdgeGap + col * (brickWidth + xGap),
				yEdgeGap + row * (brickHeight + yGap));
		}
	}

	return true;
}

//App method definitons

void App::Update()
{
	
}

void App::Draw()
{
	//window.setView(view);
	window.clear();

	// draw the bricks
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			window.draw(bricks[row][col]);
		}
	}
	window.display();
}


void App::HandleEvents()
{
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}

	//other keyboard, mouse events
}

void App::Run()
{
	while (window.isOpen())
	{
		//deltaTime = clock.restart().asSeconds();  //framerate independent code to remove processor as variable in game speed
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Update();
		Draw();
	}
}