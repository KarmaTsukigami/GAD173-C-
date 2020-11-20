#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>

using namespace std;

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
	sf::RectangleShape** b;
	bool** c;
	int** r;
	bool** col;


	ofstream myfile;
	//int MethodName(float z);
};

