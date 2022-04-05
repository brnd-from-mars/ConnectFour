//
// Created by Brendan Berg on 13.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"


/*!
* @brief ArrowView class represents the Arrow to display which players turn it is
*/
class ArrowView : public BaseView
{

public:
    /*!
    * @brief Static factory function creates a new arrow
    * 
    * @param x X-coordinate of the arrow on the screen
    * @param y Y-coordinate of the arrow on the screen
    * @param color Color of the displayed arrow
    * @param layer Layer of the arrow object
    * @return Shared pointer to the ArrowView
    */
    static std::shared_ptr<ArrowView> MakeArrow(float x, float y, sf::Color color, int layer = 0);


    /*!
    * @brief Constructor creates the associated arrow
    * 
    * @param x X-coordinate of the arrow on the screen
    * @param y Y-coordinate of the Arrow on the screen
    * @param color Color of the arrow
    * @param layer Layer of the arrow
    */
    ArrowView(float x, float y, sf::Color color, int layer);


    /*!
    *@brief Adresses the AppDelegate and draws the arrow on the screen
    */
    void Draw() override;

    /*!
    * @brief Sets the position of the arrow
    *
    * @param x X-coordinate of the arrow on the screen
    * @param y Y-coordinate of the arrow on the screen
    */
    void SetPosition(float x, float y);

    /*!
    * @brief No-op.
    * 
    * @return Returns false
    */
    bool HandleFocusReset() override;

    /*!
    * @brief No-op.
    *
    * @return Returns false
    */
    bool Handle(sf::Event event) override;


private:
    /*!
    * @brief Shape of the arrowhead
    */
    sf::ConvexShape m_ArrowHead;

    /*!
    * @brief Shape of the arrowbody
    */
    sf::ConvexShape m_ArrowBody;


};

