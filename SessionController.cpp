//
// Created by Brendan Berg on 10.03.22.
//

#include "SessionController.hpp"

#include <iostream>
#include <utility>

#include "AppDelegate.hpp"

#include "SessionModel.hpp"

#include "GameController.hpp"


std::shared_ptr<SessionController>
SessionController::MakeSessionController(const std::weak_ptr<GameController>& gameController)
{
    auto controller = std::make_shared<SessionController>(gameController);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_SessionModel->m_SessionController = controller;
    controller->m_SessionController = controller;

    controller->InitGrid();

    return controller;
}


SessionController::SessionController(std::weak_ptr<GameController> gameController)
    : m_GameController(std::move(gameController))
{
    m_SessionModel = std::make_shared<SessionModel>();
    AppDelegate::Get()->RegisterModel(m_SessionModel);

    std::clog << "SessionController constructed" << std::endl;
}


SessionController::~SessionController()
{
    std::clog << "SessionController destructed" << std::endl;
}


void SessionController::Update()
{

}


void SessionController::HandleColumnClick(int column)
{
    m_SessionModel->AddChip(column);
}


void SessionController::InitGrid()
{
    if (auto game = m_GameController.lock())
    {
        m_Grid.resize(game->GetColumns());
        for (auto column = 0; column < game->GetColumns(); ++column)
        {
            m_Grid[column].reserve(game->GetRows());
            for (auto row = 0; row < game->GetRows(); ++row)
            {
                auto gridField = GridFieldController::MakeGridFieldController(m_SessionController, column, row);
                m_Grid[column].push_back(gridField);
            }
        }
    }
}


bool SessionController::IsOngoing() const
{
    return m_SessionModel->IsOngoing();
}


