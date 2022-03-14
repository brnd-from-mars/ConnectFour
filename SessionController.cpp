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

    controller->InitGrid();
    controller->InitGameTerminateButton();
    controller->InitNameTextFields();

    return controller;
}


std::shared_ptr<SessionController>
SessionController::MakeSessionController(const SessionController& oldSessionController)
{
    auto controller = std::make_shared<SessionController>(oldSessionController);
    AppDelegate::Get()->RegisterController(controller);

    controller->m_SessionModel->m_SessionController = controller;
    controller->m_SessionController = controller;

    controller->InitGrid();
    controller->InitGameTerminateButton();
    controller->InitNameTextFields();
    controller->InitArrow();
    controller->InitClock();
    controller->InitGameRestartButton();

    controller->m_NameTextFields[0]->SetText(oldSessionController.m_NameTextFields[0]->GetText());
    controller->m_NameTextFields[1]->SetText(oldSessionController.m_NameTextFields[1]->GetText());

    if (controller->m_SessionModel->m_ColorsChanged)
    {
        controller->m_NameTextFields[0]->SetHighlightColor(ColorPalette::Cyan);
        controller->m_NameTextFields[1]->SetHighlightColor(ColorPalette::Pred);
    }

    return controller;
}


SessionController::SessionController(std::weak_ptr<GameController> gameController, int columns, int rows)
    : m_GameController(std::move(gameController))
{
    m_SessionModel = std::make_shared<SessionModel>(columns, rows);
    AppDelegate::Get()->RegisterModel(m_SessionModel);

    std::clog << "SessionController constructed" << std::endl;
}


SessionController::SessionController(const SessionController& oldSessionController)
    : m_GameController(oldSessionController.m_GameController)
{
    m_SessionModel = std::make_shared<SessionModel>(*oldSessionController.m_SessionModel);
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
        auto position = arrowPositions[m_SessionModel->GetCurrentPlayerIndex()];
        m_CurrentPlayerArrow->SetPosition(position.x, position.y);
    }
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



void SessionController::InitGameTerminateButton()
{
    m_GameTerminateButton = ButtonController::MakeButton(932.0f, 625.0f, 218.0f, "T3RMINAT3 GAM3",
                                                         ColorPalette::Orange);
    auto wController = m_SessionController;
    /*m_GameTerminateButton->RegisterMousePressCallback([wController]()
                                                      {
                                                          if (auto controller = wController.lock())
                                                          {
                                                              controller->HandleGameTerminatePress();
                                                          }
                                                      });*/
}


void SessionController::InitNameTextFields()
{
    m_VSTextView = TextView::MakeText(765.0f, 185.0f, 40, "Tron", "VS.", ColorPalette::Orange);

    auto wController = m_SessionController;
    auto handler = [wController]()
                   {
                       if (auto controller = wController.lock())
                       {
                           controller->HandleNameEnter();
                       }
                   };

    m_NameTextFields[0] = TextFieldController::MakeTextField(750.0f, 150.0f, 300.0f, "Player1", ColorPalette::Pred);
    //m_NameTextFields[0]->RegisterEnterKeyPressCallback(handler);

    m_NameTextFields[1] = TextFieldController::MakeTextField(850.0f, 200.0f, 300.0f, "Player2", ColorPalette::Cyan);
    //m_NameTextFields[1]->RegisterEnterKeyPressCallback(handler);
}


