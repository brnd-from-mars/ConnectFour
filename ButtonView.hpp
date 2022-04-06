//
// Created by Florian Wolff on 10.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class ButtonController;


/*!
 * @brief ButtonView displays the current time on the screen and handles mouse events.
 */
class ButtonView : public BaseView
{
    friend ButtonController;


public:

    /*!
     * @brief Constructor loads the font and initializes all SFML elements.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width width on the screen
     * @param text text inside the button
     * @param defaultColor default display color for the button
     * @param highlightColor highlight (pressed) color for the button
     */
    ButtonView(float x, float y, float width, const std::string& text,
               sf::Color defaultColor, sf::Color highlightColor);

    /*!
     * @brief Draws the button to the RenderWindow in the AppDelegate.
     */
    void Draw() override;

    /*!
     * @brief No-op.
     *
     * @return false
     */
    bool HandleFocusReset() override;

    /*!
     * @brief Checks if a MouseButtonPressed SFML-Event is within its boundaries to update the view. Reports a
     * HandleMousePress event back to the reported after the MouseButtonReleased SFML-Event also occurred within its
     * boundaries.
     *
     * @param event SFML-Event
     * @return Was the event handled by the view?
     */
    bool Handle(sf::Event event) override;


private:

    /*!
     * @brief Updates the view by setting the highlight color for the button while it is pressed.
     */
    void UpdateView();

    /*!
     * @brief Weak pointer to the associated controller.
     */
    std::weak_ptr<ButtonController> m_ButtonController;

    /*!
     * @brief SFML-RectangleShape: Button outline and clickable area.
     */
    sf::RectangleShape m_ButtonField;

    /*!
     * @brief SFML-Text: Text displayed on the button.
     */
    sf::Text m_TextShape;

    /*!
     * @brief SFML-Font: Font to be used for the text inside the button.
     */
    sf::Font m_Font;

    /*!
     * @brief Default color for the outline and text inside the button.
     */
    sf::Color m_DefaultColor;

    /*!
     * @brief Color for the outline and text inside the button to be used while the button is pressed.
     */
    sf::Color m_HighlightColor;

    /*!
     * @brief Is the button currently pressed?
     */
    bool m_Pressed = false;


};
