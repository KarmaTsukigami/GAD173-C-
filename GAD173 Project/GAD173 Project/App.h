#pragma once

#include "SFML/graphics.hpp"
#include "SFML/Audio.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
using namespace std;

//global variables
//declare an array of bricks
const int COLS = 7;
const int ROWS = 3;

//array of save slots
const int totalSaves = 2;

//array of menu strings
const int menuItems = 3;

class App
{
private:
	sf::Event event;
	sf::Clock clock;
	sf::RenderWindow window;
	sf::View view;

	sf::Clock gameClock;
	sf::Clock powerupClock;
	sf::Clock powerupTimer;

	//other data members

	//bricks
	//sf::RectangleShape brick[rowValue][colValue];
	//sf::RectangleShape** b;
	sf::Sprite** s;
	//bool** c;
	bool** t; //texture's collidable bool pointer as a pair with s
	int rowValue;
	int colValue;
	int customRow;
	int customCol;
	int defineRow;
	int defineCol;
	bool customValue;

	sf::CircleShape ball;
	//bool collidable[ROWS][COLS];

	//paddle specifications
	//sf::RectangleShape paddle;
	float paddleWidth;
	float paddleHeight;
	bool paddleCollidable;

	//ball specifications
	float ballRadius;
	bool isHit;

	//time
	float deltaTime;

	//speed variables
	float speed;
	
	int xMultiplier;
	int xSpeed;
	int ySpeed;

	//brick array specifications
	float pad;
	float brickWidth;
	float brickHeight;

	//text related
	int bricksDestroyed;
	int totalBricks;
	bool gameWin;

	sf::Font font;
	sf::Text gameOver;
	sf::Text wonGame;
	sf::Text score;
	sf::Text menuText[menuItems];
	sf::Text continueText;
	sf::Text livesCount;
	sf::Color textColour; 

	//names corrlate to text to be drawn
	sf::Text save[totalSaves];
	sf::Text load[totalSaves];
	sf::Text slots[totalSaves];
	int iCounter;

	//gaps
	float xEdgeGap;
	float xGap;
	float yEdgeGap;
	float yGap;

	//Writing and Reading
	ofstream colrowWrite;
	ifstream colrowRead;
	ofstream readmeWrite;
	ofstream customOne;
	ifstream customOneRead;

	//Buttons
	sf::Vector2i localPosition;
	sf::RectangleShape startButton;
	sf::RectangleShape customButton;
	sf::RectangleShape exitButton;
	sf::RectangleShape menuButton;
	sf::RectangleShape continueButton;
	sf::Color buttonColour;
	float buttonWidth;
	float buttonHeight;
	bool startPressed;
	bool inMenu;
	bool customMenu;
	bool paused;
	bool livesLost;

	//Background
	sf::Image backgroundImage;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	//Brick Texture
	sf::Texture texture;

	//Paddle Texture
	sf::Texture paddleTexture;
	sf::Sprite paddleSprite;

	//Leaf Texture
	sf::Texture leafTexture;
	sf::IntRect rect;
	sf::Sprite leafSprite;

	float leafWidth;
	float leafHeight;
	float leafSpeed;

	//Powerups
	sf::Texture powerupLife;
	sf::Texture powerupPaddle;
	sf::Sprite powerupLifeSprite;
	sf::Sprite powerupPaddleSprite;

	bool enlargedPaddle;
	bool powerupSpawned;
	bool lifeSpawned;
	bool paddleSpawned;

	float powerupWidth;
	float powerupHeight;
	float powerupSpeed;
	int powerupChoice;
	int spawnLocation;

	//Saving and Loading
	sf::RectangleShape saves[totalSaves];
	sf::RectangleShape loads[totalSaves];
	sf::RectangleShape saveSlots[totalSaves];
	bool restartInit;
	bool restarted;

	//Audio
	sf::SoundBuffer brickBuffer;
	sf::Sound brickAudio;
	sf::SoundBuffer buttonBuffer;
	sf::Sound buttonAudio;
	sf::SoundBuffer paddleBuffer;
	sf::Sound paddleAudio;
	sf::SoundBuffer wallBuffer;
	sf::Sound wallAudio;
	sf::SoundBuffer leafBuffer;
	sf::Sound leafAudio;
	sf::SoundBuffer powerupBuffer;
	sf::Sound powerupAudio;

	//other private methods
	int lives;
	bool livesToggle;
	bool livesWatch;

	/*
	//testing for level editor
	int customRowOne;
	int customRowTwo;
	int customRowThree;
	bool customRowValues;
	*/


public:
	App(const char* title, int screenWidth, int screenHeight, int screenBpp);

	~App();

	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	void Run();
};
