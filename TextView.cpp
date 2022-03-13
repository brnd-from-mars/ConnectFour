//
// Created by Florian Wolff on 10.03.22.
//

#include "TextView.hpp"

#include "AppDelegate.hpp"


std::shared_ptr<TextView> TextView::MakeText(float x, float y, unsigned int size, const std::string& font,
                                             const std::string& text, sf::Color color, int layer)
{
    auto view = std::make_shared<TextView>(x, y, size, font, text, color, layer);
    AppDelegate::Get()->RegisterView(view);

    return view;
}


TextView::TextView(float x, float y, unsigned int size, const std::string& font,
                   const std::string& text, sf::Color color, int layer)
{
    m_Layer = layer;

    auto fontFile = font;
    fontFile.append(".ttf");
    if (!m_Font.loadFromFile(fontFile))
    {
        throw std::runtime_error("FAIL!");
    }

    m_TextShape.setString(text);
    m_TextShape.setCharacterSize(size);
    m_TextShape.setPosition(sf::Vector2f(x , y));
    m_TextShape.setFillColor(color);
    m_TextShape.setFont(m_Font);
}


void TextView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_TextShape);
}


void TextView::SetText(const std::string& text)
{
    m_TextShape.setString(text);
}


bool TextView::HandleFocusReset()
{
    return false;
}


bool TextView::Handle(sf::Event event)
{
    return false;
}
