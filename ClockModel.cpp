//
// Created by Brendan Berg on 13.03.22.
//

#include "ClockModel.hpp"
#include "ClockController.hpp"


ClockModel::ClockModel()
{
    // save time point when started
    m_StartTime = std::chrono::system_clock::now();
}


void ClockModel::Update()
{
    if (auto controller = m_ClockController.lock())
    {
        // get std::chrono duration until now or the stop time
        auto duration = (m_Stopped ? m_EndTime : std::chrono::system_clock::now()) - m_StartTime;
        auto dMinutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
        auto dSeconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        auto dMillis = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

        // split duration into separate minutes, seconds and milliseconds
        auto minutes = dMinutes.count();
        auto seconds = dSeconds.count() - 60 * minutes;
        auto millis = dMillis.count() - 1000 * (60 * minutes + seconds);

        // update view
        controller->SetClockView(minutes, seconds, millis);
    }
}


void ClockModel::Stop()
{
    // save time point when stopped
    m_Stopped = true;
    m_EndTime = std::chrono::system_clock::now();
}


int ClockModel::GetTotalSeconds() const
{
    // get std::chrono duration until now or the stop time
    auto duration = (m_Stopped ? m_EndTime : std::chrono::system_clock::now()) - m_StartTime;
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    // return seconds as integer
    return seconds.count();
}
