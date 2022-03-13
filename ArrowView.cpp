//
// Created by Brendan Berg on 13.03.22.
//

#include "ArrowView.hpp"

#include "AppDelegate.hpp"


std::shared_ptr<ArrowView> ArrowView::MakeArrow(float x, float y, sf::Color color, int layer)
{
    auto view = std::make_shared<ArrowView>(x, y, color, layer);
    AppDelegate::Get()->RegisterView(view);

    return view;
}


ArrowView::ArrowView(float x, float y, sf::Color color, int layer)
{
    m_Layer = layer;

    m_ArrowHead.setPosition(x, y);
    m_ArrowHead.setFillColor(color);
    m_ArrowHead.setPointCount(3);
    m_ArrowHead.setPoint(0, sf::Vector2f(0.0f, 0.0f));
    m_ArrowHead.setPoint(1, sf::Vector2f(12.5f, -7.5f));
    m_ArrowHead.setPoint(2, sf::Vector2f(12.5f, +7.5f));

    m_ArrowBody.setPosition(x, y);
    m_ArrowBody.setFillColor(color);
    m_ArrowBody.setPointCount(4);
    m_ArrowBody.setPoint(0, sf::Vector2f(12.5f, -3.0f));
    m_ArrowBody.setPoint(1, sf::Vector2f(25.0f, -3.0f));
    m_ArrowBody.setPoint(2, sf::Vector2f(25.0f, +3.0f));
    m_ArrowBody.setPoint(3, sf::Vector2f(12.5f, +3.0f));
}


void ArrowView::Draw()
{
    AppDelegate::Get()->GetWindow()->draw(m_ArrowHead);
    AppDelegate::Get()->GetWindow()->draw(m_ArrowBody);
}


void ArrowView::SetPosition(float x, float y)
{
    m_ArrowHead.setPosition(x, y);
    m_ArrowBody.setPosition(x, y);
}


bool ArrowView::HandleFocusReset()
{
    return false;
}


bool ArrowView::Handle(sf::Event event)
{
    return false;
}
