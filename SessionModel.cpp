//
// Created by Brendan Berg on 10.03.22.
//

#include "SessionModel.hpp"

#include "SessionController.hpp"


SessionModel::SessionModel()
    : m_State(SessionState::inGame) // TODO: change to namePlayer1 after text field is added
{

}


void SessionModel::Update()
{

}


void SessionModel::AddChip(int column)
{
    if (m_State != SessionState::inGame)
    {
        return;
    }

    if (auto controller = m_SessionController.lock())
    {
        for (auto& field : controller->m_Grid[column])
        {
            if (!field->HasChip()) // check if no chip
            {
                field->SetChip(m_CurrentPlayer);

                auto row = field->GetRow();
                // TODO: call GameWon here
                // if (GameWon(column, row)) {}

                m_CurrentPlayer = 3 - m_CurrentPlayer;

                return;
            }
        }
    }

    m_State = SessionState::finished; // TODO: remove this test line
}


bool SessionModel::IsOngoing() const
{
    return m_State != SessionState::finished;
}
