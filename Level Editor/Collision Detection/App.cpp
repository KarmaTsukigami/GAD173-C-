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
	//ball
	ballRadius = 50.0f;
	ball.setRadius(ballRadius);
	ball.setPosition((window.getSize().x / 2) - ballRadius, (window.getSize().y / 2) - ballRadius);

	//brick
	brickLength = 50.0f;
	brickHeight = 100.0f;
	brick.setSize(sf::Vector2f(brickLength, brickHeight));
	brick.setPosition(500, 0);
	brick.setFillColor(sf::Color::Green);

	xSpeed = 100;

	return true;
}

//App method definitons

void App::Update()
{
	//update
	
}

void App::Draw()
{
	window.clear();
	window.setView(view);
	window.draw(ball);
	window.draw(brick);
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
		deltaTime = clock.restart().asSeconds();  //framerate independent code to remove processor as variable in game speed
		while (window.pollEvent(event))
		{
			HandleEvents();
		}
		Update();
		Draw();
	}
}