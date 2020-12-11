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
	
	//release memory: brickPos.txt closing
	//writeFile.close();
	//readFile.close();
	colrowRead.close();
	colrowWrite.close();

	//release memory: pointer array for bricks
	for (int i = 0; i < rowValue; ++i) {
		delete[] s[i];
		delete[] t[i];
	}

	delete[] s;
	delete[] t;
	
	/*
	//release memory: pointer array for menu
	delete[] menuText;

	//release memory: pointer array for saves
	delete[] save;
	delete[] saves;
	delete[] load;
	delete[] loads;
	delete[] slots;
	delete[] saveSlots;
	*/
}

bool App::Init()
{
	srand(time(NULL));

	//initialise with writing to and reading files
	if (customValue != true && restarted != true) {
		customValue = false;
		restarted = false;
		colrowWrite.open("colrowValues.txt");
		colrowWrite << ROWS << "\t" << COLS << "\t" << 0 << "\t" << 0 << "\n";
		colrowWrite.close();
	}
	else if (customValue == true) {
		colrowRead.open("colrowValues.txt");
		// open
		if (colrowRead.is_open()) {//start method, its initialising and only needs to be called in the first frame
			// read from file
			while (!colrowRead.eof()) {
				// only works with tab separated values
				colrowRead >> customRow >> customCol >> rowValue >> colValue;

				//cout << rowValue << "\t" << colValue << endl;

				colrowRead.close();
			}
		}
		else {
			cout << "Unable to open file";
		}

	}

	if (customValue == false) {
		colrowRead.open("colrowValues.txt");
		// open
		if (colrowRead.is_open()) {//start method, its initialising and only needs to be called in the first frame
			// read from file
			while (!colrowRead.eof()) {
				// only works with tab separated values
				colrowRead >> rowValue >> colValue >> customRow >> customCol;

				//cout << rowValue << "\t" << colValue << endl;

				colrowRead.close();
			}
		}
		else {
			cout << "Unable to open file";
		}
	}

	/*
	if (customValue == true && customRowValues == true) {
		customOneRead.open("customRows.txt");
		// open
		if (customOneRead.is_open()) {//start method, its initialising and only needs to be called in the first frame
			// read from file
			while (!customOneRead.eof()) {
				// only works with tab separated values
				customOneRead >> customRowOne >> customRowTwo >> customRowThree;

				//cout << rowValue << "\t" << colValue << endl;

				customOneRead.close();
			}
		}
		else {
			cout << "Unable to open file";
		}
	}*/
	
	//Init Reset
	restartInit = false;

	//ball
	ballRadius = 30.0f;
	ball.setRadius(ballRadius);
	ball.setPosition((window.getSize().x / 2) + ballRadius, (window.getSize().y / 2) + ballRadius);
	ball.setFillColor(sf::Color::Red);
	isHit = false;

	//paddle
	paddleWidth = 150.0f;
	paddleHeight = 20.0f;
	//paddle.setSize(sf::Vector2f(paddleLength, paddleHeight));
	//paddle.setPosition(window.getSize().x / 2, window.getSize().y * 0.9);
	//paddle.setFillColor(sf::Color::Magenta);
	paddleCollidable = true;

	//speed
	xMultiplier = 2 * (rand() % 2) - 1;
	speed = 350;
	xSpeed = xMultiplier * (rand() % 100 + 300);
	ySpeed = -(rand() % 100 + 300);

	//bricks
	brickHeight = 40;
	brickWidth = 80;
	bricksDestroyed = 0;
	totalBricks = 0;

	//gaps
	xGap = 20;
	xEdgeGap = (window.getSize().x - colValue * brickWidth - (colValue - 1) * xGap) / 2;;
	yGap = 30;
	yEdgeGap = 40;

	//buttons
	buttonWidth = 100.0f;
	buttonHeight = 50.0f;
	buttonColour = sf::Color::White;
	startPressed = false;
	inMenu = true;
	paused = false;

	startButton.setSize(sf::Vector2f(buttonWidth * 1.5, buttonHeight));
	startButton.setPosition(window.getSize().x - 200, yEdgeGap);
	startButton.setFillColor(buttonColour);

	customButton.setSize(sf::Vector2f(buttonWidth * 1.5, buttonHeight));
	customButton.setPosition(window.getSize().x - 200, yEdgeGap + buttonHeight + yGap);
	customButton.setFillColor(buttonColour);

	exitButton.setSize(sf::Vector2f(buttonWidth * 1.5, buttonHeight));
	exitButton.setPosition(window.getSize().x - 200, yEdgeGap + 2 * (buttonHeight + yGap));
	exitButton.setFillColor(buttonColour);

	continueButton.setSize(sf::Vector2f(buttonWidth * 1.5, buttonHeight));
	continueButton.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	continueButton.setFillColor(buttonColour);

	menuButton.setSize(sf::Vector2f(buttonWidth * 2, buttonHeight));
	menuButton.setPosition(window.getSize().x / 2, window.getSize().y / 2);
	menuButton.setFillColor(buttonColour);

	//lives
	lives = 3;
	livesLost = false;
	livesToggle = false;
	livesWatch = false;

	//Winning the Game
	gameWin = false;

	//text
	if (!font.loadFromFile("arial.ttf")) {
		std::cout << "cannot load font" << std::endl;
	}
	gameOver.setFont(font);
	score.setFont(font);
	continueText.setFont(font);
	livesCount.setFont(font);
	wonGame.setFont(font);
	
	textColour = sf::Color(238, 130, 238, 255);
	//textColour = sf::Color::Red;

	//text assign: gameOver
	gameOver.setString("Game Over");
	gameOver.setPosition((window.getSize().x / 2), (window.getSize().y / 2));
	gameOver.setFillColor(textColour);
	gameOver.setCharacterSize(30);

	//text assign: score
	score.setPosition((window.getSize().x / 2), 0);
	score.setFillColor(textColour);

	//text assign: continue
	continueText.setString("Continue");
	continueText.setPosition((window.getSize().x / 2), (window.getSize().y / 2));
	continueText.setFillColor(textColour);

	//text assign: lives
	
	livesCount.setPosition((window.getSize().x / 2), (window.getSize().y / 2) + buttonHeight + yGap);
	livesCount.setFillColor(textColour);
	
	//text assign: won game
	wonGame.setString("You win");
	wonGame.setPosition((window.getSize().x / 2), (window.getSize().y / 2));
	wonGame.setFillColor(textColour);

	//Background
	if (!backgroundImage.loadFromFile("basic bg.png"))
	{
		cout << "Unable to load image" << endl;
	}
	backgroundTexture.loadFromImage(backgroundImage);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(/*window.getSize().x, window.getSize().y*/ float(window.getSize().x) / backgroundTexture.getSize().x, float(window.getSize().y) / backgroundTexture.getSize().y);

	//brick texture
	if (!texture.loadFromFile("brick texture.png"))	{
		cout << "Unable to load texture" << endl;
	} 

	//paddle texture
	if (!paddleTexture.loadFromFile("paddle texture.png")) {
		cout << "Unable to load texture" << endl;
	}
	paddleSprite.setScale(paddleWidth / paddleTexture.getSize().x, paddleHeight / paddleTexture.getSize().y);
	paddleSprite.setPosition(window.getSize().x / 2, window.getSize().y * 0.9);
	paddleSprite.setTexture(paddleTexture);
	
	//Simple AI (Leaf) texture
	if (!leafTexture.loadFromFile("leaf animation line.png"))
	{
		std::cout << "Unable to load image" << std::endl;
	}

	
	leafWidth = leafTexture.getSize().x / 8;
	leafHeight = leafTexture.getSize().y;

	rect = sf::IntRect(0, 0, leafWidth, leafHeight);
	leafSprite = sf::Sprite(leafTexture, rect);
	leafSprite.scale(1, 1);
	leafSprite.setPosition(window.getSize().x / 2, window.getSize().y / 3);
	leafSpeed = 350.0f;

	//Powerups
	powerupWidth = 50.0f;
	powerupHeight = 50.0f;
	powerupSpeed = 200.0f;
	powerupSpawned = false;
	lifeSpawned = false;
	paddleSpawned = false;
	enlargedPaddle = false;
	spawnLocation = (rand() % 5) + 1;
	powerupChoice = (rand() % 2) + 1;

	if (!powerupLife.loadFromFile("powerup (life).png"))
	{
		std::cout << "Unable to load image" << std::endl;
	}
	powerupLifeSprite.setTexture(powerupLife);
	powerupLifeSprite.setScale(powerupWidth / powerupLife.getSize().x, powerupHeight / powerupLife.getSize().y);
	powerupLifeSprite.setPosition(window.getSize().x / spawnLocation, 0);

	if (!powerupPaddle.loadFromFile("powerup (paddle).png"))
	{
		std::cout << "Unable to load image" << std::endl;
	}
	powerupPaddleSprite.setTexture(powerupPaddle);
	powerupPaddleSprite.setScale(powerupWidth / powerupPaddle.getSize().x, powerupHeight / powerupPaddle.getSize().y);	
	powerupPaddleSprite.setPosition(window.getSize().x / spawnLocation, 0);

	//collision (old version - rectangle bricks)
	/*for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			b[row][col].setSize(sf::Vector2f(brickWidth, brickHeight));
			b[row][col].setPosition(xEdgeGap + col * (brickWidth + xGap), yEdgeGap + row * (brickHeight + yGap));
			c[row][col] = true;
			b[row][col].setFillColor(sf::Color::Red);
		}
	}*/
	
	//writeFile.open("brickPos.txt");
	//readFile.open("brickPos.txt");

	/*
	b = new sf::RectangleShape * [rowValue];
	c = new bool* [rowValue];

	for (int i = 0; i < rowValue; ++i) {
			b[i] = new sf::RectangleShape[colValue];
			c[i] = new bool[colValue];
		} 

	//Setup the Array of Bricks
	for (int row = 0; row < rowValue; ++row) {

		for (int col = 0; col < colValue; ++col) {
			//For every Row and Column (or for every brick)
			b[row][col].setSize(sf::Vector2f(brickWidth, brickHeight));
			b[row][col].setPosition(xEdgeGap + col * (brickWidth + xGap), yEdgeGap + row * (brickHeight + yGap));
			c[row][col] = true;

			//b[row][col].setTexture(texture);
		}
	}
	*/

	//Brick Array (non custom)
	//if (customValue == false) {
	s = new sf::Sprite * [rowValue];
		t = new bool* [rowValue];

		for (int i = 0; i < rowValue; ++i) {
			s[i] = new sf::Sprite[colValue];
			t[i] = new bool[colValue];
		}

	//Setup the Array of Bricks
	for (int row = 0; row < rowValue; ++row) {

		for (int col = 0; col < colValue; ++col) {

			//For every Row and Column (or for every brick)
			s[row][col].setScale(sf::Vector2f(brickWidth / texture.getSize().x, brickHeight / texture.getSize().y));
			s[row][col].setTexture(texture);
			s[row][col].setPosition(xEdgeGap + col * (brickWidth + xGap), yEdgeGap + row * (brickHeight + yGap));
			t[row][col] = true;

			totalBricks++;
			//b[row][col].setTexture(texture);
		}
	}
	//}

	/*
	//Brick Array (custom)
	if (customValue == true) {
		s = new sf::Sprite * [ROWS];
		t = new bool* [ROWS];

		for (int i = 0; i < ROWS; ++i) {
			s[0] = new sf::Sprite[customRowOne];
			t[0] = new bool[customRowOne];
			s[1] = new sf::Sprite[customRowTwo];
			t[1] = new bool[customRowTwo];
			s[2] = new sf::Sprite[customRowThree];
			t[2] = new bool[customRowThree];
		}


		//Setup the Array of Bricks
		for (int row = 0; row < ROWS; ++row) {

			for (int col = 0; col < customRowOne; ++col) {
				//For every Row and Column (or for every brick)
				s[0][col].setScale(sf::Vector2f(brickWidth / texture.getSize().x, brickHeight / texture.getSize().y));
				s[0][col].setTexture(texture);
				s[0][col].setPosition(xEdgeGap + col * (brickWidth + xGap), yEdgeGap + row * (brickHeight + yGap));
				t[0][col] = true;
				totalBricks++;

				//b[row][col].setTexture(texture);
			}
			for (int col = 0; col < customRowTwo; ++col) {
				//For every Row and Column (or for every brick)
				s[1][col].setScale(sf::Vector2f(brickWidth / texture.getSize().x, brickHeight / texture.getSize().y));
				s[1][col].setTexture(texture);
				s[1][col].setPosition(xEdgeGap + col * (brickWidth + xGap), yEdgeGap + row * (brickHeight + yGap));
				t[1][col] = true;
				totalBricks++;

				//b[row][col].setTexture(texture);
			}
			for (int col = 0; col < customRowThree; ++col) {
				//For every Row and Column (or for every brick)
				s[2][col].setScale(sf::Vector2f(brickWidth / texture.getSize().x, brickHeight / texture.getSize().y));
				s[2][col].setTexture(texture);
				s[2][col].setPosition(xEdgeGap + col * (brickWidth + xGap), yEdgeGap + row * (brickHeight + yGap));
				t[2][col] = true;
				totalBricks++;

				//b[row][col].setTexture(texture);
			}
		}
	} */

	for (int i = 0; i < menuItems; ++i) {
		menuText[i].setFillColor(textColour);
		menuText[i].setFont(font);
		menuText[i].setPosition(window.getSize().x - 200 + (buttonWidth / 2), yEdgeGap + i * (buttonHeight + yGap));
		menuText[0].setString("Start");
		menuText[1].setString("Editor");
		menuText[2].setString("Exit");
	}
	
	//Setup the pointer arrays for the save menu
	for (int i = 0; i < totalSaves; ++i) {

		loads[i].setPosition(50 + 2 * (buttonWidth + xGap) + buttonWidth, yEdgeGap + i * (buttonHeight + yGap));
		loads[i].setSize(sf::Vector2f(buttonWidth, buttonHeight));

		saves[i].setPosition(50 + (2 * buttonWidth) + xGap, yEdgeGap + i * (buttonHeight + yGap));
		saves[i].setSize(sf::Vector2f(buttonWidth, buttonHeight));

		saveSlots[i].setPosition(50, yEdgeGap + i * (buttonHeight + yGap));
		saveSlots[i].setSize(sf::Vector2f(2 * buttonWidth, buttonHeight));

		slots[i].setFillColor(textColour);
		slots[i].setFont(font);
		slots[i].setPosition(50 + (buttonWidth / 2), yEdgeGap + i * (buttonHeight + yGap));
		slots[0].setString("Default");
		slots[1].setString("Custom Values");
		//slots[2].setString("Custom Rows");
		slots[1].setPosition(50, yEdgeGap + (buttonHeight + yGap));
		//slots[2].setPosition(50, yEdgeGap + 2 * (buttonHeight + yGap));

		save[i].setFillColor(textColour);
		save[i].setFont(font);
		save[i].setPosition(50 + (2 * buttonWidth) + xGap + (buttonWidth / 4), yEdgeGap + i * (buttonHeight + yGap));
		save[i].setString("Set");

		load[i].setFillColor(textColour);
		load[i].setFont(font);
		load[i].setPosition(50 + 2 * (buttonWidth + xGap) + buttonWidth + (buttonWidth / 4), yEdgeGap + i * (buttonHeight + yGap));
		load[i].setString("Load");
	}


	/* Trying to get text to work
	//general text assign
	textColour = sf::Color::White;

	//text assign: gameOver
	gameOver.setString("Game Over");
	gameOver.setPosition((window.getSize().x / 2), (window.getSize().y / 2));
	gameOver.setFillColor(textColour);
	gameOver.setCharacterSize(30);

	//text assign: score
	score.setString("Score = " + to_string(bricksDestroyed));
	score.setPosition((window.getSize().x / 2), 0);
	score.setFillColor(textColour);
	score.setCharacterSize(20);
	*/

	if (!brickBuffer.loadFromFile("brick.wav")) {
		std::cout << "sound not loaded\n";
		return -1;
	}

	if (!buttonBuffer.loadFromFile("button.wav")) {
		std::cout << "sound not loaded\n";
		return -1;
	}

	if (!paddleBuffer.loadFromFile("paddle.wav")) {
		std::cout << "sound not loaded\n";
		return -1;
	}

	if (!wallBuffer.loadFromFile("wall.wav")) {
		std::cout << "sound not loaded\n";
		return -1;
	}

	if (!leafBuffer.loadFromFile("leaf.wav")) {
		std::cout << "sound not loaded\n";
		return -1;
	}

	if (!powerupBuffer.loadFromFile("powerup.wav")) {
		std::cout << "sound not loaded\n";
		return -1;
	}

	brickAudio.setBuffer(brickBuffer);
	buttonAudio.setBuffer(buttonBuffer);
	paddleAudio.setBuffer(paddleBuffer);
	wallAudio.setBuffer(wallBuffer);
	leafAudio.setBuffer(leafBuffer);
	powerupAudio.setBuffer(powerupBuffer);

	//cout << lives << endl;

	if (restarted != true) {
		readmeWrite.open("readme.txt");
		readmeWrite << "How to Play: " << "\n" 
			<< "Your objective is to bounce the ball off the paddle and try to destroy all of the bricks at the top of the screen.\nIf the ball hits the bottom of the screen, you will lose a life. You lose if all lives are lost." << "\n" "\n"
			<< "Controls: " << "\n" << "Left and right keys to move the paddle. Mouse to click the buttons." << "\n" "\n"
			<< "Level Editor: " << "\n" << "For the level editor, click 'Set' and you will be prompted to add an integer into the console. To use these settings, click the 'Load' button after to play with those settings." << "\n" "\n"
			<< "Note: I recommend keeping the number of rows to 4 or less, it may become too difficult otherwise, as well as less than 8 columns.";
		readmeWrite.close();
	}

	//cout << spawnLocation << endl;

	return true;
}

