#include "Paddle.h"
#include <SFML/Graphics.hpp>
#include "GlobalVariables.h"
#include <iostream>

Paddle::Paddle()
{
}
Paddle::Paddle(float w, float h, float x, float y, float spd)
{
	rect = sf::RectangleShape(sf::Vector2f(w, h));
	rect.setOrigin(w/2, h/2);
	rect.setFillColor(sf::Color::White);
	rect.setPosition(x, y);
	width = w;
	height = h;
	speed = spd;
}

void Paddle::moveUp()
{
	if (rect.getGlobalBounds().top > 0)
	{
		rect.move(0, -speed);
	}
}
void Paddle::moveDown()
{
	if (rect.getGlobalBounds().top + height < ::screenHeight)
	{
		rect.move(0, speed);
	}
}
void Paddle::aiMove(std::vector<Ball> &list)
{
	double minDist = 10000000;
	int index = -1;
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i].inPlay)
		{
			float xDist = abs(list[i].circle.getPosition().x - rect.getPosition().x);
			float yDist = abs(list[i].circle.getPosition().y - rect.getPosition().y);
			float dist = std::min(minDist, sqrt(pow(xDist, 2) + pow(yDist, 2)));
			if (dist < minDist)
			{
				index = i;
				minDist = dist;
			}
		}
	}
	if (index != -1)
	{
		if (abs(list[index].circle.getPosition().y - rect.getPosition().y) > speed)
		{
			if (list[index].circle.getPosition().y < rect.getPosition().y)
			{
				moveUp();
			}
			else
			{
				moveDown();
			}
		}
	}
}
void Paddle::autoMove()
{
	if (rect.getGlobalBounds().top <= 0 || rect.getGlobalBounds().top + height >= screenHeight)
	{
		speed *= -1;
	}
	rect.move(0, speed);
}