//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ChipController;

/*!
 * @brief ChipView displays a chip on the screen.
 */
class ChipView : public BaseView
{
    friend ChipController;


public:

    /*!
     * @brief Constructor initializes all SFML elements.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param circleColor color of the chip
     * @param highlightColor color of the ring around the chip that is displayed when highlighted
     */
    ChipView(float x, float y, sf::Color circleColor, sf::Color highlightColor);

    /*!
     * @brief Draws the chip to the RenderWindow in the AppDelegate.
     */
    void Draw() override;

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
     * @brief Sets the color of the ring depending on whether the highlight will be enabled or disabled.
     *
     * @param enable enable / disable highlight
     */
    void EnableRing(bool enable);

    /*!
     * @brief weak pointer to the associated controller
     */
    std::weak_ptr<ChipController> m_ChipController;

    /*!
    * @brief SFML-CircleShape: inner part of the chip
    */
    sf::CircleShape m_Circle;

    /*!
     * @brief SFML-CircleShape: ring around the chip that is displayed in m_HighlightColor whilst highlighted
     */
    sf::CircleShape m_Ring; // TODO: remove m_Ring and use outline attribute of CircleShape

    /*!
     * @brief color of the chip
     */
    sf::Color m_CircleColor;

    /*!
     * @brief color of the ring whilst highlighted
     */
    sf::Color m_HighlightColor;

    /*!
     * @brief inner radius to the ring
     */
    static constexpr float m_InnerRadius = 10.0f;

    /*!
     * @brief outer radius of the ring
     */
    static constexpr float m_OuterRadius = 12.0f;


};
