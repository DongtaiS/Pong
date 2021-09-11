#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Ball.h"
#include "Paddle.h"
class PongWindow
{
    public:
        Paddle paddleL, paddleR;
        sf::RenderWindow window;
        std::vector<Ball> balls;
        std::vector<Paddle> paddles;
        enum gamestates { STARTSCREEN, OPTIONS, GAME, GAMEOVER };
        gamestates gamestate;

        PongWindow();
        void mainLoop();
        void incrementScore(bool player);
    private:
        bool singlePlayer;
        bool middlePaddle;
        int ballCount;
        int p1Score, p2Score;
        sf::Text mainMenuText, subText, ballChoiceText, ballNumsText[10], singlePlayerText, twoPlayerText, middlePaddleText, startGameText, p1ScoreText, p2ScoreText, winnerText, gameOverSubtext;
        sf::Font font;
        sf::SoundBuffer winMusicB, loseMusicB, scorePointB, menuClickB;
        sf::Sound winMusic, loseMusic, scorePoint, menuClick;
        sf::Music mainMusic;

        void setup();
        void getInput();
        void getMenuInput();
        void resetBalls();
        void outlineText(sf::Text&, int thickness);
        void setupText(sf::Text&, std::string, int, float, float);
        void startGame();
        void resetGame();
        void endGame(bool);
};

