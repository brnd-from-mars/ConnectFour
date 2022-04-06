//
// Created by Brendan Berg on 13.03.22.
//

#pragma once

#include <memory>
#include <chrono>

#include "BaseModel.hpp"

class ClockController;


/*!
 * @brief ClockModel represents the current time or the time until the clock was stopped.
 */
class ClockModel : public BaseModel
{
    friend ClockController;


public:

    /*!
     * @brief Constructor starts the clock.
     */
    ClockModel();

    /*!
     * @brief Computes the duration until now or the stop time and pushes it to the controller.
     */
    void Update() override;


private:

    /*!
     * @brief Stops the clock from running.
     */
    void Stop();

    /*!
     * @brief Returns the totals seconds to this point in time or when the clock was stopped.
     *
     * @return total seconds
     */
    int GetTotalSeconds() const;

    /*!
     * @brief Weak pointer to parent ClockController.
     */
    std::weak_ptr<ClockController> m_ClockController;

    /*!
     * @brief Point in time when the instance was constructed.
     */
    std::chrono::time_point<std::chrono::system_clock> m_StartTime;

    /*!
     * @brief Point in time when Stop was called.
     */
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;

    /*!
     * @brief Is the clock stopped?
     */
    bool m_Stopped = false;


};
