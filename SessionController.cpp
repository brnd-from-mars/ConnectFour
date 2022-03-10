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
SessionController::MakeSessionController(const std::weak_ptr<GameController>& gameController, int columns, int rows)
{
    auto controller = std::make_shared<SessionController>(gameController, columns, rows);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_SessionModel->m_SessionController = controller;
    controller->m_SessionController = controller;

    controller->InitGrid();

    return controller;
}


SessionController::SessionController(std::weak_ptr<GameController> gameController, int columns, int rows)
    : m_GameController(std::move(gameController))
{
    m_SessionModel = std::make_shared<SessionModel>(columns, rows);
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
        m_Grid.resize(m_SessionModel->m_Columns);
        for (auto column = 0; column < m_SessionModel->m_Columns; ++column)
        {
            m_Grid[column].reserve(m_SessionModel->m_Rows);
            for (auto row = 0; row < m_SessionModel->m_Rows; ++row)
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


int SessionController::GetPlayerAt(int column, int row) const
{
    return m_Grid[column][row]->GetPlayer();
}
