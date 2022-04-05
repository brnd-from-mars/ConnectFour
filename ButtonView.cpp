//
// Created by Florian Wolff on 10.03.22.
//

#include "ButtonView.hpp"
#include "ButtonController.hpp"

#include "AppDelegate.hpp"


ButtonView::ButtonView(float x, float y, float width, const std::string& text,
                       sf::Color defaultColor, sf::Color highlightColor)
    : m_DefaultColor(defaultColor), m_HighlightColor(highlightColor)
{
    m_Layer = 2;

    if (!m_Font.loadFromFile("Standard.ttf"))
    {
        throw std::runtime_error("Font Standard.ttf not loaded");
    }

    m_ButtonField.setSize(sf::Vector2f(width, 25.0f));
    m_ButtonField.setPosition(sf::Vector2f(x, y));
    m_ButtonField.setFillColor(ColorPalette::BasestarLight);
    m_ButtonField.setOutlineThickness(2.0f);
    // determine horizontal center coordinates of the button rectangle
    auto center = x + width / 2;

    m_TextShape.setFont(m_Font);
    m_TextShape.setCharacterSize(20);
    m_TextShape.setString(text);
    // align the text centered inside the m_ButtonField
    auto xText = center - (m_TextShape.getGlobalBounds().width / 2);
    m_TextShape.setPosition(sf::Vector2f(xText, y));

    UpdateView();
}

void ButtonView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_ButtonField);
    AppDelegate::Get()->GetWindow()->draw(m_TextShape);
}


bool ButtonView::HandleFocusReset()
{
    return false;
}


bool ButtonView::Handle(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (m_ButtonField.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            m_Pressed = true;
            UpdateView();
            return true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && m_Pressed)
    {
        // only send MousePress event to controller if press AND release occurred with the buttons boundaries
        if (m_ButtonField.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            // hello controller, u still alive bro?
            if (auto controller = m_ButtonController.lock())
            {
                controller->HandleMousePress();
            }
        }

        m_Pressed = false;
        UpdateView();
        return true;
    }

    return false;
}


void ButtonView::UpdateView()
{
    m_ButtonField.setOutlineColor(m_Pressed ? m_HighlightColor : m_DefaultColor);
    m_TextShape.setFillColor(m_Pressed ? m_HighlightColor : m_DefaultColor);
}
