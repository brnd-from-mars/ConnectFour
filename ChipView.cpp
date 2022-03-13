//
// Created by Brendan Berg on 09.03.22.
//

#include <cmath>
#include <iostream>

#include "ChipView.hpp"
#include "ChipController.hpp"

#include "AppDelegate.hpp"


ChipView::ChipView(float x, float y, sf::Color circleColor, sf::Color highlightColor)
    : m_Circle(m_InnerRadius), m_Ring(m_OuterRadius), m_CircleColor(circleColor), m_HighlightColor(highlightColor)
{
    m_Layer = 2;

    m_Ring.setFillColor(m_CircleColor);
    m_Ring.setPosition(x - m_OuterRadius, y - m_OuterRadius);

    m_Circle.setFillColor(m_CircleColor);
    m_Circle.setPosition(x - m_InnerRadius, y - m_InnerRadius);
}


void ChipView::EnableRing(bool enable)
{
    m_Ring.setFillColor(enable ? m_HighlightColor : m_CircleColor);
}


void ChipView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_Ring);
    AppDelegate::Get()->GetWindow()->draw(m_Circle);
}


bool ChipView::HandleFocusReset()
{
    return false;
}


bool ChipView::Handle(sf::Event event)
{
    return false;
}