#include <SFML/Graphics.hpp>

int main()
{
    sf::Clock clock;

    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");

    float ballRadius = 25;
    sf::CircleShape ball(25.f);
    float xSpeed = 100;


    sf::RectangleShape brick(sf::Vector2f(100, 50));
    brick.setPosition(500, 0);


    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // collision detection
        if (ball.getGlobalBounds().intersects(brick.getGlobalBounds()))
        {
            xSpeed = -xSpeed;
        }

        ball.move(xSpeed * deltaTime, 0);


        window.clear();
        window.draw(ball);
        window.draw(brick);
        window.display();
    }

    return 0;
}