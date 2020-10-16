#pragma once

#include "SFML/graphics.hpp"

class App
{
private:
	sf::Event event;
	sf::Clock clock;
	sf::RenderWindow window;
	sf::View view;
	
	//other data members
	sf::RectangleShape paddle;
	sf::CircleShape ball;

	float paddleLength;
	float paddleHeight;
	float ballRadius;
	float deltaTime;
	float speed;

	//other private methods

public:
	App(const char* title, int screenWidth, int screenHeight, int screenBpp);

	~App();

	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	void Run();
};