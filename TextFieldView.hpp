#pragma once
#include "BaseView.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class TextFieldView :
    public BaseView
{
public:
    TextFieldView();
    void Draw() override;
    bool HandleFocusReset() override;
    bool Handle(sf::Event event) override;
    void SetText(std::string Text);
    void UpdateView();

private:
    sf::RectangleShape m_TextField;
    sf::Text m_TextShape;
    std::string m_Text;
    sf::Font m_arial;
    bool m_focus = false;
};

