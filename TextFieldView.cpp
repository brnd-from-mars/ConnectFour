#include "TextFieldView.hpp"
#include "AppDelegate.hpp"
#include <iostream>




TextFieldView::TextFieldView() {

    if (!m_arial.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("FAIL!");
    }
    
    m_TextField.setSize(sf::Vector2f(400.f, 50.f));
    m_TextField.setPosition(sf::Vector2f(100.f, 120.f));
    m_TextField.setFillColor(sf::Color::White);
    m_TextField.setOutlineThickness(2.f);
    m_TextField.setOutlineColor(sf::Color::Black);

    m_TextShape.setFont(m_arial);
    m_TextShape.setString(m_Text);
    m_TextShape.setCharacterSize(40);
    m_TextShape.setPosition(sf::Vector2f(100.f, 120.f));
    m_TextShape.setFillColor(sf::Color::Black);
}

void TextFieldView::Draw() {
    if (m_focus == true) {
        m_TextField.setOutlineColor(sf::Color::Blue);
    }
    else {
        m_TextField.setOutlineColor(sf::Color::Black);
    }
    AppDelegate::Get()->GetWindow()->draw(m_TextField);
    AppDelegate::Get()->GetWindow()->draw(m_TextShape);
}

bool TextFieldView::HandleFocusReset() {
    m_focus = false;
	return false;
}

bool TextFieldView::Handle(sf::Event event) {

    if (event.type == sf::Event::MouseButtonPressed)
    {
        auto dx = event.mouseButton.x - (m_TextField.getPosition().x);
        auto dy = event.mouseButton.y - (m_TextField.getPosition().y);
        if (((dx>=0)&&(dx<=m_TextField.getSize().x)) && ((dy>=0)&&(dy<=m_TextField.getSize().y)))
        {
            m_focus = true;
        }
    }
	return false;
}
void TextFieldView::SetText(std::string Text) {
    m_Text = Text;
}