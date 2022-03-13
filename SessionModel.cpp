//
// Created by Brendan Berg on 10.03.22.
//

#include <iostream>

#include "SessionModel.hpp"
#include "SessionController.hpp"


SessionModel::SessionModel(int columns, int rows)
    : m_Columns(columns), m_Rows(rows)
{ }


void SessionModel::Update()
{ }


void SessionModel::HandleNamePlayer1Enter()
{
    if (m_State != SessionState::namePlayer1)
    {
        return;
    }

    m_State = SessionState::namePlayer2;
}


void SessionModel::HandleNamePlayer2Enter()
{
    if (m_State != SessionState::namePlayer2)
    {
        return;
    }

    m_State = SessionState::colorPick;
}


void SessionModel::HandleColorPick()
{
    if (m_State != SessionState::colorPick)
    {
        return;
    }

    m_State = SessionState::inGame;
}


void SessionModel::AddChip(int column)
{
    if (m_State != SessionState::inGame)
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
                auto winState = GetWinState(column, row);

                if (winState != PlayerState::none)
                {
                    m_State = SessionState::finished;

                    controller->HandleGameEnd(winState);

                    // TODO: outsource to controller
                    if (winState != PlayerState::tie)
                    {
                        for (auto chip : m_WinningChips)
                        {
                            controller->m_Grid[chip.x][chip.y]->SetHighlightChip(true);
                        }
                    }
                }

                m_CurrentPlayer = 3 - m_CurrentPlayer;

                return;
            }
        }
    }
}


bool SessionModel::IsOngoing() const
{
    return m_State != SessionState::terminated;
}


PlayerState SessionModel::GetPlayerAt(int column, int row) const
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

/*!  fn PlayerState getWinState(int column, int row)
*   \brief Function that returns if either player 1 won, player 2 won or there is a tie as an enum PlayerState
*   \param column Column of the last set Chip
*   \param row Row of the last set Chip
*
*/

PlayerState SessionModel::GetWinState(int column, int row)
{
    PlayerState winState;

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

    winState = CheckFieldFull();
    if (winState != PlayerState::none)
    {
        return winState;
    }

    return PlayerState::none;

}

/*!  fn  void CheckVertical(int column, int row, PlayerState& prev, int& count)
*   \brief Function checks, if the previous Chip was similar to the current one and counts the quantity of consecutive similar Chips
*   \param column Column of the current Chip
*   \param row of the current Chip
*   \param prev contains the Playerstate of the previous chip as an enum
*   \param count saves the quantity of consecutive similar chips  
*/


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
        }

        m_WinningChips[count - 1].x = column;
        m_WinningChips[count - 1].y = row;
    }
    else
    {
        count = 0;
    }

    prev = current;
}

/*!  fn  PlayerState CheckVertical(int column, int row)
*   \brief Function checks, if there are 4 similar Chips in a horizontal line within a radius of 3 fields around the last set Chip and returns the winning player as an enum
*   \param column Column of the last set Chip
*   \param row of the last set Chip
*/

PlayerState SessionModel::CheckHorizontal(int column, int row) {

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


/*!  fn  CheckVertical(int column, int row)
*   \brief Function checks, if there are 4 similar Chips in a vertical line within a radius of 3 fields around the last set Chip and returns the winning player as an enum
*   \param column Column of the last set Chip
*   \param row of the last set Chip
*/

PlayerState SessionModel::CheckVertical(int column, int row) {

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


/*!  fn  CheckDiagonal(int column, int row)
*   \brief Function checks, if there are 4 similar Chips in a diagonal line within a radius of 3 fields around the last set Chip and returns the winning player as an enum
*   \param column Column of the last set Chip
*   \param row of the last set Chip
*/

PlayerState SessionModel::CheckDiagonal(int column, int row)
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


/*!  fn  CheckFieldFull()
*   \brief Function checks, if every free space in Grid is filled with a Chip and returns the PlayerState as an enum
*/

PlayerState SessionModel::CheckFieldFull() const
{
	for (int x = 0; x < m_Columns; ++x)
	{
		if (GetPlayerAt(x, m_Rows - 1) == PlayerState::none)
		{
            return PlayerState::none;
        }
	}

	return PlayerState::tie;
}
