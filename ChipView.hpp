//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>

#include "BaseView.hpp"

class ChipController;


class ChipView : public BaseView
{
    friend ChipController;

public:

    ChipView();

    void SetPosition(float x, float y);

    void SetFillColor(sf::Color color);

    void EnableRing(bool enable);

    void Draw() override;

    bool ResetFocus() override;

    bool Handle(sf::Event event) override;


private:

    std::weak_ptr<ChipController> m_ChipController;

    sf::CircleShape m_Circle;

    sf::CircleShape m_Ring;

    bool m_RingEnabled = false;

    static constexpr float m_InnerRadius = 42.0f;

    static constexpr float m_OuterRadius = 48.0f;


};
