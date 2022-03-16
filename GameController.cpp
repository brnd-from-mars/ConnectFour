//
// Created by Brendan Berg on 10.03.22.
//

#include <iostream>

#include "GameController.hpp"

#include "AppDelegate.hpp"


std::shared_ptr<GameController> GameController::MakeGameController(int columns, int rows)
{
    auto controller = std::make_shared<GameController>(columns, rows);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_GameModel->m_GameController = controller;
    controller->m_GameController = controller;

    controller->InitScoreBoard();

    return controller;
}


GameController::GameController(int columns, int rows)
{
    m_GameModel = std::make_shared<GameModel>(columns, rows);
    AppDelegate::Get()->RegisterModel(m_GameModel);

    m_HeadlineOrange = TextView::MakeText(52.0f, 26.0f, 75, "Tron", "C0nnect F0ur", ColorPalette::Orange, 1);
    m_HeadlineCyan = TextView::MakeText(48.0f, 22.0f, 75, "Tron", "C0nnect F0ur", ColorPalette::Cyan, 2);

    std::clog << "GameController constructed" << std::endl;
}


GameController::~GameController()
{
    std::clog << "GameController destructed" << std::endl;
}


void GameController::Update()
{
    // create new session if either no session exists or existing session was finished
    if (!m_Session)
    {
        m_Session = SessionController::MakeSessionController(m_GameController,
                                                             m_GameModel->m_Columns,
                                                             m_GameModel->m_Rows);
    }
    else if (!m_Session->IsOngoing())
    {
        if (m_Session->IsTerminated())
        {
            m_Session = SessionController::MakeSessionController(m_GameController,
                                                                 m_GameModel->m_Columns,
                                                                 m_GameModel->m_Rows);
        }
        else
        {
            m_Session = SessionController::MakeSessionController(*m_Session);
        }
    }
}


void GameController::AddGame(GameData game)
{
    m_ScoreBoard->AddGame(std::move(game));
}


void GameController::AddTie(const GameData& game)
{
    m_ScoreBoard->AddTie(game);
}


void GameController::InitScoreBoard()
{
    m_ScoreBoard = ScoreBoardController::MakeScoreBoard(750.0f, 350.0f, 400.0f);
}