//App method definitons

void App::Update()
{
	//this is here as the string updates
	livesCount.setString("Lives left: " + to_string(lives));
	score.setString("Score = " + to_string(bricksDestroyed));

	//update
	// move Paddle left, frame rate independent
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (paddleSprite.getPosition().x > 0) {
			paddleSprite.move(-speed * deltaTime, 0);
		}
	}

	// move Paddle right, frame rate independent
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (paddleSprite.getPosition().x < window.getSize().x - paddleWidth)	{
			paddleSprite.move(speed * deltaTime, 0); //the defining feature which makes this framerate independent
		}
	}

	// left border collision detection
	if (ball.getPosition().x <= 0) {
		xSpeed = -xSpeed;
		wallAudio.play();
	}

	// right border collision detection
	if (ball.getPosition().x >= window.getSize().x - 2 * ballRadius) {
		xSpeed = -xSpeed;
		wallAudio.play();
	}

	// top border collision detection
	if (ball.getPosition().y <= 0) {
		ySpeed = -ySpeed;
		wallAudio.play();
	}

	// bottom border collision detection
	if (ball.getPosition().y >= window.getSize().y - 2 * ballRadius) {
		//ySpeed = -ySpeed;

		//ball.setPosition((window.getSize().x / 2) - ballRadius, (window.getSize().y / 2) - ballRadius);
		
		//cout << gameOver << endl;
		if (lives == 0)	{
			livesLost = true;
			//cout << lives << endl;
		}

		else if (lives > 0) {
			paused = true;
			if (livesWatch == false) {
				--lives;
				livesWatch = true;
			}
		}

	}
	
	//paddle collision
	if (ball.getGlobalBounds().intersects(paddleSprite.getGlobalBounds()) && paddleCollidable) {
		ySpeed = -ySpeed;
		paddleAudio.play();
		//cout << totalBricks << endl;
	}

	if (isHit == true) {
		xSpeed = -xSpeed;
		ySpeed = -ySpeed;
		brickAudio.play();
		isHit = false;
	}
	// detect collision with collidable brick 
	// i.e. if brick has not been hit

	for (int row = 0; row < rowValue; ++row) {
		for (int col = 0; col < colValue; ++col) {
			if (ball.getGlobalBounds().intersects(s[row][col].getGlobalBounds()) && t[row][col] == true) {
				// destroy the brick
				t[row][col] = false;
				isHit = true;
				bricksDestroyed += 1;
				totalBricks-= 1;
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
	if (inMenu == false && paused == false && gameWin == false) {
		ball.move(xSpeed * deltaTime, ySpeed * deltaTime);
	}

	if (totalBricks == 0) {
		//Run 'Win' function
		gameWin = true;
	}

	//Leaf Animation + AI
	if (gameClock.getElapsedTime().asSeconds() > 1.0f) {
		rect.left += 64;

		leafSprite.setTextureRect(rect);
		gameClock.restart();
	}

	if (rect.left == 448){
		//reset the animation
		rect.left = -64;
	}

	//move the leaf
	if (inMenu == false && paused == false && gameWin == false) {
		leafSprite.move(leafSpeed * deltaTime, 0);
	}

	if (leafSprite.getPosition().x >= window.getSize().x - leafWidth) {
		leafSpeed = -leafSpeed;
	}

	if (leafSprite.getPosition().x <= 0) {
		leafSpeed = -leafSpeed;
	}

	if (ball.getGlobalBounds().intersects(leafSprite.getGlobalBounds())) {
		ySpeed = -ySpeed;
		xSpeed = -xSpeed;
		leafAudio.play();
	}

	//spawn powerups and collisions
	if (powerupSpawned == false && inMenu == false && paused == false) {
		if (powerupClock.getElapsedTime().asSeconds() > 8.0f /*&& powerupSpawned == false*/) {
			powerupSpawned = true;
			if (powerupChoice == 1 && lifeSpawned == false)	{
				//life powerup
				lifeSpawned = true;
			}
			if (powerupChoice == 2 && paddleSpawned == false) {
				//paddle powerup
				paddleSpawned = true;
			}

			//reset the random variables
			spawnLocation = (rand() % 10) + 1;
			powerupChoice = (rand() % 2) + 1;
		}
	}

	//Lives Powerup
	if (lifeSpawned == true && inMenu == false && paused == false && gameWin == false) {
		powerupLifeSprite.move(0, powerupSpeed * deltaTime);
	}
	if (powerupLifeSprite.getPosition().y >= window.getSize().y - powerupHeight) {
		lifeSpawned = false;
		powerupSpawned = false;
		powerupClock.restart();
		powerupLifeSprite.setPosition(window.getSize().x / spawnLocation, 0);
	}
	if (powerupLifeSprite.getGlobalBounds().intersects(paddleSprite.getGlobalBounds()) && lifeSpawned == true) {
		lifeSpawned = false;
		powerupSpawned = false;
		powerupClock.restart();
		powerupLifeSprite.setPosition(window.getSize().x / spawnLocation, 0);
		powerupAudio.play();
		lives++;
		//powerupTimer.restart();
	}

	//Paddle Powerup
	if (paddleSpawned == true && inMenu == false && paused == false && gameWin == false) {
		powerupPaddleSprite.move(0, powerupSpeed * deltaTime);
	}
	if (powerupPaddleSprite.getPosition().y >= window.getSize().y - powerupHeight) {
		paddleSpawned = false;
		powerupSpawned = false;
		powerupClock.restart();
		powerupPaddleSprite.setPosition(window.getSize().x / spawnLocation, 0);
	}
	if (powerupPaddleSprite.getGlobalBounds().intersects(paddleSprite.getGlobalBounds()) && paddleSpawned == true) {
		paddleSpawned = false;
		powerupSpawned = false;
		powerupClock.restart();
		powerupPaddleSprite.setPosition(window.getSize().x / spawnLocation, 0);
		powerupAudio.play();
		powerupTimer.restart();
		paddleWidth += 50;
		enlargedPaddle = true;
		paddleSprite.setScale(paddleWidth / paddleTexture.getSize().x, paddleHeight / paddleTexture.getSize().y);
	}
	if (enlargedPaddle == true && powerupTimer.getElapsedTime().asSeconds() > 4.0f) {
		enlargedPaddle = false;
		paddleWidth -= 50;
		paddleSprite.setScale(paddleWidth / paddleTexture.getSize().x, paddleHeight / paddleTexture.getSize().y);
	}

}

//have it so it saves it as an array and you have it select a certain value of the array on load, and you can save values up to x number

void App::Draw()
{
	window.clear();
	window.setView(view);
	window.draw(backgroundSprite);
	if (startPressed == true) {
		window.draw(ball);
		window.draw(paddleSprite);
		window.draw(score);
		//if (customValue == false) {
		for (int row = 0; row < rowValue; ++row)
		{
			for (int col = 0; col < colValue; ++col)
			{
				if (t[row][col])
				{
					window.draw(s[row][col]);
					//totalBricks++;
				}
			}
		}
		//}
		/*if (customValue == true) {
			for (int row = 0; row < ROWS; ++row)
			{
				for (int col = 0; col < customRowOne; ++col)
				{
					if (t[0][col])
					{
						window.draw(s[0][col]);
						//totalBricks++;
					}
				}
				for (int col = 0; col < customRowTwo; ++col)
				{
					if (t[1][col])
					{
						window.draw(s[1][col]);
						//totalBricks++;
					}
				}
				for (int col = 0; col < customRowThree; ++col)
				{
					if (t[2][col])
					{
						window.draw(s[2][col]);
						//totalBricks++;
					}
				}
			}
		}*/
		inMenu = false;
		window.draw(leafSprite);
	}
	if (inMenu == true) {
		window.draw(startButton);
		window.draw(customButton);
		window.draw(exitButton);
		for (int i = 0; i < menuItems; ++i) {
			window.draw(menuText[i]);
		}
	}
	if (customMenu == true) {
		for (int i = 0; i < totalSaves; ++i) {
			window.draw(saveSlots[i]);
			
			window.draw(loads[i]);
			window.draw(slots[i]);
			
			window.draw(load[i]);
		}
		window.draw(saves[1]);
		window.draw(save[1]);
		//window.draw(saves[2]);
		//window.draw(save[2]);
	}
	if (paused == true && lives > 0) {
		window.draw(continueButton);
		window.draw(continueText);
		window.draw(livesCount);
	}
	if (livesLost == true) {
		window.draw(menuButton);
		window.draw(gameOver);
	}
	if (restartInit == true) {
		window.clear();
	}
	if (gameWin == true && inMenu == false) {
		window.draw(menuButton);
		window.draw(wonGame);
	}
	if (lifeSpawned == true) {
		window.draw(powerupLifeSprite);
	}
	if (paddleSpawned == true) {
		window.draw(powerupPaddleSprite);
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		localPosition = sf::Mouse::getPosition(window);
		//buttons for the menu
		if (startButton.getGlobalBounds().contains(sf::Vector2f(localPosition)) && inMenu == true) {
			buttonAudio.play();
			//cout << "Hello World 1!" << endl; //app.cpp
			window.clear();
			startPressed = true;
			customMenu = false;
			gameClock.restart();
			powerupClock.restart();
			//cout << totalBricks << endl;
		}
		if (customButton.getGlobalBounds().contains(sf::Vector2f(localPosition)) && inMenu == true) {
			buttonAudio.play();
			//cout << "Hello World 2!" << endl; //app.cpp
			customMenu = true;
		}
		if (exitButton.getGlobalBounds().contains(sf::Vector2f(localPosition)) && inMenu == true) {
			buttonAudio.play();
			//cout << "Hello World 3!" << endl; //app.cpp
			window.close();
		}
		if (menuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)) && livesLost == true) {
			buttonAudio.play();
			//cout << "Hello World 4!" << endl; //app.cpp
			window.clear();
			startPressed = false;
			restartInit = true;
			restarted = true;
		}
		if (continueButton.getGlobalBounds().contains(sf::Vector2f(localPosition)) && paused == true) {
			buttonAudio.play();
			//cout << "Hello World 5!" << endl; //app.cpp
			paused = false;
			paddleSprite.setPosition(window.getSize().x / 2, window.getSize().y * 0.9);
			ball.setPosition((window.getSize().x / 2) + ballRadius, (window.getSize().y / 2) + ballRadius);
			ySpeed = -ySpeed;
			livesWatch = false;
		}
		if (saves[1].getGlobalBounds().contains(sf::Vector2f(localPosition)) && customMenu == true) {
			buttonAudio.play();
			//cout << "Hello World 6!" << endl; //app.cpp

			cout << "Please enter an integer for the number of rows of bricks:";
			cin >> defineRow;
			cout << "Please enter an integer for the number of columns of bricks:";
			cin >> defineCol;

			colrowWrite.open("colrowValues.txt");
			colrowWrite << ROWS << "\t" << COLS << "\t" << defineRow << "\t" << defineCol << "\n";
			colrowWrite.close();
		}
		/*
		if (saves[2].getGlobalBounds().contains(sf::Vector2f(localPosition)) && customMenu == true) {
			buttonAudio.play();
			//cout << "Hello World 6!" << endl; //app.cpp

			cout << "Please enter an integer for the number of bricks in the first row:";
			cin >> customRowOne;
			cout << "Please enter an integer for the number of bricks in the second row:";
			cin >> customRowTwo;
			cout << "Please enter an integer for the number of bricks in the third row:";
			cin >> customRowThree;

			colrowWrite.open("customRows.txt");
			colrowWrite << customRowOne << "\t" << customRowTwo << "\t" << customRowTwo << "\n";
			colrowWrite.close();
		}*/
		if (loads[0].getGlobalBounds().contains(sf::Vector2f(localPosition)) && customMenu == true) {
			buttonAudio.play();
			//cout << "Hello World 7!" << endl; //app.cpp
			customValue = false;
			restartInit = true;
			restarted = true;
			customMenu = false;
			//customRowValues = false;
		}
		if (loads[1].getGlobalBounds().contains(sf::Vector2f(localPosition)) && customMenu == true) {
			buttonAudio.play();
			//cout << "Hello World 7!" << endl; //app.cpp
			customValue = true;
			restartInit = true;
			restarted = true;
			customMenu = false;
			//customRowValues = false;
		}
		/*
		if (loads[2].getGlobalBounds().contains(sf::Vector2f(localPosition)) && customMenu == true) {
			buttonAudio.play();
			//cout << "Hello World 7!" << endl; //app.cpp
			customValue = true;
			restartInit = true;
			restarted = true;
			customMenu = false;
			//customRowValues = true;
		}*/
		if (menuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)) && gameWin == true) {
			buttonAudio.play();
			//cout << "Hello World 8!" << endl; //app.cpp
			window.clear();
			startPressed = false;
			restartInit = true;
			restarted = true;
		}
	}
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

		if (restartInit == true) {
			Init();
		}

	}
}