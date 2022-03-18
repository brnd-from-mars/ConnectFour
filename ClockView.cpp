//
// Created by Brendan Berg on 13.03.22.
//

#include <sstream>
#include <iomanip>

#include "ClockView.hpp"

#include "AppDelegate.hpp"


ClockView::ClockView(float x, float y, sf::Color color)
{
    m_Layer = 1;

    if (!m_Font.loadFromFile("Standard.ttf"))
    {
        throw std::runtime_error("Font Standard.ttf not loaded");
    }

    m_PrefixTextShape.setString("T+");
    m_PrefixTextShape.setCharacterSize(20);
    m_PrefixTextShape.setPosition(sf::Vector2f(x, y));
    m_PrefixTextShape.setFillColor(color);
    m_PrefixTextShape.setFont(m_Font);

    m_MinutesTextShape.setString("00");
    m_MinutesTextShape.setCharacterSize(20);
    m_MinutesTextShape.setPosition(sf::Vector2f(x + 30.0f , y));
    m_MinutesTextShape.setFillColor(color);
    m_MinutesTextShape.setFont(m_Font);

    m_Dots1TextShape.setString(":");
    m_Dots1TextShape.setCharacterSize(20);
    m_Dots1TextShape.setPosition(sf::Vector2f(x + 62.0f, y));
    m_Dots1TextShape.setFillColor(color);
    m_Dots1TextShape.setFont(m_Font);

    m_SecondsTextShape.setString("00");
    m_SecondsTextShape.setCharacterSize(20);
    m_SecondsTextShape.setPosition(sf::Vector2f(x + 69.0f, y));
    m_SecondsTextShape.setFillColor(color);
    m_SecondsTextShape.setFont(m_Font);

    m_Dots2TextShape.setString(":");
    m_Dots2TextShape.setCharacterSize(20);
    m_Dots2TextShape.setPosition(sf::Vector2f(x + 100.0f, y));
    m_Dots2TextShape.setFillColor(color);
    m_Dots2TextShape.setFont(m_Font);

    m_MillisTextShape.setString("000");
    m_MillisTextShape.setCharacterSize(20);
    m_MillisTextShape.setPosition(sf::Vector2f(x + 106.0f, y));
    m_MillisTextShape.setFillColor(color);
    m_MillisTextShape.setFont(m_Font);
}


void ClockView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_PrefixTextShape);
    AppDelegate::Get()->GetWindow()->draw(m_MinutesTextShape);
    AppDelegate::Get()->GetWindow()->draw(m_SecondsTextShape);
    AppDelegate::Get()->GetWindow()->draw(m_MillisTextShape);

    if (m_DotsVisible | m_ForceDotsVisible)
    {
        AppDelegate::Get()->GetWindow()->draw(m_Dots1TextShape);
        AppDelegate::Get()->GetWindow()->draw(m_Dots2TextShape);
    }
}


bool ClockView::HandleFocusReset()
{
    return false;
}


bool ClockView::Handle(sf::Event event)
{
    return false;
}


void ClockView::SetTime(int minutes, int seconds, int millis)
{
    std::stringstream string;

    string << std::setw(2) << std::setfill('0') << minutes;
    m_MinutesTextShape.setString(minutes < 100 ? string.str() : "XX");

    string.str(std::string());
    string << std::setw(2) << std::setfill('0') << seconds;
    m_SecondsTextShape.setString(string.str());

    string.str(std::string());
    string << std::setw(3) << std::setfill('0') << millis;
    m_MillisTextShape.setString(string.str());

    m_DotsVisible = millis < 500;
}
