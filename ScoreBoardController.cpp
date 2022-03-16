//
// Created by Brendan Berg on 15.03.22.
//

#include <sstream>
#include <iomanip>

#include "ScoreBoardModel.hpp"
#include "ScoreBoardView.hpp"
#include "ScoreBoardController.hpp"

#include "AppDelegate.hpp"


std::shared_ptr<ScoreBoardController> ScoreBoardController::MakeScoreBoard(float x, float y, float width)
{
    auto controller = std::make_shared<ScoreBoardController>(x, y, width);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_ScoreBoardController = controller;

    controller->InitButtons();
    controller->UpdateView();

    return controller;
}


ScoreBoardController::ScoreBoardController(float x, float y, float width)
{
    m_ScoreBoardView = std::make_shared<ScoreBoardView>(x, y, width);
    AppDelegate::Get()->RegisterView(m_ScoreBoardView);

    m_ScoreBoardModel = std::make_shared<ScoreBoardModel>();
    AppDelegate::Get()->RegisterModel(m_ScoreBoardModel);

    m_PrevScoreBoardButton = ButtonController::MakeButton(x + width - 50.0f, y, 25.f, "<", ColorPalette::Orange);
    m_NextScoreBoardButton = ButtonController::MakeButton(x + width - 25.0f, y, 25.f, ">", ColorPalette::Orange);
}


void ScoreBoardController::Update()
{ }


void ScoreBoardController::AddGame(GameData game)
{
    m_ScoreBoardModel->AddGame(std::move(game));
}


void ScoreBoardController::InitButtons()
{
    auto wController = m_ScoreBoardController;

    m_PrevScoreBoardButton->RegisterMousePressCallback([wController]()
                                                       {
                                                           if (auto controller = wController.lock())
                                                           {
                                                               controller->PrevScoreBoard();
                                                           }
                                                       });
    m_NextScoreBoardButton->RegisterMousePressCallback([wController]()
                                                       {
                                                           if (auto controller = wController.lock())
                                                           {
                                                               controller->NextScoreBoard();
                                                           }
                                                       });
}


void ScoreBoardController::PrevScoreBoard()
{
    auto current = static_cast<int>(m_CurrentScoreBoard);
    constexpr auto max = static_cast<int>(ScoreBoardType::num);

    current = (current + max - 1) % max;
    m_CurrentScoreBoard = static_cast<ScoreBoardType>(current);

    UpdateView();
}


void ScoreBoardController::NextScoreBoard()
{
    auto current = static_cast<int>(m_CurrentScoreBoard);
    constexpr auto max = static_cast<int>(ScoreBoardType::num);

    current = (current + 1) % max;
    m_CurrentScoreBoard = static_cast<ScoreBoardType>(current);

    UpdateView();
}


void ScoreBoardController::UpdateView()
{
    switch (m_CurrentScoreBoard)
    {
        case ScoreBoardType::mostVictories:
            m_ScoreBoardView->SetHeadline("Most wins");
            m_ScoreBoardModel->SortPlayerListVictories();
            for (int i = 0; i < 5; ++i)
            {
                auto player = m_ScoreBoardModel->m_PlayerList[-i - 1];
                m_ScoreBoardView->SetLine(i,
                                          player ? player->name : "XXX",
                                          player ? std::to_string(player->victories) : "X");
            }
            break;

        case ScoreBoardType::bestKD:
            m_ScoreBoardView->SetHeadline("Highest win ratio");
            m_ScoreBoardModel->SortPlayerListKD();
            for (int i = 0; i < 5; ++i)
            {
                auto player = m_ScoreBoardModel->m_PlayerList[-i - 1];
                m_ScoreBoardView->SetLine(i,
                                          player ? player->name : "XXX",
                                          player ? std::to_string(static_cast<int>(
                                                        100 * player->victories / player->games)).append(" %") : "%");
            }
            break;

        case ScoreBoardType::leastMoves:
            m_ScoreBoardView->SetHeadline("Least moves to win");
            m_ScoreBoardModel->SortGameListMoves();
            for (int i = 0; i < 5; ++i)
            {
                auto game = m_ScoreBoardModel->m_GameList[i];
                m_ScoreBoardView->SetLine(i,
                                          game ? game->winningPlayer : "XXX",
                                          game ? std::to_string(game->moves) : "X");
            }
            break;

        case ScoreBoardType::leastTime:
            m_ScoreBoardView->SetHeadline("Least time to win");
            m_ScoreBoardModel->SortGameListTime();
            for (int i = 0; i < 5; ++i)
            {
                auto game = m_ScoreBoardModel->m_GameList[i];
                if (game)
                {
                    std::stringstream time;
                    time << std::setw(2) << std::setfill('0');
                    int minutes = game->time / 60;
                    if (minutes >= 100)
                    {
                        time << "XX";
                    }
                    else
                    {
                        time << minutes;
                    }
                    time << ":" << std::setw(2) << std::setfill('0') << game->time - minutes * 60;
                    m_ScoreBoardView->SetLine(i, game->winningPlayer, time.str());
                }
                else
                {
                    m_ScoreBoardView->SetLine(i, "XXX", "XX:XX");
                }
            }
            break;

        default:
            break;
    }
}
