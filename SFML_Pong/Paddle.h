#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
class Paddle
{
	public:
		sf::RectangleShape rect;
		float width, height;
		float speed;

		Paddle();
		Paddle(float w, float h, float x, float y, float spd);
		void moveUp();
		void moveDown();
		void aiMove(std::vector<Ball> &);
		void autoMove();
};

