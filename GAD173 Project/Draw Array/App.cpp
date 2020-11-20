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

	myfile.close();

	// release the memory for the dynamically allocated array
	for (int i = 0; i < ROWS; ++i) {
		delete[] r[i];
		//deletes go into the destructor
	}

	delete[] r;

	for (int i = 0; i < ROWS; ++i) {
		delete[] b[i];
		delete[] c[i];
	}

	delete[] b;
	delete[] c;

}

bool App::Init()
{
	brickWidth = 60;
	brickHeight = 30;

	xGap = 10;
	yGap = 20;

	xEdgeGap = (window.getSize().x - COLS * brickWidth - (COLS - 1) * xGap) / 2;
	yEdgeGap = 40;

	/*
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			bricks[row][col].setSize(sf::Vector2f(brickWidth, brickHeight));
			bricks[row][col].setPosition(xEdgeGap + col * (brickWidth + xGap),
				yEdgeGap + row * (brickHeight + yGap));
		}
	}*/

	// dynamically allocate memory for an array of pointers to integers
	r = new int* [ROWS];

	// dynamically allocate memory for arrays of integers
	for (int i = 0; i < ROWS; ++i) {
		r[i] = new int[COLS];
	}

	// initialise and output the 2D array
	for (int i = 0; i < ROWS; ++i) {
		for (int j = 0; j < COLS; ++j) {
			r[i][j] = rand();
			std::cout << r[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	b = new sf::RectangleShape * [ROWS];
	c = new bool* [ROWS];

	for (int i = 0; i < ROWS; ++i) {
		b[i] = new sf::RectangleShape[COLS];
		c[i] = new bool[COLS];
	}


	myfile.open("brickPos.txt");

	//Setup the Array of Bricks
	for (int row = 0; row < ROWS; ++row)
	{

		for (int col = 0; col < COLS; ++col)
		{
			//For every Row and Column (or for every brick)
			b[row][col].setSize(sf::Vector2f(brickWidth, brickHeight));
			b[row][col].setPosition(xEdgeGap + col * (brickWidth + xGap), yEdgeGap + row * (brickHeight + yGap));

			myfile << b[row][col].getPosition().x << "\t" << b[row][col].getPosition().y << "\n";
		}

	}


	return true;
}

//App method definitons

void App::Update()
{
	
}

void App::Draw()
{
	//window.setView(view);
	window.clear();

	// draw the bricks
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			window.draw(b[row][col]);
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
		//deltaTime = clock.restart().asSeconds();  //framerate independent code to remove processor as variable in game speed
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		Update();
		Draw();
	}
}