#pragma once
#include <SFML/Graphics.hpp>

class StatsManager {
public:
    StatsManager();
    ~StatsManager() {};

    void setTime(const float time);
    float getTime() const;
    void changeTime(const float time);

    void setScore(int totalScore);
    int getScore(){ return m_totalScore; }

    void updateSticksLeft(int count) { m_sticksLeft = count; }
    void incrementSticksPickedUp() { m_sticksPickedUp++; }
    void setSticksPickedUp(int count) { m_sticksPickedUp = count; }
    int getSticksPickedUp() { return m_sticksPickedUp; }
    void updateSticksAvailableToPick(int count) { m_sticksAvailableToPick = count; }

    void draw(sf::RenderWindow& window) const;

private:
    float m_time;

    int m_totalScore;
    int m_sticksLeft;
    int m_sticksPickedUp;
    int m_sticksAvailableToPick;

    sf::Font m_font;
};
