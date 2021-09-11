#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
class Ball
{
	public:
		bool inPlay;
		float radius;
		float xSpeed, ySpeed, speed;
		sf::CircleShape circle;
		sf::SoundBuffer bounceB;
		sf::Sound bounce;

		Ball(float r, float x, float y, float xspd, float yspd);
		Ball();
		void CheckShapeCollision(sf::Shape& shape);
		void CheckOutOfBounds();
		int DetectBoundsCollision();
		void updateSpeed(float yDist, float ballR, float paddleSize, int sign);
		void onUpdate();
};

