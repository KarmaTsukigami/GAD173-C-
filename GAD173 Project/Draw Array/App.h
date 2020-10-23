#pragma once
#include "SFML/Graphics.hpp"

const int ROWS = 3;
const int COLS = 7;

class App
{
public:
	App(const char* title, int screenWidth, int screenHeight, int screenBpp);


	~App();

	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	void Run();

private:

	sf::Event event;
	sf::RenderWindow window;
	sf::View view;

	float brickWidth;
	float brickHeight;

	float xGap;
	float yGap;

	float xEdgeGap;
	float yEdgeGap;

	// declare a 2D array of bricks
	sf::RectangleShape bricks[ROWS][COLS];
};