void SessionController::InitColorPickPrompt()
{
    auto playerName = m_SessionModel->GetRandomPlayerForColorPick();
    playerName = playerName.append(":");

    m_StatusNameText = TextView::MakeText(750.0f, 250.0f, 20, "Standard", playerName, ColorPalette::Orange);
    m_StatusPromptText = TextView::MakeText(750.0f, 275.0f, 20, "Standard", "Pick your color!", ColorPalette::Orange);

    auto wController = m_SessionController;

    m_ColorPickButtons[0] = ButtonController::MakeButton(975.0f, 275.0f, 75.0f, "R3D", ColorPalette::Pred);
    /*m_ColorPickButtons[0]->RegisterMousePressCallback([wController]()
                                                      {
                                                          if (auto controller = wController.lock())
                                                          {
                                                              controller->HandleColorPick(0);
                                                          }
                                                      });*/

    m_ColorPickButtons[1] = ButtonController::MakeButton(1075.0f, 275.0f, 75.0f, "BLU3", ColorPalette::Cyan);
    /*m_ColorPickButtons[1]->RegisterMousePressCallback([wController]()
                                                      {
                                                          if (auto controller = wController.lock())
                                                          {
                                                              controller->HandleColorPick(1);
                                                          }
                                                      });*/
}


void SessionController::InitArrow()
{
    m_CurrentPlayerArrow = ArrowView::MakeArrow(0.0f, 0.0f, ColorPalette::Orange);
}


void SessionController::InitClock()
{
    m_Clock = ClockController::MakeClock(995.0f, 25.0f, ColorPalette::Orange);
}


void SessionController::InitGameRestartButton()
{
    m_GameRestartButton = ButtonController::MakeButton(750.0f, 625.0f, 120.0f, "R3START",
                                                         ColorPalette::Orange);
    auto wController = m_SessionController;
    /*m_GameRestartButton->RegisterMousePressCallback([wController]()
                                                    {
                                                        if (auto controller = wController.lock())
                                                        {
                                                            controller->HandleGameRestartPress();
                                                        }
                                                    });*/
}


void SessionController::HandleColumnClick(int column)
{
    m_SessionModel->AddChip(column);
}


void SessionController::HandleGameTerminatePress()
{
    m_SessionModel->m_State = SessionState::terminated;
}


void SessionController::HandleNameEnter()
{
    if (!m_SessionModel->HandleInitialNameEnter())
    {
        return;
    }

    InitColorPickPrompt();
}


void SessionController::HandleColorPick(int color)
{
    if (!m_SessionModel->HandleColorPick(color))
    {
        return;
    }

    if (m_SessionModel->m_ColorsChanged)
    {
        m_NameTextFields[0]->SetHighlightColor(ColorPalette::Cyan);
        m_NameTextFields[1]->SetHighlightColor(ColorPalette::Pred);
    }

    m_StatusPromptText.reset();
    m_StatusNameText.reset();
    m_ColorPickButtons[0].reset();
    m_ColorPickButtons[1].reset();

    InitArrow();
    InitClock();
    InitGameRestartButton();
}


void SessionController::HandleGameRestartPress()
{
    m_SessionModel->m_State = SessionState::restarted;
}


void SessionController::HandleGameEnd(PlayerState winState, std::string playerName)
{
    m_CurrentPlayerArrow.reset();
    m_Clock->Stop();

    if (winState == PlayerState::none)
    {
        return;
    }
    else if (winState == PlayerState::tie)
    {
        m_StatusPromptText = TextView::MakeText(750.0f, 275.0f, 20, "Standard", "It's a tie!", ColorPalette::Orange);
    }
    else
    {
        playerName = playerName.append(":");
        m_StatusNameText = TextView::MakeText(750.0f, 250.0f, 20, "Standard", playerName, ColorPalette::Orange);
        m_StatusPromptText = TextView::MakeText(750.0f, 275.0f, 20, "Standard", "You won!", ColorPalette::Orange);

        for (auto chip : m_SessionModel->m_WinningChips)
        {
            m_Grid[chip.x][chip.y]->SetHighlightChip(true);
        }
    }
}


std::string SessionController::GetName(int index)
{
    return m_NameTextFields[index]->GetText();
}


bool SessionController::IsOngoing() const
{
    return (m_SessionModel->m_State != SessionState::restarted) &&
           (m_SessionModel->m_State != SessionState::terminated);
}


bool SessionController::IsTerminated() const
{
    return (m_SessionModel->m_State == SessionState::terminated);
}


int SessionController::GetPlayerAt(int column, int row) const
{
    return m_Grid[column][row]->GetPlayer();
}
