//
// Created by Brendan Berg on 10.03.22.
//

#include "SessionController.hpp"

#include <iostream>
#include <utility>

#include "AppDelegate.hpp"

#include "GameController.hpp"


std::shared_ptr<SessionController>
SessionController::MakeSessionController(const std::weak_ptr<GameController>& gameController)
{
    auto controller = std::make_shared<SessionController>(gameController);
    AppDelegate::Get()->RegisterController(controller);

    return controller;
}


SessionController::SessionController(std::weak_ptr<GameController> gameController)
    : m_GameController(std::move(gameController))
{
    if (auto game = m_GameController.lock())
    {
        m_ChipContainer.resize(game->GetColumns());
        // TODO: remove
        m_ChipContainer[0].push_back(ChipController::MakeChip(1, 0, 0));
        m_ChipContainer[1].push_back(ChipController::MakeChip(2, 1, 0));
        m_ChipContainer[1].push_back(ChipController::MakeChip(1, 1, 1));
    }
    std::clog << "SessionController constructed" << std::endl;
}


SessionController::~SessionController()
{
    std::clog << "SessionController destructed" << std::endl;
}


void SessionController::Update()
{

}

bool SessionController::IsOngoing() const
{
    return m_Ongoing;
}
