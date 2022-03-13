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
{ }


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
    auto randomPlayerName = (m_ColorPickingPlayer == 1 ? m_NamePlayer1TextField : m_NamePlayer2TextField)->GetText();
    auto message = randomPlayerName.append(": Pick your color!");
    m_ColorPickerPromptTextView = TextView::MakeText(750.0f, 250.0f, 20, "Standard", message, ColorPalette::Orange);

    auto wController = m_SessionController;

    m_ColorPickerPredButton = ButtonController::MakeButton(750.0f, 300.0f, 75.0f, "R3D",
                                                           ColorPalette::Pred, ColorPalette::BasestarDark);
    m_ColorPickerPredButton->RegisterMousePressCallback([wController]()
                                                        {
                                                            if (auto controller = wController.lock())
                                                            {
                                                                controller->HandleColorPickerPredPress();
                                                            }
                                                        });

    m_ColorPickerCyanButton = ButtonController::MakeButton(850.0f, 300.0f, 75.0f, "BLU3",
                                                           ColorPalette::Cyan, ColorPalette::BasestarDark);
    m_ColorPickerCyanButton->RegisterMousePressCallback([wController]()
                                                        {
                                                            if (auto controller = wController.lock())
                                                            {
                                                                controller->HandleColorPickerCyanPress();
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


void SessionController::HandleTerminateGamePress()
{
    m_SessionModel->m_State = SessionModel::State::terminated;
}


void SessionController::HandleColumnClick(int column)
{
    m_SessionModel->AddChip(column);
}


void SessionController::HandleNamePlayer1Enter()
{
    if (m_SessionModel->m_State == SessionModel::State::namePlayer1)
    {
        InitNamePlayer2TextField();
    }

    m_SessionModel->HandleNamePlayer1Enter();
}


void SessionController::HandleNamePlayer2Enter()
{
    if (m_SessionModel->m_State == SessionModel::State::namePlayer2)
    {
        InitPickColorPrompt();
    }
    m_SessionModel->HandleNamePlayer2Enter();
}


void SessionController::HandleColorPickerPredPress()
{
    if (m_SessionModel->m_State != SessionModel::State::colorPick)
    {
        return;
    }

    HandleColorPick(m_ColorPickingPlayer == 2);
}


void SessionController::HandleColorPickerCyanPress()
{
    if (m_SessionModel->m_State != SessionModel::State::colorPick)
    {
        return;
    }

    HandleColorPick(m_ColorPickingPlayer == 1);
}


void SessionController::HandleColorPick(bool changeColors)
{
    if (m_SessionModel->m_State != SessionModel::State::colorPick)
    {
        return;
    }

    if (changeColors)
    {
        m_NamePlayer1TextField->SetHighlightColor(ColorPalette::Cyan);
        m_NamePlayer2TextField->SetHighlightColor(ColorPalette::Pred);
    }

    m_ColorPickerPromptTextView.reset();
    m_ColorPickerPredButton.reset();
    m_ColorPickerCyanButton.reset();

    m_SessionModel->HandleColorPick();
}


bool SessionController::IsOngoing() const
{
    return m_SessionModel->IsOngoing();
}


int SessionController::GetPlayerAt(int column, int row) const
{
    return m_Grid[column][row]->GetPlayer();
}
