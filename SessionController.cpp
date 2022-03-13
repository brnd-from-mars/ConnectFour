//
// Created by Brendan Berg on 10.03.22.
//

#include "SessionModel.hpp"
#include "SessionController.hpp"

#include <iostream>
#include <utility>

#include "AppDelegate.hpp"

#include "GameController.hpp"


std::shared_ptr<SessionController>
SessionController::MakeSessionController(const std::weak_ptr<GameController>& gameController, int columns, int rows)
{
    auto controller = std::make_shared<SessionController>(gameController, columns, rows);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_SessionModel->m_SessionController = controller;
    controller->m_SessionController = controller;

    controller->InitTerminateGameButton();
    controller->InitNamePlayer1TextField();
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
    if (m_SessionModel->m_State == SessionState::inGame)
    {
        const sf::Vector2f arrowPositions[2] = {sf::Vector2f(1062.5f, 162.5f), sf::Vector2f(1162.5f, 212.5f)};
        auto currentPlayer = m_SessionModel->m_CurrentPlayer;
        auto position = arrowPositions[(m_ColorChange ? 3 - currentPlayer : currentPlayer) - 1];
        m_CurrentPlayerArrow->SetPosition(position.x, position.y);
    }
}


void SessionController::InitTerminateGameButton()
{
    m_TerminateGameButton = ButtonController::MakeButton(932.0f, 625.0f, 218.0f, "TERMINATE GAME",
                                                         ColorPalette::Orange, ColorPalette::BasestarDark);
    auto wController = m_SessionController;
    m_TerminateGameButton->RegisterMousePressCallback([wController]()
                                                      {
                                                          if (auto controller = wController.lock())
                                                          {
                                                              controller->HandleTerminateGamePress();
                                                          }
                                                      });
}


void SessionController::InitNamePlayer1TextField()
{
    m_NamePlayer1TextField = TextFieldController::MakeTextField(750.0f, 150.0f, 300.0f, "Player1", ColorPalette::Pred);
    auto wController = m_SessionController;
    m_NamePlayer1TextField->RegisterEnterKeyPressCallback([wController]()
                                                          {
                                                              if (auto controller = wController.lock())
                                                              {
                                                                  controller->HandleNamePlayer1Enter();
                                                              }
                                                          });
}


void SessionController::InitNamePlayer2TextField()
{
    m_VSTextView = TextView::MakeText(765.0f, 185.0f, 40, "Tron", "VS.", ColorPalette::Orange);

    m_NamePlayer2TextField = TextFieldController::MakeTextField(850.0f, 200.0f, 300.0f, "Player2", ColorPalette::Cyan);
    auto wController = m_SessionController;
    m_NamePlayer2TextField->RegisterEnterKeyPressCallback([wController]()
                                                          {
                                                              if (auto controller = wController.lock())
                                                              {
                                                                  controller->HandleNamePlayer2Enter();
                                                              }
                                                          });
}


void SessionController::InitPickColorPrompt()
{
    m_ColorPickingPlayer = AppDelegate::Get()->GetRandomNumber() % 7 % 2 + 1;
    auto playerName = (m_ColorPickingPlayer == 1 ? m_NamePlayer1TextField : m_NamePlayer2TextField)->GetText();
    playerName = playerName.append(":");
    m_StatusNameText = TextView::MakeText(750.0f, 250.0f, 20, "Standard",
                                          playerName, ColorPalette::Orange);
    m_StatusPromptText = TextView::MakeText(750.0f, 275.0f, 20, "Standard",
                                            "Pick your color!", ColorPalette::Orange);

    auto wController = m_SessionController;

    m_ColorPickerPredButton = ButtonController::MakeButton(975.0f, 275.0f, 75.0f, "R3D",
                                                           ColorPalette::Pred, ColorPalette::BasestarDark);
    m_ColorPickerPredButton->RegisterMousePressCallback([wController]()
                                                        {
                                                            if (auto controller = wController.lock())
                                                            {
                                                                controller->HandleColorPickerPredPress();
                                                            }
                                                        });

    m_ColorPickerCyanButton = ButtonController::MakeButton(1075.0f, 275.0f, 75.0f, "BLU3",
                                                           ColorPalette::Cyan, ColorPalette::BasestarDark);
    m_ColorPickerCyanButton->RegisterMousePressCallback([wController]()
                                                        {
                                                            if (auto controller = wController.lock())
                                                            {
                                                                controller->HandleColorPickerCyanPress();
                                                            }
                                                        });
}


void SessionController::InitArrow()
{
    m_CurrentPlayerArrow = ArrowView::MakeArrow(0.0f, 0.0f, ColorPalette::Orange);
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


void SessionController::HandleTerminateGamePress()
{
    m_SessionModel->m_State = SessionState::terminated;
}


void SessionController::HandleNamePlayer1Enter()
{
    if (m_SessionModel->m_State == SessionState::namePlayer1)
    {
        InitNamePlayer2TextField();
    }

    m_SessionModel->HandleNamePlayer1Enter();
}


void SessionController::HandleNamePlayer2Enter()
{
    if (m_SessionModel->m_State == SessionState::namePlayer2)
    {
        InitPickColorPrompt();
    }
    m_SessionModel->HandleNamePlayer2Enter();
}


void SessionController::HandleColorPickerPredPress()
{
    if (m_SessionModel->m_State != SessionState::colorPick)
    {
        return;
    }

    HandleColorPick(m_ColorPickingPlayer == 2);
}


void SessionController::HandleColorPickerCyanPress()
{
    if (m_SessionModel->m_State != SessionState::colorPick)
    {
        return;
    }

    HandleColorPick(m_ColorPickingPlayer == 1);
}


void SessionController::HandleColorPick(bool changeColors)
{
    if (m_SessionModel->m_State != SessionState::colorPick)
    {
        return;
    }

    if (changeColors)
    {
        m_NamePlayer1TextField->SetHighlightColor(ColorPalette::Cyan);
        m_NamePlayer2TextField->SetHighlightColor(ColorPalette::Pred);
        m_ColorChange = true;
    }

    m_StatusPromptText.reset();
    m_StatusNameText.reset();
    m_ColorPickerPredButton.reset();
    m_ColorPickerCyanButton.reset();

    InitArrow();
    m_SessionModel->HandleColorPick();
}


void SessionController::HandleColumnClick(int column)
{
    m_SessionModel->AddChip(column);
}


void SessionController::HandleGameEnd(PlayerState winState)
{
    m_CurrentPlayerArrow.reset();

    if (winState == PlayerState::none)
    {
        return;
    }
    else if (winState == PlayerState::tie)
    {
        m_StatusPromptText = TextView::MakeText(750.0f, 275.0f, 20, "Standard",
                                                "It's a tie! (-;", ColorPalette::Orange);
    }
    else
    {
        auto winningPlayerTextField = m_ColorChange != (winState == PlayerState::player1);
        auto playerName = (winningPlayerTextField ? m_NamePlayer1TextField : m_NamePlayer2TextField)->GetText();
        playerName = playerName.append(":");
        m_StatusNameText = TextView::MakeText(750.0f, 250.0f, 20, "Standard",
                                              playerName, ColorPalette::Orange);
        m_StatusPromptText = TextView::MakeText(750.0f, 275.0f, 20, "Standard",
                                                "You are the winner!", ColorPalette::Orange);
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
