//
// Created by Florian Wolff on 09.03.22.
//

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseView.hpp"

class TextFieldController;

/*!
 * @brief TextFieldView displays a text field on the screen and handles mouse events as well as typing events as long as
 * the text field is in focus.
 */
class TextFieldView : public BaseView
{
    friend TextFieldController;


public:

    /*!
     * @brief Constructor initializes all SFML elements.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width width on the screen
     * @param placeholder placeholder string to display when no text is entered
     * @param highlightColor color for the outline and text to use while the text field is in focus
     */
    TextFieldView(float x, float y, float width, const std::string& placeholder, sf::Color highlightColor);

    /*!
     * @brief Draws the text field to the RenderWindow in the AppDelegate.
     */
    void Draw() override;

    /*!
     * @brief Sets m_InFocus to false before a new MouseButtonPressed event will be send.
     *
     * @return Was the text field in focus before the reset?
     */
    bool HandleFocusReset() override;

    /*!
     * @brief Reacts to MouseButtonPressed events inside the boundaries by activating the focus. If a TextEntered or
     * KeyPressed event occurs whilst this text field is in focus, the event will be forwarded to the associated
     * controller.
     *
     * @param event SFML-Event
     * @return Was the event handled by the view?
     */
    bool Handle(sf::Event event) override;

    /*!
     * @brief Sets the highlight color for the text field.
     *
     * @param highlightColor highlight color
     */
    void SetHighlightColor(sf::Color highlightColor);

    /*!
     * @brief Overrides the text entered into the text field.
     *
     * @param text text string to display
     */
    void SetText(const std::string& text);


private:

    /*!
     * @brief Sets the outline color of the text field according to its focus status.
     */
    void UpdateView();

    /*!
     * @brief Weak pointer to the associated controller.
     */
    std::weak_ptr<TextFieldController> m_TextFieldController;

    /*!
     * @brief SFML-RectangleShape: Text field boundaries.
     */
    sf::RectangleShape m_TextField;

    /*!
     * @brief SFML-Text: Graphical representation of the text inside the text field.
     */
    sf::Text m_TextShape;

    /*!
     * @brief SFML-Text: Graphical representation of the placeholder text that will be displayed as long as the entered
     * string is empty in a discrete color.
     */
    sf::Text m_PlaceholderShape;

    /*!
   * @brief SFML-Font: Font in which the text will be displayed.
   */
    sf::Font m_Font;

    /*!
     * @brief Color for the outline of the field while in focus as well as the entered text.
     */
    sf::Color m_HighlightColor;

    /*!
     * @brief Is the text field currently in focus?
     */
    bool m_InFocus = false;
};
