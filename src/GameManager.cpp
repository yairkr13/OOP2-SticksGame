#include "GameManager.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "Menu.h"

GameManager::GameManager() : m_gameTime(0), m_score(0)
{
    m_window.create(sf::VideoMode(1280, 720), "DUKIM");
    m_intToColorMap[0] = sf::Color::Red;
    m_intToColorMap[1] = sf::Color::Blue;
    m_intToColorMap[2] = sf::Color::Green;
    m_intToColorMap[3] = sf::Color::Yellow;

    // Initialize buttons
    m_buttonManager.initializeUI(m_window);
    m_buttonManager.initMenuButton(m_window);
    m_buttonManager.initHelpButton(m_window);
    m_buttonManager.initSaveButton(m_window);


    // Initialize score and time menu background
    m_scoreTimeMenuBackground.setSize(sf::Vector2f(static_cast<float>(m_window.getSize().x), 150));
    m_scoreTimeMenuBackground.setFillColor(sf::Color(50, 50, 50)); // Initial color
    m_scoreTimeMenuBackground.setPosition(0, static_cast<float>(m_window.getSize().y) - 150.f);
}

void GameManager::play() {
    if (m_statsManager.getScore() == 0)
    {
        loadLevel();
    }
    sf::Clock clock;

    while (m_window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        m_statsManager.changeTime(-deltaTime.asSeconds());

        if (m_statsManager.getTime() <= 0) {
            m_statsManager.setTime(0);
            handleGameEnd();
            return;
        }
        if (m_sticks.empty())
        {
            handleGameEnd();
            return;
        }
        draw();
        handleEvent();
    }
}

void GameManager::draw()
{
    m_window.clear();

    for (const auto& stick : m_sticks) {
        stick->draw(m_window);
    }

    m_buttonManager.drawButtons(m_window);
    m_statsManager.draw(m_window);

    m_window.display();
}

void GameManager::handleEvent() {
    for (sf::Event event; m_window.pollEvent(event); ) {
        switch (event.type) {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::MouseButtonPressed:
            clickTheStick(event);
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f pos = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });
                if (m_buttonManager.isMenuButtonClicked(pos)) {
                    goToMenu();
                }
                else if (m_buttonManager.isHelpButtonClicked(pos)) {
                    m_buttonManager.highlightAvailableSticks(m_availableSticks);
                    draw();
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    resetAllSticksColor();
                    draw();
                }
                //
                else if (m_buttonManager.isSaveButtonClicked(pos)) {
                    try {
                        saveGame("savefile.txt");
                        std::cout << "Game saved successfully!" << std::endl;
                    }
                    catch (const std::exception& e) {
                        std::cerr << "Error saving game: " << e.what() << std::endl;
                    }
                }
            }
            break;
        }
    }
}

void GameManager::clickTheStick(sf::Event event) {
    sf::Vector2f pos = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

    std::shared_ptr<Stick> clickedStick = nullptr;

    for (const auto& stick : m_sticks) {
        if (stick->hit(pos)) {
            clickedStick = stick;
            break;
        }
    }

    if (!clickedStick) {
        return;
    }

    if (clickedStick->canBePickedUp()) {
        auto it = std::remove(m_sticks.begin(), m_sticks.end(), clickedStick);
        m_sticks.erase(it, m_sticks.end());

        // Remove the stick from the available sticks list
        m_availableSticks.erase(std::remove(m_availableSticks.begin(), m_availableSticks.end(), clickedStick), m_availableSticks.end());

        m_statsManager.incrementSticksPickedUp();
        m_statsManager.updateSticksLeft(static_cast<int>(m_sticks.size()));
        m_statsManager.setScore(10);

        for (auto& stick : m_sticks) {
            stick->removeOverlappingStick(clickedStick);

            // If the stick now has no overlaps, add it to the available sticks list
            if (stick->getOverlappingSticks().empty() && std::find(m_availableSticks.begin(), m_availableSticks.end(), stick) == m_availableSticks.end()) {
                m_availableSticks.push_back(stick);
            }
        }
        m_statsManager.updateSticksAvailableToPick(static_cast<int>(m_availableSticks.size()));
    }
    else
    {
        for (const auto& obstructingStick : clickedStick->getOverlappingSticks()) {
            obstructingStick->highlight(sf::Color::Magenta);
        }
        draw();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        resetAllSticksColor();
        draw();
    }
}

void GameManager::loadLevel() {
    int numSticks = 30 + rand() % 10;
    m_statsManager.setScore(0);
    m_statsManager.setTime(float(30 + numSticks));
    m_sticks.clear();
    m_availableSticks.clear();

    for (int i = 0; i < numSticks; i++) {
        auto newStick = std::make_shared<Stick>(m_intToColorMap[i % m_intToColorMap.size()]);
        m_availableSticks.push_back(newStick);

        for (auto& existingStick : m_sticks) {

            if (existingStick != newStick && newStick->isOverlapping(*existingStick)) {
                existingStick->addOverlappingStick(newStick);
                m_availableSticks.erase(std::remove(m_availableSticks.begin(), m_availableSticks.end(), existingStick), m_availableSticks.end());
            }
        }
        m_sticks.push_back(newStick);
    }
    m_statsManager.updateSticksLeft(static_cast<int>(m_sticks.size()));
    m_statsManager.updateSticksAvailableToPick(static_cast<int>(m_availableSticks.size()));
}

