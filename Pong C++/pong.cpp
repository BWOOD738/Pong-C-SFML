#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include "pong.h"

int main()
{
    std::srand(time(NULL));

    // Time
    sf::Clock clock;

    // Create window 
    sf::RenderWindow window(sf::VideoMode(g_width, g_height), "Pong C++");

    // Used to tell if we are playing or not
    bool isPlaying = false;

    // create left paddle
    lPaddle.setSize(paddleSize);
    lPaddle.setOutlineThickness(3);
    lPaddle.setOutlineColor(sf::Color::Black);
    lPaddle.setFillColor(sf::Color::White);
    lPaddle.setOrigin(paddleSize / 2.f);
    
    // Create the right paddle 
    rPaddle.setSize(paddleSize);
    rPaddle.setOutlineThickness(3);
    rPaddle.setOutlineColor(sf::Color::Black);
    rPaddle.setFillColor(sf::Color::White);
    rPaddle.setOrigin(paddleSize / 2.f);

    // Create the ball
    ball.setRadius(ballRadius);
    ball.setOutlineThickness(3);
    ball.setOutlineColor(sf::Color::Black);
    ball.setFillColor(sf::Color::White);
    ball.setOrigin(ballRadius / 2, ballRadius / 2);

     // run the program as long as the window is open
     while (window.isOpen())
     {
         // check all the window's events that were triggered since the last iteration of the loop
         sf::Event event;
         while (window.pollEvent(event))
         {
             // "close requested" event: we close the window
             if (event.type == sf::Event::Closed)
             {
                 window.close();
             }
            // Press the space bar to play 
              if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
              {
                 if (!isPlaying)
                 {
                      isPlaying = true;
                      clock.restart();

                      // Set the position of the game objects 
                      ball.setPosition(g_width / 2, g_height / 2);
                      rPaddle.setPosition(g_width - 25 , g_height / 2);
                      lPaddle.setPosition(10, g_height / 2);
                      ballSpeed = 500.f;

                      // Makes the ball go into a random direction
                      do
                      {
                          ballAngle = (std::rand() % 360) * 2 * pi / 360;
                      } 
                      while (std::abs(std::cos(ballAngle)) < 0.7f);
                 }
              }
         }

         if (isPlaying)
         {
             float deltaT = clock.restart().asSeconds();

             // Handle player input 
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (lPaddle.getPosition().y - paddleSize.y / 2 > 5.f))
             {
                 lPaddle.move(0.f, -PaddleSpeed * deltaT);
             }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (lPaddle.getPosition().y + paddleSize.y / 2 < g_height - 5.f))
             {           
                 lPaddle.move(sf::Vector2f(0.f, PaddleSpeed * deltaT));
             }

             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && rPaddle.getPosition().y - paddleSize.y / 2 > 5.f)
             {
                 rPaddle.move(0.f, -PaddleSpeed * deltaT);
             }
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && rPaddle.getPosition().y - paddleSize.y / 2 < g_height - 100.f)
             {
                 rPaddle.move(0.f, PaddleSpeed * deltaT);
             }

             // Move the ball
             float factor = ballSpeed * deltaT;
             ball.move(std::cos(ballAngle)* factor, std::sin(ballAngle) * factor);

            void HandleScreenCollision();
             {
                 if (ball.getPosition().x - ballRadius < 0.f)
                 {
                     isPlaying = false;
                     // say P2 has won
                 }
                 if (ball.getPosition().x + ballRadius > g_width)
                 {
                     isPlaying = false;
                     // Say that P1 has won the game
                 }
                 if (ball.getPosition().y - ballRadius < 0.f)
                 {
                     ballAngle = -ballAngle;
                     ball.setPosition(ball.getPosition().x, ballRadius + 0.1f);
                 }
                 if (ball.getPosition().y + ballRadius > g_height)
                 {
                     ballAngle = -ballAngle;
                     ball.setPosition(ball.getPosition().x, g_height - ballRadius - 0.1f);
                 }
             }

             void HandlePaddleCollisions();
             {
                 // Left paddle 
                 if (ball.getPosition().x - ballRadius < lPaddle.getPosition().x + paddleSize.x / 2 &&
                     ball.getPosition().x - ballRadius > lPaddle.getPosition().x &&
                     ball.getPosition().y + ballRadius >= lPaddle.getPosition().y - paddleSize.y / 2 &&
                     ball.getPosition().y - ballRadius <= lPaddle.getPosition().y + paddleSize.y / 2)
                 {
                     if (ball.getPosition().y > lPaddle.getPosition().y)
                     {
                         ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 180;
                         ballSpeed = ballSpeed + 100.f;
                     }
                     else
                     {
                         ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                         ballSpeed = ballSpeed + 100.f;
                     }
                     ball.setPosition(lPaddle.getPosition().x + ballRadius + paddleSize.x / 2 + 0.1f, ball.getPosition().y);
                 }

                 // Right paddle
                 if (ball.getPosition().x + ballRadius > rPaddle.getPosition().x - paddleSize.x / 2 &&
                     ball.getPosition().x + ballRadius < rPaddle.getPosition().x &&
                     ball.getPosition().y + ballRadius >= rPaddle.getPosition().y - paddleSize.y / 2 &&
                     ball.getPosition().y - ballRadius <= rPaddle.getPosition().y + paddleSize.y / 2)
                 {
                     if (ball.getPosition().y > rPaddle.getPosition().y)
                     {
                         ballAngle = pi - ballAngle + (std::rand() % 20) * pi / 18;
                         ballSpeed = ballSpeed + 100.f;
                     }
                     else
                     {
                         ballAngle = pi - ballAngle - (std::rand() % 20) * pi / 180;
                         ballSpeed = ballSpeed + 100.f;
                     }
                     ball.setPosition(rPaddle.getPosition().x - ballRadius - paddleSize.x / 2 - 0.1f, ball.getPosition().y);
                 }
             }
         }

         window.clear(sf::Color::Black);
         
         if (isPlaying)
         {
             window.draw(ball);
             window.draw(rPaddle);
             window.draw(lPaddle);
         }
         window.display();
     }
     return 0;
}