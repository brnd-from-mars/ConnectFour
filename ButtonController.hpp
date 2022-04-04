//
// Created by Brendan Berg on 12.03.22.
//

#pragma once

#include <memory>
#include <optional>
#include <functional>

#include <SFML/Graphics.hpp>

#include "BaseController.hpp"

#include "AppDelegate.hpp"
#include "ConnectFourUtility.hpp"

class ButtonView;


/*!
 * @brief ButtonController class represents a button that reacts to clicks by the user.
 */
class ButtonController : public BaseController
{
    friend ButtonView;


public:

    /*!
     * @brief Static factory function creates a new button and sets references between the MVC elements.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width width on the screen
     * @param text text inside the button
     * @param defaultColor default display color for the button
     * @param highlightColor highlight (pressed) color for the button
     * @return shared pointer to the new ButtonController
     */
    static std::shared_ptr<ButtonController> MakeButton(float x, float y, float width, const std::string& text,
                                                        sf::Color defaultColor,
                                                        sf::Color highlightColor = ColorPalette::BasestarDark);

    /*!
     * @brief Constructor creates associated ButtonView.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width width on the screen
     * @param text text inside the button
     * @param defaultColor default display color for the button
     * @param highlightColor highlight (pressed) color for the button
     */
    ButtonController(float x, float y, float width, const std::string& text,
                     sf::Color defaultColor, sf::Color highlightColor);

    /*!
     * @brief No-op.
     */
    void Update() override;

    /*!
     * @brief Registers a given function pointer as the callback for a mouse press event
     *
     * @param callback void() function pointer to the event listener
     */
    void RegisterMousePressCallback(const std::function<void()>& callback);


private:

    /*!
     * @brief Handles mouse press events by pushing them to the callback.
     */
    void HandleMousePress();

    /*!
     * @brief shared pointer (ownership) to the ButtonView
     */
    std::shared_ptr<ButtonView> m_ButtonView;

    /*!
     * @brief function pointer for the mouse press event callback
     */
    std::optional<std::function<void()>> m_MousePressCallback = std::nullopt;


};
