#include "TextFieldView.hpp"
#include "AppDelegate.hpp"
#include "TextFieldController.hpp"
#include <iostream>




TextFieldView::TextFieldView(float x, float y, float width) {

    if (!m_arial.loadFromFile("arial.ttf"))
    {
        throw std::runtime_error("FAIL!");
    }
    
    m_TextField.setSize(sf::Vector2f(width, 25.f));
    m_TextField.setPosition(sf::Vector2f(x, y));
    m_TextField.setFillColor(sf::Color::White);
    m_TextField.setOutlineThickness(2.f);
    m_TextField.setOutlineColor(sf::Color::Black);

    m_TextShape.setFont(m_arial);
    m_TextShape.setString(m_Text);
    m_TextShape.setCharacterSize(20);
    m_TextShape.setPosition(sf::Vector2f(x+5, y));
    m_TextShape.setFillColor(sf::Color::Black);
}

void TextFieldView::Draw() {
    
    AppDelegate::Get()->GetWindow()->draw(m_TextField);
    AppDelegate::Get()->GetWindow()->draw(m_TextShape);
}

bool TextFieldView::HandleFocusReset() {
    m_focus = false;
    UpdateView();
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
            UpdateView();
        }
    }

    if (event.type == sf::Event::TextEntered) {
        if (m_focus == true) {
            if (event.text.unicode < 128)
                if(auto a=m_TextFieldController.lock()) {
                    a->HandleTextEntry(static_cast<char>(event.text.unicode));
                }
        }
    }
    if (event.type == sf::Event::KeyPressed) {
        if (m_focus == true) {
            if (event.key.code == sf::Keyboard::Backspace) {
                if (auto a = m_TextFieldController.lock()) {
                    a->HandleDeleteKeyPress();
                }
            }
        }
    }

	return false;
}
void TextFieldView::SetText(std::string Text) {
    m_Text = Text;
    m_TextShape.setString(m_Text);
}

void TextFieldView::UpdateView() {
    if (m_focus == true) {
        m_TextField.setOutlineColor(sf::Color::Blue);
    }
    else {
        m_TextField.setOutlineColor(sf::Color::Black);
    }
}