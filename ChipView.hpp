//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ChipController;


class ChipView : public BaseView
{
    friend ChipController;


public:

    ChipView(float x, float y, sf::Color circleColor, sf::Color highlightColor);

    void Draw() override;

    bool HandleFocusReset() override;

    bool Handle(sf::Event event) override;

    void EnableRing(bool enable);


private:

    std::weak_ptr<ChipController> m_ChipController;

    sf::CircleShape m_Circle;
    sf::CircleShape m_Ring;

    sf::Color m_CircleColor;
    sf::Color m_HighlightColor;

    bool m_HandleEvents = false;

    static constexpr float m_InnerRadius = 10.0f;
    static constexpr float m_OuterRadius = 12.0f;


};
