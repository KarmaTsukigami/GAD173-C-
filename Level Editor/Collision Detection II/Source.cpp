#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
	srand(time(NULL));

	sf::Clock Clock;

	sf::RenderWindow Window(sf::VideoMode(800, 600), "SFML works!");

	// ball specifications
	float radius = 25;
	sf::CircleShape Ball(25.f);
	Ball.setPosition(25, 25);

	// random speed
	float xSpeed = rand() % 100 + 400;
	float ySpeed = rand() % 100 + 400;

	// a tolerance value to take into account
	// that an object may move after a collision is detected
	float pad = 20;


	// brick specifications
	float brickWidth = 200;
	float brickHeight = 100;
	sf::RectangleShape Brick(sf::Vector2f(brickWidth, brickHeight));
	Brick.setPosition(400, 0);

	// check if brick has been hit
	bool collidable = true;


	while (Window.isOpen())
	{
		// measure time between frames
		float deltaTime = Clock.restart().asSeconds();

		// handle window events
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}


		// left border collision detection
		if (Ball.getPosition().x <= 0)
		{
			xSpeed = -xSpeed;
		}

		// right border collision detection
		if (Ball.getPosition().x >= Window.getSize().x - 2 * radius)
		{
			xSpeed = -xSpeed;
		}

		// top border collision detection
		if (Ball.getPosition().y <= 0)
		{
			ySpeed = -ySpeed;
		}

		// bottom border collision detection
		if (Ball.getPosition().y >= Window.getSize().y - 2 * radius)
		{
			ySpeed = -ySpeed;
		}

		// detect collision with collidable brick 
		// i.e. if brick has not been hit
		if (Ball.getGlobalBounds().intersects(Brick.getGlobalBounds()) && collidable)
		{
			// destroy the brick
			collidable = false;

			// left or right border
			if (
				Ball.getPosition().x > Brick.getPosition().x + brickWidth - pad ||
				Ball.getPosition().x + 2 * radius < Brick.getPosition().x + pad
				)
			{
				// reset position

				// reverse x speed
				xSpeed = -xSpeed;
			}

			// top or bottom border
			if (
				Ball.getPosition().y + 2 * radius < Brick.getPosition().y + pad ||
				Ball.getPosition().y > Brick.getPosition().y + brickHeight - pad
				)
			{
				// reset position

				// reverse y speed
				ySpeed = -ySpeed;
			}

		}


		// move the ball 
		Ball.move(xSpeed * deltaTime, ySpeed * deltaTime);


		// clear the window
		Window.clear();

		// draw the brick
		Window.draw(Ball);

		// only draw those bricks that have not been hit
		if (collidable)
		{
			Window.draw(Brick);
		}

		// display all drawn objects
		Window.display();
	}

	return 0;
}