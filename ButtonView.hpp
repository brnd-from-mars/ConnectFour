#pragma once
#include "BaseView.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class ButtonView :
    public BaseView
{
public:
    ButtonView();
    void Draw() override;
    bool HandleFocusReset() override;
    bool Handle(sf::Event event) override;
    void UpdateView();

private:
    sf::RectangleShape m_ButtonField;
    bool m_focus = false;
};


