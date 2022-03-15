//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>
#include <vector>

#include "BaseController.hpp"

#include "ArrowView.hpp"
#include "TextView.hpp"
#include "ClockController.hpp"
#include "ButtonController.hpp"
#include "TextFieldController.hpp"
#include "GridFieldController.hpp"
#include "ScoreBoardController.hpp"

class SessionModel;
enum class PlayerState;

class GameController;


class SessionController : public BaseController
{
    friend SessionModel;


public:

    static std::shared_ptr<SessionController> MakeSessionController(const std::weak_ptr<GameController>& game,
                                                                    int columns, int rows);

    static std::shared_ptr<SessionController> MakeSessionController(const SessionController& oldSessionController);

    SessionController(std::weak_ptr<GameController> game, int columns, int rows);

    SessionController(const SessionController& oldSessionController);

    virtual ~SessionController();

    void Update() override;

    void HandleColumnClick(int column);

    bool IsOngoing() const;
    bool IsTerminated() const;


private:

    void InitScoreBoard();
    void InitGrid();
    void InitGameTerminateButton();
    void InitNameTextFields();
    void InitColorPickPrompt();
    void InitArrow();
    void InitClock();
    void InitGameRestartButton();

    void HandleGameTerminatePress();
    void HandleNameEnter();
    void HandleColorPick(int color);
    void HandleGameRestartPress();
    void HandleGameEnd(PlayerState winState, std::string winningPlayer);

    std::string GetName(int index);
    int GetPlayerAt(int column, int row) const;

    std::shared_ptr<SessionModel> m_SessionModel;
    std::weak_ptr<SessionController> m_SessionController;

    std::weak_ptr<GameController> m_Game;

    std::shared_ptr<ScoreBoardController> m_ScoreBoard;

    std::vector<std::vector<std::shared_ptr<GridFieldController>>> m_Grid;

    std::shared_ptr<ButtonController> m_GameRestartButton;
    std::shared_ptr<ButtonController> m_GameTerminateButton;

    std::shared_ptr<TextFieldController> m_NameTextFields[2];
    std::shared_ptr<TextView> m_VSTextView;

    std::shared_ptr<TextView> m_StatusNameText;
    std::shared_ptr<TextView> m_StatusPromptText;

    std::shared_ptr<ButtonController> m_ColorPickButtons[2];

    std::shared_ptr<ArrowView> m_CurrentPlayerArrow;
    std::shared_ptr<ClockController> m_Clock;
};
