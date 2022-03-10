#include "TextView.hpp"
#include "AppDelegate.hpp"
#include <iostream>




TextView::TextView(float x, float y, float size, std::string font, std::string content, sf::Color color) {

    if (!m_Tron.loadFromFile("Tron.ttf"))
    {
        throw std::runtime_error("FAIL!");
    }

    if (!m_Standard.loadFromFile("Standard.ttf"))
    {
        throw std::runtime_error("FAIL!");
    }


    if (font == "Standard") {
        m_TextClass.setFont(m_Standard);
    }

    if (font == "Tron") {
        m_TextClass.setFont(m_Tron);
    }

    m_Text = content;
    m_TextClass.setString(m_Text);
    m_TextClass.setCharacterSize(size);
    m_TextClass.setPosition(sf::Vector2f(x , y));
    m_TextClass.setFillColor(color);
}

void TextView::Draw() {

    AppDelegate::Get()->GetWindow()->draw(m_TextClass);
}


void TextView::SetText(std::string Text) {
    m_Text = Text;
    m_TextClass.setString(m_Text);
}

bool TextView::HandleFocusReset() {
    return false;
}

bool TextView::Handle(sf::Event event) {
    return false;
}
