//
// Created by Brendan Berg on 13.03.22.
//

#include "ClockModel.hpp"
#include "ClockView.hpp"
#include "ClockController.hpp"

#include "AppDelegate.hpp"


std::shared_ptr<ClockController> ClockController::MakeClock(float x, float y, sf::Color color)
{
    auto controller = std::make_shared<ClockController>(x, y, color);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_ClockModel->m_ClockController = controller;

    return controller;
}


ClockController::ClockController(float x, float y, sf::Color color)
{
    m_ClockModel = std::make_shared<ClockModel>();
    AppDelegate::Get()->RegisterModel(m_ClockModel);

    m_ClockView = std::make_shared<ClockView>(x, y, color);
    AppDelegate::Get()->RegisterView(m_ClockView);
}


void ClockController::Update()
{ }


void ClockController::Stop()
{
    m_ClockView->m_ForceDotsVisible = true;
    m_ClockModel->Stop();
}


int ClockController::GetTotalSeconds() const
{
    return m_ClockModel->GetTotalSeconds();
}


void ClockController::SetClockView(int minutes, int seconds, int millis)
{
    m_ClockView->SetTime(minutes, seconds, millis);
}
