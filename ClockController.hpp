//
// Created by Brendan Berg on 13.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseController.hpp"

class ClockModel;
class ClockView;


class ClockController : public BaseController
{
    friend ClockModel;
    friend ClockView;


public:

    static std::shared_ptr<ClockController> MakeClock(float x, float y, sf::Color color);

    ClockController(float x, float y, sf::Color color);

    void Update() override;

    void Stop();

    int GetTotalSeconds() const;


private:

    void SetClockView(int minutes, int seconds, int millis);

    std::shared_ptr<ClockModel> m_ClockModel;
    std::shared_ptr<ClockView> m_ClockView;


};
