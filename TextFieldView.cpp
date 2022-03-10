#include "TextFieldView.hpp"
#include "AppDelegate.hpp"

TextFieldView::TextFieldView() {
    
    m_TextField.setSize(sf::Vector2f(400.f, 50.f));
    m_TextField.setPosition(sf::Vector2f(100.f, 120.f));
    m_TextField.setFillColor(sf::Color::White);
    m_TextField.setOutlineThickness(1.f);
    m_TextField.setOutlineColor(sf::Color::Black);
}

void TextFieldView::Draw() {
    AppDelegate::Get()->GetWindow()->draw(m_TextField);
}

bool TextFieldView::ResetFocus() {
	return false;
}

bool TextFieldView::Handle(sf::Event event) {
	return false;
}