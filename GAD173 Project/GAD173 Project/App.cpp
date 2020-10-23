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
	ballRadius = 30.0f;
	ball.setRadius(ballRadius);
	ball.setPosition((window.getSize().x / 2) - ballRadius, (window.getSize().y / 2) - ballRadius);
	isHit = false;

	//paddle
	paddleLength = 150.0f;
	paddleHeight = 20.0f;
	paddle.setSize(sf::Vector2f(paddleLength, paddleHeight));
	paddle.setPosition(window.getSize().x / 2, window.getSize().y * 0.9);
	paddle.setFillColor(sf::Color::Magenta);
	paddleCollidable = true;

	//speed
	speed = 350;
	xSpeed = rand() % 100 + 300;
	ySpeed = -(rand() % 100 + 300);

	//bricks
	brickHeight = 30;
	brickWidth = 60;
	

	//gaps
	xGap = 10;
	xEdgeGap = (window.getSize().x - COLS * brickWidth - (COLS - 1) * xGap) / 2;;
	yGap = 20;
	yEdgeGap = 40;


	//collision
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			brick[row][col].setSize(sf::Vector2f(brickWidth, brickHeight));
			brick[row][col].setPosition(xEdgeGap + col * (brickWidth + xGap), yEdgeGap + row * (brickHeight + yGap));
			collidable[row][col] = true;
			brick[row][col].setFillColor(sf::Color::Red);
		}
	}
	
	

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

	// left border collision detection
	if (ball.getPosition().x <= 0)
	{
		xSpeed = -xSpeed;
	}

	// right border collision detection
	if (ball.getPosition().x >= window.getSize().x - 2 * ballRadius)
	{
		xSpeed = -xSpeed;
	}

	// top border collision detection
	if (ball.getPosition().y <= 0)
	{
		ySpeed = -ySpeed;
	}

	// bottom border collision detection
	if (ball.getPosition().y >= window.getSize().y - 2 * ballRadius)
	{
		//ySpeed = -ySpeed;

		//ball.setPosition((window.getSize().x / 2) - ballRadius, (window.getSize().y / 2) - ballRadius);
		ySpeed = 0;
		xSpeed = 0;
	}
	
	if (ball.getGlobalBounds().intersects(paddle.getGlobalBounds()) && paddleCollidable)
	{
		ySpeed = -ySpeed;
	}

	if (isHit == true)
	{
		xSpeed = -xSpeed;
		ySpeed = -ySpeed;
		isHit = false;
	}
	// detect collision with collidable brick 
	// i.e. if brick has not been hit

	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (ball.getGlobalBounds().intersects(brick[row][col].getGlobalBounds()) && collidable[row][col] == true)
			{
				// destroy the brick
				collidable[row][col] = false;
				isHit = true;

				//The below code didn't work for me, so I wrote it differently.
				/*
				// left or right border
				if (ball.getPosition().x > brick[row][col].getPosition().x + brickWidth - pad ||
					ball.getPosition().x + 2 * ballRadius < brick[row][col].getPosition().x + pad)
				{
					// reset position

					// reverse x speed
					xSpeed = -xSpeed;
				}

				// top or bottom border
				if (ball.getPosition().y + 2 * ballRadius < brick[row][col].getPosition().y + pad ||
					ball.getPosition().y > brick[row][col].getPosition().y + brickHeight - pad)
				{
					// reset position

					// reverse y speed
					ySpeed = -ySpeed;
				}
				*/

			}
		}
	}
	
	// move the ball 
	ball.move(xSpeed * deltaTime, ySpeed * deltaTime);
}

void App::Draw()
{
	window.clear();
	window.setView(view);
	window.draw(ball);
	window.draw(paddle);
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (collidable[row][col])
			{
				window.draw(brick[row][col]);
			}
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
		deltaTime = clock.restart().asSeconds();  //framerate independent code to remove processor as variable in game speed
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			HandleEvents();
		}
		
		Update();
		Draw();
	}
}