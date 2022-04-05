//
// Created by Brendan Berg on 13.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"


/*!
 * @brief ArrowView displays an left-pointing arrow on the screen.
 */
class ArrowView : public BaseView
{

public:

    /*!
     * @brief Static factory function creates a new arrow.
     *
     * @param x x-coordinate of the arrow on the screen
     * @param y y-coordinate of the arrow on the screen
     * @param color color of the displayed arrow
     * @param layer layer of the arrow object on the screen
     * @return shared pointer to the new ArrowView
     */
    static std::shared_ptr<ArrowView> MakeArrow(float x, float y, sf::Color color, int layer = 0);


    /*!
     * @brief Constructor initializes all SFML elements.
     *
     * @param x x-coordinate of the arrow on the screen
     * @param y y-coordinate of the arrow on the screen
     * @param color color of the arrow
     * @param layer layer of the arrow
     */
    ArrowView(float x, float y, sf::Color color, int layer);


    /*!
     * @brief Draws the arrow to the RenderWindow in the AppDelegate.
     */
    void Draw() override;

    /*!
     * @brief Sets the position of the arrowhead.
     *
     * @param x x-coordinate of the arrow on the screen
     * @param y y-coordinate of the arrow on the screen
     */
    void SetPosition(float x, float y);

    /*!
     * @brief No-op.
     *
     * @return false
     */
    bool HandleFocusReset() override;

    /*!
     * @brief No-op.
     *
     * @param event SFML-Event
     * @return false
     */
    bool Handle(sf::Event event) override;


private:

    /*!
     * @brief SFML-ConvexShape: Shape of the arrowhead
     */
    sf::ConvexShape m_ArrowHead;

    /*!
     * @brief SFML-ConvexShape: Shape of the arrowbody
     */
    sf::ConvexShape m_ArrowBody;


};

