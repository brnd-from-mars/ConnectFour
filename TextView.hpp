//
// Created by Florian Wolff on 10.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"


class TextView : public BaseView
{

public:

    static std::shared_ptr<TextView> MakeText(float x, float y, unsigned int size, const std::string& font,
                                              const std::string& text, sf::Color color, int layer = 0);

    TextView(float x, float y, unsigned int size, const std::string& font,
             const std::string& text, sf::Color color, int layer);

    void Draw() override;

    void SetText(const std::string& text);

    bool HandleFocusReset() override;

    bool Handle(sf::Event event) override;


private:

    sf::Text m_TextShape;
    sf::Font m_Font;


};

