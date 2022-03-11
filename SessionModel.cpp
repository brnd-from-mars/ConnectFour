//
// Created by Brendan Berg on 10.03.22.
//

#include "SessionModel.hpp"
#include "SessionController.hpp"


SessionModel::SessionModel(int columns, int rows)
    : m_Columns(columns), m_Rows(rows)
{ }


void SessionModel::Update()
{ }


void SessionModel::AddChip(int column)
{
    if (m_State != State::inGame)
    {
        return;
    }

    if (auto controller = m_SessionController.lock())
    {
        for (auto& field : controller->m_Grid[column]) // go through each field in column
        {
            if (!field->HasChip()) // check if field does not contain chip
            {
                field->SetChip(m_CurrentPlayer);

                auto row = field->GetRow();
                if (GetWinState(column, row) != PlayerState::none)
                {
                    // game over
                }

                m_CurrentPlayer = 3 - m_CurrentPlayer;

                return;
            }
        }
    }
}


bool SessionModel::IsOngoing() const
{
    return m_State != State::finished;
}


SessionModel::PlayerState SessionModel::GetPlayerAt(int column, int row) const
{
    if ((column < 0) || (m_Columns <= column) || (row < 0) || (m_Rows <= row))
    {
        return PlayerState::none;
    }
	if (auto controller = m_SessionController.lock())
	{
	    switch (controller->GetPlayerAt(column, row))
        {
            case 1:
                return PlayerState::player1;
            case 2:
                return PlayerState::player2;
            default:
                return PlayerState::none;
        }
	}
    return PlayerState::none;
}


SessionModel::PlayerState SessionModel::GetWinState(int column, int row)
{
    PlayerState winState = PlayerState::none;

    winState = CheckHorizontal(column, row);
    if (winState != PlayerState::none)
    {
        return winState;
    }

    winState = CheckVertical(column, row);
    if (winState != PlayerState::none)
    {
        return winState;
    }

    winState = CheckDiagonal(column, row);
    if (winState != PlayerState::none)
    {
        return winState;
    }

    winState = CheckDiagonal(column, row);
    if (winState != PlayerState::none)
    {
        return winState;
    }

	return PlayerState::none;
}


void SessionModel::CheckChips(int column, int row, PlayerState& prev, int& count)
{
    PlayerState current = GetPlayerAt(column, row);

    if ((current == PlayerState::player1) || (current == PlayerState::player2))
    {
        if (current == prev)
        {
            ++count;
        }
        else
        {
            count = 1;
            m_WinningChips.resize(0);
        }

        m_WinningChips.emplace_back(column, row);
    }
    else
    {
        count = 0;
        m_WinningChips.resize(0);
    }

    prev = current;
}


SessionModel::PlayerState SessionModel::CheckHorizontal(int column, int row) {

    int count = 0; // number of adjacent chips of same color
    PlayerState prev = PlayerState::none; // chip in previous field

    for (int x = column - 3; x <= column + 3; ++x)
    {
        CheckChips(x, row, prev, count);
        if (count == 4)
        {
            return prev;
        }
    }

    return PlayerState::none;
}


SessionModel::PlayerState SessionModel::CheckVertical(int column, int row) {

    int count = 0; // number of adjacent chips of same color
    PlayerState prev = PlayerState::none; // chip in previous field

    for (int y = row - 3; y <= row; ++y)
    {
        CheckChips(column, y, prev, count);
        if (count == 4)
        {
            return prev;
        }
    }

    return PlayerState::none;
}


SessionModel::PlayerState SessionModel::CheckDiagonal(int column, int row)
{
    int count = 0; // number of adjacent chips of same color
    PlayerState prev = PlayerState::none; // chip in previous field

	int y = row - 3;
	for (int x = column - 3; x <= column + 3; ++x)
	{
		CheckChips(x, y, prev, count);
        if (count == 4)
        {
            return prev;
        }
		++y;
	}


	count = 0;
	prev = PlayerState::none;

	y = row + 3;
	for (int x = column - 3; x <= column + 3; ++x)
	{
		CheckChips(x, y, prev, count);
        if (count == 4)
        {
            return prev;
        }
        --y;
	}

	return PlayerState::none;
}


SessionModel::PlayerState SessionModel::CheckFieldFull() const
{
	for (int x = 0; x <= m_Columns; ++x)
	{
		if (GetPlayerAt(x, m_Rows - 1) == PlayerState::none)
		{
            return PlayerState::none;
        }
	}

	return PlayerState::tie;
}
