//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ChipController;

/*!
* @brief ChipView represents a chip on a grid field
*/
class ChipView : public BaseView
{
    friend ChipController;


public:
    /*!
    * @brief Constructor creates the ChipView
    *
    * @param x X-coordinate on the screen
    * @param y Y-coordinate on the screen
    * @param circleColor Color of the chip
    * @param highlightColor Color of the chip if it is highlighted
    */
    ChipView(float x, float y, sf::Color circleColor, sf::Color highlightColor);

    /*!
    *@brief Adresses the AppDelegate and draws the chip on the screen
    */
    void Draw() override;

    /*!
    * @brief No-op.
    *
    * @return Returns false
    */
    bool HandleFocusReset() override;

    /*!
    * @brief No-op.
    * 
    * @param event Event to handle
    * @return Returns false
    */
    bool Handle(sf::Event event) override;


private:

    /*!
    * @brief Sets the color of the ring according to the variable
    * 
    * @param enable Parameter if the circle is highlighted or not
    */
    void EnableRing(bool enable);

    /*!
    * @brief Shared pointer to the associated controller
    */
    std::weak_ptr<ChipController> m_ChipController;

    /*!
    * @brief Shape of the inner part of the chip
    */
    sf::CircleShape m_Circle;

    /*!
    * @brief Shape of the ring around the chip
    */
    sf::CircleShape m_Ring;

    /*!
    *@brief Default color of the chip
    */
    sf::Color m_CircleColor;

    /*!
    *@brief Color of the ring if highlighted
    */
    sf::Color m_HighlightColor;

    /*!
    *@brief Static value of the chips inner radius to the ring
    */
    static constexpr float m_InnerRadius = 10.0f;

    /*!
    *@brief Static value of the chips outer radius including the ring
    */
    static constexpr float m_OuterRadius = 12.0f;


};
