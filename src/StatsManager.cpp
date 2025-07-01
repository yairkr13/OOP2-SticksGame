#include "StatsManager.h"

StatsManager::StatsManager()
    : m_time(0), m_totalScore(0), m_sticksLeft(0), m_sticksPickedUp(0), m_sticksAvailableToPick(0)
{
    m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
}

void StatsManager::setTime(const float time) {
    m_time = time;
}

float StatsManager::getTime() const {
    return m_time;
}

void StatsManager::changeTime(const float time) {
    m_time += time;
}

void StatsManager::setScore(int totalScore) {
    m_totalScore += totalScore;
}

void StatsManager::draw(sf::RenderWindow& window) const {

    sf::Text timeText, scoreText;
    sf::Text sticksLeftText("Sticks Left: " + std::to_string(m_sticksLeft), m_font, 30);
    sf::Text sticksPickedUpText("Sticks Picked Up: " + std::to_string(m_sticksPickedUp), m_font, 30);
    sf::Text sticksAvailableText("Sticks Available: " + std::to_string(m_sticksAvailableToPick), m_font, 30);

    timeText.setFont(m_font);
    timeText.setString("Time: " + std::to_string(static_cast<int>(m_time)));
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(20, 580);

    scoreText.setFont(m_font);
    scoreText.setString("Score: " + std::to_string(m_totalScore));
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20, 620);

    sticksLeftText.setPosition(200, 580);
    sticksAvailableText.setPosition(200, 620);
    sticksPickedUpText.setPosition(200, 660);

    window.draw(timeText);
    window.draw(scoreText);
    window.draw(sticksLeftText);
    window.draw(sticksPickedUpText);
    window.draw(sticksAvailableText);
}
