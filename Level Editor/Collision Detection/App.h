#pragma once

#include <SFML/Graphics.hpp>

class App
{
private:
	sf::Event event;
	sf::Clock clock;
	sf::View view;
	sf::RenderWindow window;
	

	//other data members
	sf::CircleShape ball;
	float ballRadius;

	sf::RectangleShape brick;
	float brickLength;
	float brickHeight;
	
	float deltaTime;
	float xSpeed;

public:
	App(const char* title, int screenWidth, int screenHeight, int screenBpp);

	~App();

	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	void Run();

}