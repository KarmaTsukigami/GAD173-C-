#pragma once

#include "SFML/graphics.hpp"


//global variables
//declare an array of bricks
const int COLS = 7;
const int ROWS = 3;

class App
{
private:
	sf::Event event;
	sf::Clock clock;
	sf::RenderWindow window;
	sf::View view;

	//other data members
	sf::RectangleShape paddle;
	sf::RectangleShape brick[ROWS][COLS];
	sf::CircleShape ball;
	bool collidable[ROWS][COLS];

	//paddle specifications
	float paddleLength;
	float paddleHeight;
	bool paddleCollidable;

	//ball specifications
	float ballRadius;
	bool isHit;

	//time
	float deltaTime;

	//speed variables
	float speed;
	
	int xSpeed;
	int ySpeed;

	//brick array specifications
	float pad;
	float brickWidth;
	float brickHeight;


	//gaps
	float xEdgeGap;
	float xGap;
	float yEdgeGap;
	float yGap;

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
