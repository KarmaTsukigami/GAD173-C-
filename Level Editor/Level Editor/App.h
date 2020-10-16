#pragma once

#include "SFML/graphics.hpp"

class App
{
private:
	sf::Event		event;
	sf::View		view;
	sf::RenderWindow		window;
	
	//other data members here
	float	radius;
	sf::CircleShape	circle;

public:
	App(const char* title, int screenWidth, int screenHeight, int screenBpp);

	~App();

	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	void Run();
};

//end of App class definition