void GameManager::goToMenu()
{
    m_window.close();
    Menu menu;
    menu.show();
}

void GameManager::resetAllSticksColor()
{
    for (auto& stick : m_sticks)
    {
        stick->resetColor();
    }
}

void GameManager::handleGameEnd() {
    if (m_sticks.empty()) {
        std::string message = "WINNER\nScore: " + std::to_string(m_statsManager.getScore());
        displayGameOverMessage(message, sf::Color::Green);
    }
    else {
        displayGameOverMessage("LOOSER", sf::Color::Red);
    }
}

void GameManager::displayGameOverMessage(const std::string& message, const sf::Color& color) {
    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/Arial.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    sf::Text text(message, font, 100); // Large text for the message
    text.setFillColor(color);
    text.setPosition((m_window.getSize().x - text.getGlobalBounds().width) / 2,
        (m_window.getSize().y - text.getGlobalBounds().height) / 2);

    m_window.clear(); 
    m_window.draw(text); 
    m_window.display();

    std::this_thread::sleep_for(std::chrono::seconds(3)); 
    m_window.close();
}

//
void GameManager::saveGame(const std::string& filename) {
    std::ofstream saveFile(filename);
    if (!saveFile) {
        throw std::runtime_error("Unable to open file for saving.");
    }

    // Save the remaining time
    saveFile << m_statsManager.getTime() << std::endl;

    // Save the player's score
    saveFile << m_statsManager.getScore() << std::endl;

    // Save the number of sticks
    saveFile << m_sticks.size() << std::endl;

    saveFile << m_statsManager.getSticksPickedUp() << std::endl;

    // Save each stick's position, rotation, color, and overlapping sticks
    for (const auto& stick : m_sticks) {
        sf::Vector2f position = stick->getPosition();
        float rotation = stick->getRotation();
        sf::Color color = stick->getFillColor();
        saveFile << position.x << " " << position.y << " ";
        saveFile << rotation << " ";
        saveFile << static_cast<int>(color.r) << " " << static_cast<int>(color.g) << " " << static_cast<int>(color.b) << " ";
        // Save the indices of overlapping sticks
        saveFile << stick->getOverlappingSticks().size() << " ";
        for (const auto& overlappingStick : stick->getOverlappingSticks()) {
            // Save the index of the overlapping stick
            auto it = std::find(m_sticks.begin(), m_sticks.end(), overlappingStick);
            if (it != m_sticks.end()) {
                size_t index = std::distance(m_sticks.begin(), it);
                saveFile << index << " ";
            }
        }
        saveFile << std::endl;
    }

    saveFile.close();
}

void GameManager::loadGame(const std::string& filename) {
    std::ifstream loadFile(filename);
    if (!loadFile) {
        throw std::runtime_error("File does not exist or cannot be opened.");
    }

    float time;
    loadFile >> time;
    if (loadFile.fail() || time < 0) {
        throw std::runtime_error("Invalid or unrealistic game time.");
    }
    m_statsManager.setTime(time);

    int score;
    loadFile >> score;
    if (loadFile.fail() || score < 0) {
        throw std::runtime_error("Invalid score value.");
    }
    m_statsManager.setScore(score);

    size_t numSticks;
    loadFile >> numSticks;
    if (loadFile.fail()) {
        throw std::runtime_error("Invalid number of sticks.");
    }
    size_t sticksPicked;
    loadFile >> sticksPicked;
    if (loadFile.fail()) {
        throw std::runtime_error("Invalid number of sticks.");
    }

    m_sticks.clear();
    m_availableSticks.clear();

    // Temporarily store overlapping indices
    std::vector<std::vector<size_t>> overlappingIndices(numSticks);

    for (size_t i = 0; i < numSticks; ++i) {
        float x, y, rotation;
        int r, g, b;
        size_t numOverlaps;

        loadFile >> x >> y >> rotation >> r >> g >> b >> numOverlaps;
        if (loadFile.fail()) {
            throw std::runtime_error("Invalid stick data.");
        }

        auto stick = std::make_shared<Stick>(sf::Color(r, g, b));
        stick->setPosition(sf::Vector2f(x, y));
        stick->setRotation(rotation);
        m_sticks.push_back(stick);

        overlappingIndices[i].resize(numOverlaps);
        for (size_t j = 0; j < numOverlaps; ++j) {
            size_t index;
            loadFile >> index;
            if (loadFile.fail() || index >= numSticks) {
                throw std::runtime_error("Invalid overlapping stick index.");
            }
            overlappingIndices[i][j] = index;
        }
    }

    // Reconstruct overlapping relationships
    for (size_t i = 0; i < numSticks; ++i) {
        for (size_t index : overlappingIndices[i]) {
            m_sticks[i]->addOverlappingStick(m_sticks[index]);
        }
        if (m_sticks[i]->canBePickedUp()) {
            m_availableSticks.push_back(m_sticks[i]);
        }
    }

    m_statsManager.updateSticksLeft(static_cast<int>(m_sticks.size()));
    m_statsManager.updateSticksAvailableToPick(static_cast<int>(m_availableSticks.size()));
    m_statsManager.setSticksPickedUp(static_cast<int>(sticksPicked));

    loadFile.close();
}
