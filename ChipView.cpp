//
// Created by Brendan Berg on 09.03.22.
//

#include "ChipView.hpp"

#include <cmath>

#include "AppDelegate.hpp"

#include "ChipController.hpp"


ChipView::ChipView()
    : m_Circle(m_InnerRadius), m_Ring(m_OuterRadius)
{
    m_Layer = 2;
}


void ChipView::SetPosition(float x, float y)
{
    m_Ring.setPosition(x - m_OuterRadius, y - m_OuterRadius);
    m_Circle.setPosition(x - m_InnerRadius, y - m_InnerRadius);
}


void ChipView::SetFillColor(sf::Color color)
{
    m_Ring.setFillColor(m_RingEnabled ? sf::Color(255, 255, 255) : color);
    m_Circle.setFillColor(color);
}


void ChipView::EnableRing(bool enable)
{
    m_RingEnabled = enable;
    m_Ring.setFillColor(m_RingEnabled ? sf::Color(255, 255, 255) : m_Circle.getFillColor());
}


void ChipView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_Ring);
    AppDelegate::Get()->GetWindow()->draw(m_Circle);
}


bool ChipView::ResetFocus()
{
    return false;
}


bool ChipView::Handle(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        // TODO: check if left click
        auto dx = event.mouseButton.x - (m_Circle.getPosition().x + m_OuterRadius);
        auto dy = event.mouseButton.y - (m_Circle.getPosition().y + m_OuterRadius);
        if (sqrt(dx * dx + dy * dy) <= m_OuterRadius)
        {
            if (auto controller = m_ChipController.lock())
            {
                controller->HandleClick();
            }
            return true;
        }
    }

    return false;
}