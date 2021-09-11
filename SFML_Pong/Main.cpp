#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "Ball.h"
#include <iostream>
#include "GlobalVariables.h"
#include "PongWindow.h"

float screenWidth = 1920;
float screenHeight = 1080;
PongWindow pong;

int main()
{
    pong.mainLoop();
    return 0;
}