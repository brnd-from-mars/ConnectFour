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

class SessionModel;
enum class PlayerState;

class GameController;


class SessionController : public BaseController
{
    friend SessionModel;


public:

    static std::shared_ptr<SessionController> MakeSessionController(const std::weak_ptr<GameController>& gameController,
                                                                    int columns, int rows);

    explicit SessionController(std::weak_ptr<GameController> gameController, int columns, int rows);

    virtual ~SessionController();

    void Update() override;


    void InitGrid();

    void InitGameTerminateButton();

    void InitNameTextFields();

    void InitColorPickPrompt();

    void InitArrow();

    void InitClock();


    void HandleColumnClick(int column);

    void HandleGameTerminatePress();

    void HandleNameEnter();

    void HandleColorPick(int color);

    void HandleGameEnd(PlayerState winState, std::string winningPlayer);


    std::string GetName(int index);

    bool IsOngoing() const;

    int GetPlayerAt(int column, int row) const;


private:

    std::shared_ptr<SessionModel> m_SessionModel;
    std::weak_ptr<SessionController> m_SessionController;

    std::weak_ptr<GameController> m_GameController;


    std::vector<std::vector<std::shared_ptr<GridFieldController>>> m_Grid;

    std::shared_ptr<ButtonController> m_GameTerminateButton;

    std::shared_ptr<TextFieldController> m_NameTextFields[2];
    std::shared_ptr<TextView> m_VSTextView;

    std::shared_ptr<TextView> m_StatusNameText;
    std::shared_ptr<TextView> m_StatusPromptText;

    std::shared_ptr<ButtonController> m_ColorPickButtons[2];

    std::shared_ptr<ArrowView> m_CurrentPlayerArrow;
    std::shared_ptr<ClockController> m_Clock;
};
