 //
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class GridFieldController;


/*!
 * @brief GridFieldView displays a single field inside the ConnectFour grid on the screen and handles mouse events.
 */
class GridFieldView : public BaseView
{
    friend GridFieldController;


public:

    /*!
     * @brief Constructor initializes all SFML elements.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     */
    GridFieldView(float x, float y);

    /*!
     * @brief Draws the grid field to the RenderWindow in the AppDelegate.
     */
    void Draw() override;

    /*!
     * @brief No-op.
     *
     * @return false
     */
    bool HandleFocusReset() override;

    /*!
     * @brief Checks if a MouseButtonPressed event occurred within its boundaries and reports back to the controller in
     * that case by triggering a HandleClick event.
     *
     * @param event SFML-Event
     * @return Was the event handled by the view?
     */
    bool Handle(sf::Event event) override;


private:

    /*!
     * @brief Returns the center coordinates of the field.
     * 
     * @return float vector of the center
     */
    sf::Vector2f GetCenter() const;

    /*!
     * @brief Weak pointer to the associated controller.
     */
    std::weak_ptr<GridFieldController> m_GridFieldController;

    /*!
     * @brief SFML-RectangleShape: Grid field.
     */
    sf::RectangleShape m_FieldShape;

    /*!
     * @brief Horizontal and vertical distance between two neighboring fields.
     */
    static constexpr float m_Size = 25.0;

    /*!
     * @brief Padding inside the field for the m_FieldShape.
     */
    static constexpr float m_Outline = 1.0;


};
