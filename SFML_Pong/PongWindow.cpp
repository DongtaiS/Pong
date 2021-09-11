#pragma once
#include <cmath>
#include <iostream>
#include "GlobalVariables.h"
#include "PongWindow.h"

PongWindow::PongWindow()
{
    ballCount = 1;
    singlePlayer = true;
    middlePaddle = true;
    paddleL = Paddle(20, 200, 30, screenHeight / 2, screenHeight / 150);
    paddleR = Paddle(20, 200, screenWidth-30, screenHeight / 2, screenHeight / 150);
    window.create(sf::VideoMode(screenWidth, screenHeight), "PONG");
    font.loadFromFile("Media/Avant_Garde.ttf");
    winMusicB.loadFromFile("Media/WinMusic.wav");
    loseMusicB.loadFromFile("Media/LoseMusic.wav");
    scorePointB.loadFromFile("Media/ScorePoint.wav");
    menuClickB.loadFromFile("Media/Bounce.wav");
    mainMusic.openFromFile("Media/Music.wav");
    winMusic.setBuffer(winMusicB);
    loseMusic.setBuffer(loseMusicB);
    scorePoint.setBuffer(scorePointB);
    menuClick.setBuffer(menuClickB);
    mainMusic.setLoop(true);
    gamestate = STARTSCREEN;
    p1Score = 0;
    p2Score = 0;
}

void PongWindow::getInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        paddleL.moveUp();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        paddleL.moveDown();
    }
    if (!singlePlayer)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {
            paddleR.moveUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {
            paddleR.moveDown();
        }
    }
}

