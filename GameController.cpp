//
// Created by Brendan Berg on 10.03.22.
//

#include "GameController.hpp"

#include <iostream>

#include "AppDelegate.hpp"


std::shared_ptr<GameController> GameController::MakeGameController(int columns, int rows)
{
    auto controller = std::make_shared<GameController>(columns, rows);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_GameController = controller;

    return controller;
}


GameController::GameController(int columns, int rows)
    : m_Columns(columns), m_Rows(rows)
{
    std::clog << "GameController constructed" << std::endl;
}


GameController::~GameController()
{
    std::clog << "GameController destructed" << std::endl;
}


void GameController::Update()
{
    // create new session if either no session exists or existing session was finished
    if (!m_SessionController || !m_SessionController->IsOngoing())
    {
        m_SessionController = SessionController::MakeSessionController(m_GameController);
    }
}


int GameController::GetColumns() const
{
    return m_Columns;
}


int GameController::GetRows() const
{
    return m_Rows;
}
