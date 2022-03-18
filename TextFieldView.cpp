//
// Created by Florian Wolff on 09.03.22.
//

#include "TextFieldView.hpp"
#include "TextFieldController.hpp"

#include "AppDelegate.hpp"
#include "ConnectFourUtility.hpp"


TextFieldView::TextFieldView(float x, float y, float width, const std::string& placeholder, sf::Color highlightColor)
    : m_HighlightColor(highlightColor)
{
    m_Layer = 2;

    if (!m_Font.loadFromFile("Standard.ttf"))
    {
        throw std::runtime_error("Font Standard.ttf not loaded");
    }
    
    m_TextField.setSize(sf::Vector2f(width, 25.0f));
    m_TextField.setPosition(sf::Vector2f(x, y));
    m_TextField.setFillColor(ColorPalette::BasestarLight);
    m_TextField.setOutlineThickness(2.0f);

    m_TextShape.setFont(m_Font);
    m_TextShape.setCharacterSize(20);
    m_TextShape.setPosition(sf::Vector2f(x + 5.0f, y));
    m_TextShape.setFillColor(m_HighlightColor);

    m_PlaceholderShape.setString(placeholder);
    m_PlaceholderShape.setFont(m_Font);
    m_PlaceholderShape.setCharacterSize(20);
    m_PlaceholderShape.setPosition(sf::Vector2f(x + 5.0f, y));
    m_PlaceholderShape.setFillColor(ColorPalette::BasestarDark);

    UpdateView();
}


void TextFieldView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_TextField);
    AppDelegate::Get()->GetWindow()->draw(m_TextShape.getString().isEmpty() ? m_PlaceholderShape : m_TextShape);
}


bool TextFieldView::HandleFocusReset()
{
    m_InFocus = false;
    UpdateView();
	return true;
}


bool TextFieldView::Handle(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (m_TextField.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
        {
            m_InFocus = true;
            UpdateView();
            return true;
        }
    }

    if (m_InFocus)
    {
        if (auto controller = m_TextFieldController.lock())
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    controller->HandleTextEntry(static_cast<char>(event.text.unicode));
                }
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case sf::Keyboard::Backspace:
                        controller->HandleBackspaceKeyPress();
                        break;
                    case sf::Keyboard::Enter:
                        HandleFocusReset();
                        controller->HandleEnterKeyPress();
                        break;
                    default:
                        break;
                }
            }
        }
    }

	return false;
}


void TextFieldView::SetHighlightColor(sf::Color highlightColor)
{
    m_HighlightColor = highlightColor;
    m_TextShape.setFillColor(m_HighlightColor);
    UpdateView();
}


void TextFieldView::SetText(const std::string& text)
{
    m_TextShape.setString(text);
    if (m_TextShape.getGlobalBounds().width > m_TextField.getGlobalBounds().width - 10.0f)
    {
        if (auto controller = m_TextFieldController.lock())
        {
            controller->HandleBackspaceKeyPress();
        }
    }
}


void TextFieldView::UpdateView()
{
    m_TextField.setOutlineColor(m_InFocus ? m_HighlightColor : ColorPalette::BasestarDark);
}