void PongWindow::getMenuInput()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (int i = 0; i < 10; i++)
        {
            if (ballNumsText[i].getGlobalBounds().contains(mousePos.x, mousePos.y))
            {
                menuClick.play();
                ballCount = i + 1;
                for (int j = 0; j < 10; j++)
                {
                    outlineText(ballNumsText[j], 0);
                }
                outlineText(ballNumsText[i], 3);
                return;
            }
        }
        if (startGameText.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            menuClick.play();
            startGame();
        }
        else if (singlePlayerText.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            menuClick.play();
            singlePlayer = true;
            outlineText(twoPlayerText, 0);
            outlineText(singlePlayerText, 2);
        }
        else if (twoPlayerText.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            menuClick.play();
            singlePlayer = false;
            outlineText(twoPlayerText, 2);
            outlineText(singlePlayerText, 0);
        }
        else if (middlePaddleText.getGlobalBounds().contains(mousePos.x, mousePos.y))
        {
            menuClick.play();
            if (middlePaddle)
            {
                outlineText(middlePaddleText, 0);
                middlePaddle = false;
            }
            else
            {
                outlineText(middlePaddleText, 2);
                middlePaddle = true;
            }
        }
    }
}
void PongWindow::resetBalls()
{
    for (int i = 0; i < ballCount; i++)
    {
        float xspd = screenWidth / 200;
        float xpos = screenWidth / 2;
        if (i % 2 == 1)
        {
            xspd *= -1;
            if (middlePaddle)
            {
                xpos += screenWidth / 4;
            }
        }
        else if (i % 2 == 0 && middlePaddle)
        {
            xpos -= screenWidth / 4;
        }
        balls[i].inPlay = true;
        balls[i].circle.setPosition(xpos, (i + 1) * screenHeight / (ballCount + 1));
        balls[i].xSpeed = xspd;
        balls[i].ySpeed = screenHeight / 200;
    }
}
void PongWindow::startGame()
{
    gamestate = GAME;
    if (singlePlayer)
    {
        paddleR.speed = screenHeight / 200;
    }
    else
    {
        paddleR.speed = screenHeight / 150;
    }
    if (middlePaddle)
    {
        paddles.push_back(Paddle(20, 400, screenWidth / 2, screenHeight / 2, screenHeight / 200));
    }
    for (int i = 0; i < ballCount; i++)
    {
        float xspd = screenWidth / 200;
        float xpos = screenWidth / 2;
        if (i % 2 == 1)
        {
            xspd *= -1;
            if (middlePaddle)
            {
                xpos += screenWidth / 4;
            }
        }
        else if (i % 2 == 0 && middlePaddle)
        {
            xpos -= screenWidth / 4;
        }
        balls.push_back(Ball(30, xpos, (i+1) * screenHeight / (ballCount+1), xspd, screenHeight / 200));
    }
}
void PongWindow::outlineText(sf::Text& text, int thickness)
{
    text.setOutlineThickness(thickness);
    text.setOutlineColor(sf::Color::White);
}
void PongWindow::setupText(sf::Text& text, std::string msg, int fontSize, float x, float y)
{
    text.setFont(font);
    text.setString(msg);
    text.setCharacterSize(fontSize);
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(x, y);
}
void PongWindow::incrementScore(bool player1)
{
    scorePoint.play();
    if (player1)
    {
        p1Score++;
        p1ScoreText.setString(std::to_string(p1Score));
        if (p1Score == 10)
        {
            endGame(true);
        }
    }
    else
    {
        p2Score++;
        p2ScoreText.setString(std::to_string(p2Score));
        if (p2Score == 10)
        {
            endGame(false);
        }
    }
}
void PongWindow::endGame(bool p1Win)
{
    gamestate = GAMEOVER;
    if (p1Win)
    {
        setupText(winnerText, "Player 1 wins!", 60, screenWidth / 2, screenHeight / 2);
        outlineText(p1ScoreText, 2);
        winMusic.play();
    }
    else
    {
        if (singlePlayer)
        {
            setupText(winnerText, "CPU wins!", 60, screenWidth / 2, screenHeight / 2);
            loseMusic.play();
        }
        else
        {
            setupText(winnerText, "Player 2 wins!", 60, screenWidth / 2, screenHeight / 2);
            winMusic.play();
        }
        outlineText(p2ScoreText, 2);
    }
    setupText(gameOverSubtext, "Press ESC to return to main menu", 48, screenWidth / 2, screenHeight * 3 / 4);
}
void PongWindow::resetGame()
{
    balls.clear();
    paddles.clear();
    paddleL.rect.setPosition(30, screenHeight / 2);
    paddleR.rect.setPosition(screenWidth - 30, screenHeight / 2);
    outlineText(p1ScoreText, 0);
    outlineText(p2ScoreText, 0);
    p1Score = 0;
    p2Score = 0;
    p1ScoreText.setString(std::to_string(p1Score));
    p2ScoreText.setString(std::to_string(p2Score));
}
void PongWindow::setup()
{
    window.setFramerateLimit(120);
    mainMusic.play();

    setupText(mainMenuText, "PONG", 72, screenWidth / 2, screenHeight / 2);
    setupText(subText, "Press any key to play", 30, screenWidth / 2, screenHeight * 3.0 / 4);
    setupText(ballChoiceText, "Choose number of balls", 48, screenWidth / 2, 100);
    setupText(singlePlayerText, "Single Player (VS AI)", 48, screenWidth / 3, screenHeight / 2);
    setupText(twoPlayerText, "Two Player", 48, screenWidth * 2 / 3, screenHeight / 2);
    setupText(middlePaddleText, "Include middle paddle", 48, screenWidth / 2, screenHeight * 2 / 3);
    setupText(startGameText, "Start Game", 48, screenWidth / 2, screenHeight * 4 / 5);
    setupText(p1ScoreText, std::to_string(p1Score), 48, screenWidth / 4, 100);
    setupText(p2ScoreText, std::to_string(p2Score), 48, screenWidth * 3 / 4, 100);

    for (int i = 0; i < 10; i++)
    {
        setupText(ballNumsText[i], std::to_string(i + 1), 30, (i + 1) * screenWidth / 11, screenHeight / 4);
    }
    outlineText(ballNumsText[0], 2);
    outlineText(singlePlayerText, 2);
    outlineText(middlePaddleText, 2);
}
void PongWindow::mainLoop()
{
    setup();
    do
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (gamestate == STARTSCREEN)
                {
                    gamestate = OPTIONS;
                }
                else if (gamestate == GAMEOVER && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
                {
                    resetGame();
                    gamestate = STARTSCREEN;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed && gamestate == OPTIONS)
            {
                getMenuInput();
            }
        }
        window.clear();
        switch (gamestate)
        {
            case gamestates::STARTSCREEN:
                window.draw(mainMenuText);
                window.draw(subText);
                break;
            case gamestates::OPTIONS:
                window.draw(ballChoiceText);
                for (int i = 0; i < 10; i++)
                {
                    window.draw(ballNumsText[i]);
                }
                window.draw(singlePlayerText);
                window.draw(twoPlayerText);
                window.draw(middlePaddleText);
                window.draw(startGameText);
                break;
            case GAMEOVER:
                window.draw(winnerText);
                window.draw(p1ScoreText);
                window.draw(p2ScoreText);
                window.draw(gameOverSubtext);
                break;
            case gamestates::GAME:
                getInput();
                if (singlePlayer)
                {
                    paddleR.aiMove(balls);
                }
                bool noBallsInPlay = true;
                for (Ball &ball : balls)
                {
                    if (ball.inPlay)
                    {
                        noBallsInPlay = false;
                        for (Paddle &paddle : paddles)
                        {
                            ball.CheckShapeCollision(paddle.rect);
                        }
                        ball.CheckShapeCollision(paddleL.rect);
                        ball.CheckShapeCollision(paddleR.rect);
                        ball.onUpdate();
                        window.draw(ball.circle);
                    }
                }
                if (noBallsInPlay)
                {
                    resetBalls();
                }
                for (Paddle &paddle : paddles)
                {
                    paddle.autoMove();
                    window.draw(paddle.rect);
                }
                window.draw(paddleL.rect);
                window.draw(paddleR.rect);
                window.draw(p1ScoreText);
                window.draw(p2ScoreText);
                break;
        }
        window.display();
    } while (window.isOpen());
}