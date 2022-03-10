#pragma once
#include "BaseView.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

class TextView :
    public BaseView
{
public:
    TextView(float x, float y, float size, std::string font, std::string content, sf::Color color);
    void Draw() override;
    void SetText(std::string Text);
    bool HandleFocusReset() override;
    bool Handle(sf::Event event) override;

private:
    sf::Text m_TextClass;
    std::string m_Text;
    sf::Font m_Standard;
    sf::Font m_Tron;
};

