//
// Created by Brendan Berg on 10.03.22.
//

#include "SessionController.hpp"

#include <iostream>
#include <utility>

#include "AppDelegate.hpp"

#include "GameController.hpp"


std::shared_ptr<SessionController>
SessionController::MakeSessionController(std::weak_ptr<GameController> gameController)
{
    auto controller = std::make_shared<SessionController>(std::move(gameController));
    AppDelegate::Get()->RegisterController(controller);

    return controller;
}


SessionController::SessionController(std::weak_ptr<GameController> gameController)
    : m_GameController(std::move(gameController))
{
    std::clog << "SessionController constructed" << std::endl;
}


SessionController::~SessionController()
{
    std::clog << "SessionController destructed" << std::endl;
}


void SessionController::Update()
{
    i--;
    if (i == 0) m_Ongoing = false;
}

bool SessionController::IsOngoing() const
{
    return m_Ongoing;
}
