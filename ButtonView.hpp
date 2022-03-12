//
// Created by Florian Wolff on 10.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"


class ButtonView : public BaseView
{

public:

    ButtonView(float x, float y, float width, const std::string& text,
               sf::Color defaultColor, sf::Color highlightColor);

    void Draw() override;

    bool HandleFocusReset() override;

    bool Handle(sf::Event event) override;

    void UpdateView();


private:

    sf::RectangleShape m_ButtonField;
    sf::Text m_TextShape;
    sf::Font m_Font;

    sf::Color m_DefaultColor;
    sf::Color m_HighlightColor;

    bool m_Pressed = false;


};
