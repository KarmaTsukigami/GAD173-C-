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
	//initialise App data members
	radius = 100.0f;
	circle.setRadius(radius);

	circle.setPosition((window.getSize().x / 2) - radius, (window.getSize().y / 2) - radius);

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
	window.draw(circle);
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
		while (window.pollEvent(event))
		{
			HandleEvents();
		}
		Update();
		Draw();
	}
}