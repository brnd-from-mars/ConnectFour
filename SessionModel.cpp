//
// Created by Brendan Berg on 10.03.22.
//

#include "SessionModel.hpp"
#include "SessionController.hpp"

#include "AppDelegate.hpp"
#include "ConnectFourUtility.hpp"


SessionModel::SessionModel(int columns, int rows)
    : m_Columns(columns), m_Rows(rows)
{ }


SessionModel::SessionModel(const SessionModel& oldSessionModel)
    : m_Columns(oldSessionModel.m_Columns), m_Rows(oldSessionModel.m_Rows)
{
    m_RandomNameForColorPick = oldSessionModel.m_RandomNameForColorPick;
    m_ColorsChanged = oldSessionModel.m_ColorsChanged;

    m_State = SessionState::inGame;
}


void SessionModel::Update()
{ }


bool SessionModel::HandleInitialNameEnter()
{
    if (m_State != SessionState::nameEnter)
    {
        return false;
    }

    auto controller = m_SessionController.lock();
    if (!controller)
    {
        return false;
    }

    if (controller->GetName(0).empty() || controller->GetName(1).empty())
    {
        return false;
    }

    m_State = SessionState::colorPick;
    return true;
}


bool SessionModel::HandleColorPick(int color)
{
    if (m_State != SessionState::colorPick)
    {
        return false;
    }

    m_ColorsChanged = color != m_RandomNameForColorPick;

    m_State = SessionState::inGame;
    return true;
}


std::string SessionModel::GetRandomPlayerForColorPick()
{
    if (m_State != SessionState::colorPick)
    {
        return std::string();
    }

    auto controller = m_SessionController.lock();
    if (!controller)
    {
        return std::string();
    }

    m_RandomNameForColorPick = AppDelegate::Get()->GetRandomNumber() % 2;
    return controller->GetName(m_RandomNameForColorPick);
}


int SessionModel::GetCurrentPlayerIndex() const
{
    return (m_ColorsChanged ? 3 - m_CurrentPlayer : m_CurrentPlayer) - 1;
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
                ++m_Moves[m_CurrentPlayer - 1];

                field->SetChip(m_CurrentPlayer);

                auto row = field->GetRow();
                auto winState = GetWinState(column, row);

                if (winState != PlayerState::none)
                {
                    GameData game;

                    if (winState != PlayerState::tie)
                    {
                        // interpret as (ColorsChanged XOR (player1 won))
                        int k = m_ColorsChanged == (winState == PlayerState::player1);
                        game.winningPlayer = controller->GetName(k);
                        game.loosingPlayer = controller->GetName(1 - k);
                        game.moves = m_Moves[m_CurrentPlayer - 1];
                    }

                    controller->HandleGameEnd(winState, game);
                    m_State = SessionState::finished;
                }

                // player 1 -> player 2
                // player 2 -> player 1
                m_CurrentPlayer = 3 - m_CurrentPlayer;

                return;
            }
        }
    }
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

        m_WinningChips[count - 1].x = column;   //add location of current Chip to a Vector 
        m_WinningChips[count - 1].y = row;      //vector contains coordinates of the 4 winnning chips
    }
    else
    {
        count = 0;
    }

    prev = current;                             //going to the next Field: current Chip is now the previous
}


PlayerState SessionModel::CheckHorizontal(int column, int row) {

    int count = 0;                              //reset control variables                                            
    PlayerState prev = PlayerState::none;       //

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


PlayerState SessionModel::CheckVertical(int column, int row) {

    int count = 0;
    PlayerState prev = PlayerState::none; 

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


PlayerState SessionModel::CheckDiagonal(int column, int row)
{
    int count = 0;                          //reset control variables
    PlayerState prev = PlayerState::none;   // 

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


	count = 0;                               //reset control variables
	prev = PlayerState::none;                //

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
