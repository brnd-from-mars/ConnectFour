#include "ButtonView.hpp"
#include "AppDelegate.hpp"
#include <iostream>




ButtonView::ButtonView() {

    m_ButtonField.setSize(sf::Vector2f(30.f, 30.f));
    m_ButtonField.setPosition(sf::Vector2f(200.f, 200.f));
    m_ButtonField.setFillColor(sf::Color::Red);
    m_ButtonField.setOutlineThickness(2.f);
    m_ButtonField.setOutlineColor(sf::Color::Red);
}

void ButtonView::Draw() {

    AppDelegate::Get()->GetWindow()->draw(m_ButtonField);
}

bool ButtonView::HandleFocusReset() {
    m_focus = false;
    UpdateView();
    return false;
}

bool ButtonView::Handle(sf::Event event) {

    if (event.type == sf::Event::MouseButtonPressed)
    {
        auto dx = event.mouseButton.x - (m_ButtonField.getPosition().x);
        auto dy = event.mouseButton.y - (m_ButtonField.getPosition().y);
        if (((dx >= 0) && (dx <= m_ButtonField.getSize().x)) && ((dy >= 0) && (dy <= m_ButtonField.getSize().y)))
        {
            m_focus = true;
            UpdateView();
        }
    }

    return false;
}

void ButtonView::UpdateView() {
    if (m_focus == true) {
        m_ButtonField.setOutlineColor(sf::Color::Yellow);
    }
    else {
        m_ButtonField.setOutlineColor(sf::Color::Red);
    }
}