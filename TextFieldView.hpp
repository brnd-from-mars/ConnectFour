#pragma once
#include "BaseView.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class TextFieldController;


class TextFieldView :
    public BaseView
{
    friend TextFieldController;

public:
    TextFieldView(float x, float y, float width);
    void Draw() override;
    bool HandleFocusReset() override;
    bool Handle(sf::Event event) override;
    void SetText(std::string Text);
    void UpdateView();

private:
    std::weak_ptr<TextFieldController> m_TextFieldController;

    sf::RectangleShape m_TextField;
    sf::Text m_TextShape;
    std::string m_Text;
    sf::Font m_arial;
    bool m_focus = false;
};

