//
// Created by Brendan Berg on 13.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseController.hpp"

class ClockModel;
class ClockView;


/*!
 * @brief ClockController class represents the session clock that measures and shows the game time.
 */
class ClockController : public BaseController
{
    friend ClockModel;
    friend ClockView;


public:

    /*!
     * @brief Static factory function creates a new clock and sets references between the MVC elements.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param color text color
     * @return shared pointer to the new ClockController
     */
    static std::shared_ptr<ClockController> MakeClock(float x, float y, sf::Color color);

    /*!
     * @brief Constructor creates associated ClockModel and ClockView.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param color text color
     */
    ClockController(float x, float y, sf::Color color);

    /*!
     * @brief No-op.
     */
    void Update() override;

    /*!
     * @brief Holds the clock and stops the separating dots in the view from blinking.
     */
    void Stop();

    /*!
     * @brief Returns the totals seconds to this point in time or when the clock was stopped.
     * @return total seconds
     */
    int GetTotalSeconds() const;


private:

    /*!
     * @brief Updates the text displayed in the ClockView.
     *
     * @param minutes number of minutes that passed
     * @param seconds number of seconds that passed since the last minute ended
     * @param millis number of milliseconds that passed since the last seconds ended
     */
    void SetClockView(int minutes, int seconds, int millis);

    /*!
     * @brief Shared pointer (ownership) to the ClockModel.
     */
    std::shared_ptr<ClockModel> m_ClockModel;

    /*!
     * @brief Shared pointer (ownership) to the ClockView.
     */
    std::shared_ptr<ClockView> m_ClockView;


};
