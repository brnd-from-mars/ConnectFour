//
// Created by Brendan Berg on 10.03.22.
//

#include "GridFieldView.hpp"

#include <iostream>

#include "AppDelegate.hpp"

#include "GridFieldController.hpp"


GridFieldView::GridFieldView(float x, float y)
{
    m_Layer = 1;

    m_FieldShape.setPosition(x + m_Outline, y + m_Outline);
    m_FieldShape.setSize(sf::Vector2f(m_Size - 2 * m_Outline, m_Size - 2 * m_Outline));
    m_FieldShape.setFillColor(sf::Color(51, 59, 60));
}


void GridFieldView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_FieldShape);
}


bool GridFieldView::HandleFocusReset()
{
    return false;
}


bool GridFieldView::Handle(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        auto dx = event.mouseButton.x - (m_FieldShape.getPosition().x);
        auto dy = event.mouseButton.y - (m_FieldShape.getPosition().y);
        if (((dx >= 0) && (dx <= m_FieldShape.getSize().x)) &&
            ((dy >= 0) && (dy <= m_FieldShape.getSize().y)))
        {
            if (auto controller = m_GridFieldController.lock())
            {
                controller->HandleClick();
            }
        }
    }
    return false;
}


sf::Vector2f GridFieldView::GetCenter() const
{
    auto pos = m_FieldShape.getPosition();
    auto size = m_FieldShape.getSize();
    return sf::Vector2f(pos.x + size.x / 2, pos.y + size.y / 2);
}
