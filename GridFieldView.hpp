 //
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class GridFieldController;

/*!
 * @brief GridFieldView respresents one field of the grid each
 */
class GridFieldView : public BaseView
{
    friend GridFieldController;


public:
    /*!
    * @brief Constructor creates the GridFieldView
    *
    * @param x X-coordinate on the screen
    * @param y Y-coordinate on the screen
    */
    GridFieldView(float x, float y);

    /*!
    *@brief Adresses the AppDelegate and draws the grid field on the screen
    */
    void Draw() override;

    /*!
    * @brief No-op.
    *
    * @return Returns false
    */
    bool HandleFocusReset() override;

    /*!
     * @brief Checks if a mouseclick event is within its boundarys and reports back to the controller if so
     *
     * @param event Event which is given to handle
     * @return Returns false
     */
    bool Handle(sf::Event event) override;


private:

    /*!
     * @brief Gets the center of the field
     * 
     * @return Vector to center
     */
    sf::Vector2f GetCenter() const;

    /*!
     * @brief Weak pointer to the associated controller
     */
    std::weak_ptr<GridFieldController> m_GridFieldController;

    /*!
    * @brief Shape of the field
    */
    sf::RectangleShape m_FieldShape;

    /*!
    *@brief Static value of the fields edge length
    */
    static constexpr float m_Size = 25.0;

    /*!
    *@brief Static value of the fields outline thickness
    */
    static constexpr float m_Outline = 1.0;


};
