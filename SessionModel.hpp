//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "BaseModel.hpp"

class SessionController;


class SessionModel : public BaseModel
{
    friend SessionController;


public:

    enum class State
    {
        namePlayer1,
        namePlayer2,
        colorPlayerA,
        colorPlayerB,
        inGame,
        finished,
        terminated
    };

    enum class PlayerState
    {
        none = 0,
        player1 = 1,
        player2 = 2,
        tie = 3
    };

    SessionModel(int columns, int rows);

    void Update() override;

    void AddChip(int column);

    bool IsOngoing() const;

    PlayerState GetPlayerAt(int column, int row) const;

    PlayerState GetWinState(int column, int row);


private:

    std::weak_ptr<SessionController> m_SessionController;

    int m_Columns;
    int m_Rows;

    State m_State = State::inGame; // TODO: change to State::namePlayer1 after text field is added
    int m_CurrentPlayer = 1;

    sf::Vector2i m_WinningChips[4];

    void CheckChips(int column, int row, PlayerState& prev, int& count);
    PlayerState CheckHorizontal(int column, int row);
    PlayerState CheckVertical(int column, int row);
    PlayerState CheckDiagonal(int column, int row);
    PlayerState CheckFieldFull() const;


};
