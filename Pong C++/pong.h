#pragma once
#ifndef PONG_H
#define PONG_H

// Define constants 
const int g_width = 1920;
const int g_height = 1080;
float ballRadius = 12.f;
sf::Vector2f paddleSize(25, 100);
float ballSpeed = 500.f;
float ballAngle = 0.f;
double pi = 3.1415;

float PaddleSpeed = 800.0f;

// Create left paddle
sf::RectangleShape lPaddle;

// Right paddle
sf::RectangleShape rPaddle;

// Ball 
sf::CircleShape ball;
#endif