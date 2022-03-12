#include "TextView.hpp"
#include "AppDelegate.hpp"
#include <iostream>




TextView::TextView(float x, float y, float size, const std::string& font, const std::string& text, sf::Color color)
{
    if (!m_Tron.loadFromFile("Tron.ttf"))
    {
        throw std::runtime_error("FAIL!");
    }

    if (!m_Standard.loadFromFile("Standard.ttf"))
    {
        throw std::runtime_error("FAIL!");
    }


    if (font == "Standard")
    {
        m_TextClass.setFont(m_Standard);
    }

    if (font == "Tron")
    {
        m_TextClass.setFont(m_Tron);
    }

    m_TextClass.setString(text);
    m_TextClass.setCharacterSize(size);
    m_TextClass.setPosition(sf::Vector2f(x , y));
    m_TextClass.setFillColor(color);
}

void TextView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_TextClass);
}


void TextView::SetText(const std::string& text)
{
    m_TextClass.setString(text);
}

bool TextView::HandleFocusReset()
{
    return false;
}

bool TextView::Handle(sf::Event event)
{
    return false;
}
