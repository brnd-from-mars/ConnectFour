//
// Created by Brendan Berg on 10.03.22.
//

#include "SessionModel.hpp"

#include "SessionController.hpp"


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


int SessionController::GetPlayerAt(int column, int row) const
{
	return m_Grid[column][row]->GetPlayer();
}


int get_winningPlayer(int row, int col) { /*gibt den Spieler zurück, der gewonnen hat;	0 kein Ergebnis;
																						1 Spieler 1;
																						2 Spieler 2;
																						3 Gleichstand/Spielfeld voll */

	if (check_diagonal(row, col) != 0) {
		return check_diagonal(row, col);
	}
	if (check_vertical(row, col) != 0) {
		return check_vertical(row, col);
	}
	if (check_horizontal(row, col) != 0) {
		return check_horizontal(row, col);
	}
	if (full_matchfield(row, col)) { //Gleichstand
		return 3;
	}
	else { //Kein Ergebnis
		return 0;
	}
}


int* get_winningChips() { //gibt ein Array mit den x- und y-Koordinaten der 4 gewinnenden Punkte zurück
	return &winningChips;
}




int count = 0; //Zählt die hintereinanderfolgenden gleichen Felder
int prev = 0; //0, wenn vorher ein leeres Feld war, 1 wenn ein X, 2 wenn ein O war
int winningChips[2][4]; //enthält 4 Koordinaten der gewinnenden Steine

int check_diagonal(int row, int col) { //Überprüft, ob in der Nähe des letzten Steins (an Position row;col) 4 gleiche sind in Diagonalen


	for (int x = col - 3; int y = row - 3; x <= row + 3 && x <= m_Colums && y <= m_Rows; x++; y++) { //schräg hoch von links
		if (x >= 0 && y >= 0) {
			check_Chips(x, y);
		}
	}

	if (count == 4) { //Wenn 4 gleiche gezählt wurden
		return prev; //Spieler, der 4 Gleiche hat returnen
	}


	count = 0; //Reset der Laufvariablen
	prev = 0;



	for (int x = col - 3; int y = row + 3; x <= row + 3 && x <= m_Colums && y >= 0; x++; y--) { //schräg runter von links
		if (x >= 0 && y <= m_Colums) {
			check_Chips(x, y);
		}
	}
	if (count == 4) { //Wenn 4 gleiche gezählt wurden
		return prev; //Spieler, der 4 Gleiche hat returnen
	}

	return 0;
}

int check_vertical(int row, int col) {

	count = 0; //Reset der Laufvariablen
	prev = 0;
	int x = col;
	for (int y = row; y >= row - 3 && y >= m_Rows; y--) { //Befinden sich in der Verkikalen unter dem letzten Chip 4 gleiche?
		check_Chips(x, y);
	}
	if (cout == 4) { //Wenn 4 gleiche gezählt wurden
		return prev; //Spieler, der 4 Gleiche hat returnen
	}

	return 0;
}

int check_horizontal(int row, int col) {

	count = 0; //Reset der Laufvariablen
	prev = 0;
	y = row;
	for (int x = col - 3; x <= col + 3 && x <= m_Colums; x++) { //Befinden sich in der Horizontalen um den letzten gesetzten Stein 4 Gleiche?
		if (x >= 0) { //Überprüfen, ob linke spielfeldrand überschritten wurde
			check_Chips(x, y);
		}


	}
	if (count == 4) { //Wenn 4 gleiche gezählt wurden
		return prev; //Spieler, der 4 Gleiche hat returnen
	}

	return 0;
}

void check_Chips(int row, int col) {

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

	if (matrix[row][col] == 2) {

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

bool full_matchfield() {

	for (int x = 0; x <= m_Colums; x++) {

		for (int y = 0; y <= m_Rows; y++) {

			if (matrix[x][y] == 0) {
				return false;
			}

		}
	}
	return true;
}
