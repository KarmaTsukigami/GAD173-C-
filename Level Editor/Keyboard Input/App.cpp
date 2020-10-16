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

	//paddle
	paddleLength = 100.0f;
	paddleHeight = 30.0f;
	paddle.setSize(sf::Vector2f(paddleLength, paddleHeight));
	paddle.setPosition(window.getSize().x / 2, window.getSize().y * 0.9);
	paddle.setFillColor(sf::Color::Green);

	speed = 350;

	return true;
}

//App method definitons

void App::Update()
{
	//update
	// move Paddle left, frame rate independent
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (paddle.getPosition().x > 0)
		{
			paddle.move(-speed * deltaTime, 0);
		}
	}

	// move Paddle right, frame rate independent
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (paddle.getPosition().x < window.getSize().x - paddleLength)
		{
			paddle.move(speed * deltaTime, 0); //the defining feature which makes this framerate independent
		}
	}
}

void App::Draw()
{
	window.clear();
	window.setView(view);
	window.draw(ball);
	window.draw(paddle);
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