//
// Created by Brendan Berg on 13.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ClockController;


class ClockView : public BaseView
{
    friend ClockController;


public:

    ClockView(float x, float y, sf::Color color);

    void Draw() override;

    bool HandleFocusReset() override;

    bool Handle(sf::Event event) override;

    void SetTime(int minutes, int seconds, int millis);


private:

    sf::Text m_PrefixTextShape;
    sf::Text m_MinutesTextShape;
    sf::Text m_Dots1TextShape;
    sf::Text m_SecondsTextShape;
    sf::Text m_Dots2TextShape;
    sf::Text m_MillisTextShape;
    sf::Font m_Font;

    bool m_DotsVisible = true;
    bool m_ForceDotsVisible = false;


};

