#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <map>
#include <vector>
#include <stdexcept>
#include <string>
#include "Stick.h"
#include "ButtonManager.h"
#include "StatsManager.h"

class GameManager {
public:
    GameManager();
    void play();
    void saveGame(const std::string& filename);
    void loadGame(const std::string& filename) throw(std::runtime_error);

private:
    void draw();
    void handleEvent();
    void clickTheStick(sf::Event event);
    void loadLevel();
    void goToMenu();
    void resetAllSticksColor();
    void displayGameOverMessage(const std::string& message, const sf::Color& color);
    void handleGameEnd();

    sf::RenderWindow m_window;
    std::vector<std::shared_ptr<Stick>> m_sticks;
    std::map<int, sf::Color> m_intToColorMap;
    std::vector<std::shared_ptr<Stick>> m_availableSticks;

    float m_gameTime;
    int m_score;

    ButtonManager m_buttonManager;
    StatsManager m_statsManager;

    sf::RectangleShape m_scoreTimeMenuBackground;
};