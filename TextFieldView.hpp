#pragma once
#include "BaseView.hpp"
#include <SFML/Graphics.hpp>

class TextFieldView :
    public BaseView
{
public:
    TextFieldView();
    void Draw() override;
    bool ResetFocus() override;
    bool Handle(sf::Event event) override;

private:
    sf::RectangleShape m_TextField;
};

