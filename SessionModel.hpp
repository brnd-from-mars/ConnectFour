//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseModel.hpp"

class SessionController;


enum class SessionState
{
    namePlayer1,
    namePlayer2,
    colorPlayerA,
    colorPlayerB,
    inGame,
    finished
};


class SessionModel : public BaseModel
{
    friend SessionController;
 

public:

    SessionModel(int columns, int rows);

    void Update() override;

    void AddChip(int column);

    bool IsOngoing() const;

    int get_winningPlayer(int row, int col);

    int GetPlayerAt(int column, int row) const;

private:

    std::weak_ptr<SessionController> m_SessionController;

    int m_Columns;

    int m_Rows;

    SessionState m_State;

    int m_CurrentPlayer = 1;

    int check_diagonal(int row, int col);

    int check_vertical(int row, int col);

    int check_horizontal(int row, int col);

    void check_Chips(int row, int col, int& prev, int& count);

    bool full_matchfield();

    int winningChips[2][4]{}; //enthaelt 4 Koordinaten der gewinnenden Steine


};
