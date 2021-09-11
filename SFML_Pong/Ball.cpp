#pragma once
#include <iostream>
#include "Ball.h"
#include "GlobalVariables.h"

Ball::Ball(float r, float x, float y, float xspd, float yspd)
{
	inPlay = true;
	circle = sf::CircleShape(r);
	circle.setOrigin(r, r);
	circle.setFillColor(sf::Color::White);
	circle.setPosition(x,y);
	radius = r;
	xSpeed = xspd;
	ySpeed = yspd;
	speed = sqrt(pow(xSpeed, 2) + pow(xSpeed, 2));
	bounceB.loadFromFile("Media/Bounce.wav");
	bounce.setBuffer(bounceB);
}

void Ball::CheckShapeCollision(sf::Shape& shape)
{
	if (circle.getGlobalBounds().intersects(shape.getGlobalBounds()))
	{
		int sign = 1;
		if (circle.getPosition().x < shape.getPosition().x)
		{
			sign = -1;
		}
		float yDist = circle.getPosition().y - shape.getPosition().y;
		updateSpeed(yDist, circle.getRadius(), shape.getLocalBounds().height, sign);
		bounce.setBuffer(bounceB);
		bounce.play();
	}
}
void Ball::CheckOutOfBounds()
{
	int collisionState = DetectBoundsCollision();
	if (collisionState == 1)
	{
		pong.incrementScore(false);
		inPlay = false;
	}
	else if (collisionState == 2)
	{
		pong.incrementScore(true);
		inPlay = false;
	}
	else if (collisionState == 3)
	{
		bounce.setBuffer(bounceB);
		bounce.play();
		ySpeed *= -1;
	}
}
int Ball::DetectBoundsCollision() //1 for going past left side of screen, 2 for going past right side of screen, 3 for going past top/bottom of screen, 0 for no collision
{
	if (circle.getPosition().x < radius)
	{
		return 1;
	}
	else if (circle.getPosition().x - radius > screenWidth)
	{
		return 2;
	}
	else if (circle.getPosition().y < radius || circle.getPosition().y > 1080 - radius)
	{
		return 3;
	}
	else
	{
		return 0;
	}
}
void Ball::updateSpeed(float yDist, float ballR, float paddleSize, int sign)
{
	ySpeed = (speed - 0.1) * yDist / (paddleSize / 2 + ballR);
	xSpeed = sqrt(pow(speed, 2) - pow(ySpeed, 2));
	xSpeed *= sign;
}
void Ball::onUpdate()
{
	CheckOutOfBounds();
	circle.move(xSpeed, ySpeed);
}