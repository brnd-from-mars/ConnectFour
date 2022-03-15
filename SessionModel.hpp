//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>
#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "BaseModel.hpp"

class SessionController;


enum class SessionState
{
    nameEnter,
    colorPick,
    inGame,
    finished,
    restarted,
    terminated
};


enum class PlayerState
{
    none = 0,
    player1 = 1,
    player2 = 2,
    tie = 3
};


class SessionModel : public BaseModel
{
    friend SessionController;


public:

    SessionModel(int columns, int rows);
    SessionModel(const SessionModel& oldSessionModel);

    void Update() override;


private:

    bool HandleInitialNameEnter();
    bool HandleColorPick(int color);

    std::string GetRandomPlayerForColorPick();

    int GetCurrentPlayerIndex() const;

    void AddChip(int column);

    PlayerState GetPlayerAt(int column, int row) const;

    PlayerState GetWinState(int column, int row);
    void CheckChips(int column, int row, PlayerState& prev, int& count);
    PlayerState CheckHorizontal(int column, int row);
    PlayerState CheckVertical(int column, int row);
    PlayerState CheckDiagonal(int column, int row);
    PlayerState CheckFieldFull() const;

    std::weak_ptr<SessionController> m_SessionController;

    int m_Columns;
    int m_Rows;

    SessionState m_State = SessionState::nameEnter;
    int m_CurrentPlayer = 1;

    int m_RandomNameForColorPick = 0;
    bool m_ColorsChanged = false;

    sf::Vector2i m_WinningChips[4];


};
