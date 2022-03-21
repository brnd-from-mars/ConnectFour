//
// Created by Brendan Berg on 13.03.22.
//

#pragma once

#include <memory>
#include <chrono>

#include "BaseModel.hpp"

class ClockController;


class ClockModel : public BaseModel
{
    friend ClockController;


public:

    ClockModel();

    void Update() override;


private:

    void Stop();

    int GetTotalSeconds() const;

    std::weak_ptr<ClockController> m_ClockController;

    std::chrono::time_point<std::chrono::system_clock> m_StartTime;
    std::chrono::time_point<std::chrono::system_clock> m_EndTime;

    bool m_Stopped = false;


};
