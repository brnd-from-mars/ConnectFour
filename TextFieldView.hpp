//
// Created by Florian Wolff on 09.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class TextFieldController;


class TextFieldView : public BaseView
{
    friend TextFieldController;


public:

    TextFieldView(float x, float y, float width, const std::string& placeholder, sf::Color highlightColor);

    void Draw() override;

    bool HandleFocusReset() override;

    bool Handle(sf::Event event) override;

    void SetHighlightColor(sf::Color highlightColor);

    void SetText(const std::string& text);


private:

    void UpdateView();

    std::weak_ptr<TextFieldController> m_TextFieldController;

    sf::RectangleShape m_TextField;
    sf::Text m_TextShape;
    sf::Text m_PlaceholderShape;
    sf::Font m_Font;

    sf::Color m_HighlightColor;

    bool m_InFocus = false;
};

