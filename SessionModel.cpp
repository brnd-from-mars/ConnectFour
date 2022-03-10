//
// Created by Brendan Berg on 10.03.22.
//

#include "SessionModel.hpp"

#include "SessionController.hpp"
#include <iostream>


SessionModel::SessionModel(int columns, int rows)
    : m_Columns(columns), m_Rows(rows), m_State(SessionState::inGame) // TODO: change to namePlayer1 after text field is added
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

				std::cout << get_winningPlayer(column, row) << std::endl;

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

int SessionModel::GetPlayerAt(int column, int row) const
{
	if (auto controller = m_SessionController.lock()) {
		return controller->GetPlayerAt(column, row);
	}
	return 0;
}


int SessionModel::get_winningPlayer(int col, int row) { /*gibt den Spieler zur�ck, der gewonnen hat;	0 kein Ergebnis;
																										1 Spieler 1;
																										2 Spieler 2;
																										3 Gleichstand/Spielfeld voll */

	if (check_diagonal(col, row) != 0) {
		return check_diagonal(col, row);
	}
	if (check_vertical(col, row) != 0) {
		return check_vertical(col, row);
	}
	if (check_horizontal(col, row) != 0) {
		return check_horizontal(col, row);
	}
	if (full_matchfield()) { //Gleichstand
		return 3;
	}
	else { //Kein Ergebnis
		return 0;
	}
}



int SessionModel::check_diagonal(int col, int row) { //�berpr�ft, ob in der N�he des letzten Steins (an Position row;col) 4 gleiche sind in Diagonalen

	int count = 0; //Z�hlt die hintereinanderfolgenden gleichen Felder
	int prev = 0; //0, wenn vorher ein leeres Feld war, 1 wenn ein X, 2 wenn ein O war

	int y = row - 3;
	for (int x = col - 3; x <= col + 3 && x <= m_Columns && y <= m_Rows; x++) { //schr�g hoch von links
		if (x >= 0 && y >= 0) {
			check_Chips(x, y, prev, count);
		}
		y++;
	}

	if (count == 4) { //Wenn 4 gleiche gez�hlt wurden
		return prev; //Spieler, der 4 Gleiche hat returnen
	}


	count = 0; //Reset der Laufvariablen
	prev = 0;

	y = row + 3;
	for (int x = col - 3;  x <= col + 3 && x <= m_Columns && y >= 0; x++) { //schr�g runter von links
		if (x >= 0 && y <= m_Columns) {
			check_Chips(x, y, prev, count);
		}
		y--;
	}
	if (count == 4) { //Wenn 4 gleiche gez�hlt wurden
		return prev; //Spieler, der 4 Gleiche hat returnen
	}

	return 0;
}

int SessionModel::check_vertical(int col, int row) {

	int count = 0; //Reset der Laufvariablen
	int prev = 0;
	int x = col;

    for (int y = row; y >= row - 3 && y >= 0; y--) { //Befinden sich in der Verkikalen unter dem letzten Chip 4 gleiche?
		check_Chips(x, y, prev, count);
	}
	if (count == 4) { //Wenn 4 gleiche gez�hlt wurden
		return prev; //Spieler, der 4 Gleiche hat returnen
	}

	return 0;
}

int SessionModel::check_horizontal(int col, int row) {

	int count = 0; //Z�hlt die hintereinanderfolgenden gleichen Felder
	int prev = 0; //0, wenn vorher ein leeres Feld war, 1 wenn ein X, 2 wenn ein O war
	int y = row;
	for (int x = col - 3; x <= col + 3 && x <= m_Columns; x++) { //Befinden sich in der Horizontalen um den letzten gesetzten Stein 4 Gleiche?
		if (x >= 0) { //�berpr�fen, ob linke spielfeldrand �berschritten wurde
			check_Chips(x, y, prev, count);
		}


	}
	if (count == 4) { //Wenn 4 gleiche gez�hlt wurden
		return prev; //Spieler, der 4 Gleiche hat returnen
	}

	return 0;
}
void SessionModel::check_Chips(int col, int row, int &prev, int &count) {


	if (GetPlayerAt(col, row) == 1) {

		if (prev != 1) {
			count = 1;
		}
		else {

			winningChips[0][count - 1] = row;
			winningChips[1][count - 1] = col;

			count++;
		}
		prev = 1;
	}

	if (GetPlayerAt(col, row) == 2) {

		if (prev != 2) {
			count = 1;
		}
		else {
			winningChips[0][count - 1] = row;
			winningChips[1][count - 1] = col;

			count++;
		}
		prev = 2;

	}
}

bool SessionModel::full_matchfield() {

	for (int x = 0; x <= m_Columns; x++) {

		for (int y = 0; y <= m_Rows; y++) {

			if (GetPlayerAt(x, y) == 0) {
				return false;
			}

		}
	}
	return true;
}
