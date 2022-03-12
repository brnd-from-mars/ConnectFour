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

    controller->InitNamePlayer1();
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
{ }


void SessionController::InitNamePlayer1()
{
    m_NamePlayer1 = TextFieldController::MakeTextField(750.0f, 150.0f, 300.0f, "Player1", ColorPalette::Pred);
    auto wController = m_SessionController;
    m_NamePlayer1->RegisterEnterKeyPressCallback([wController]()
                                                 {
                                                     if (auto controller = wController.lock())
                                                     {
                                                         controller->HandleNamePlayer1Enter();
                                                     }
                                                 });
}


void SessionController::InitNamePlayer2()
{
    m_NamePlayer2 = TextFieldController::MakeTextField(875.0f, 200.0f, 300.0f, "Player2", ColorPalette::Cyan);
    auto wController = m_SessionController;
    m_NamePlayer2->RegisterEnterKeyPressCallback([wController]()
                                                 {
                                                     if (auto controller = wController.lock())
                                                     {
                                                         controller->HandleNamePlayer2Enter();
                                                     }
                                                 });
}


void SessionController::InitGrid()
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


void SessionController::HandleColumnClick(int column)
{
    m_SessionModel->AddChip(column);
}


void SessionController::HandleNamePlayer1Enter()
{
    m_SessionModel->HandleNamePlayer1Enter();
    InitNamePlayer2();
}


void SessionController::HandleNamePlayer2Enter()
{
    m_SessionModel->HandleNamePlayer2Enter();
}


bool SessionController::IsOngoing() const
{
    return m_SessionModel->IsOngoing();
}


int SessionController::GetPlayerAt(int column, int row) const
{
    return m_Grid[column][row]->GetPlayer();
}
