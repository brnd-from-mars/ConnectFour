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


/*!
 * @brief SessionState names the states that the SessionModel can be in.
 */
enum class SessionState
{
    nameEnter,
    colorPick,
    inGame,
    finished,
    restarted,
    terminated
};


/*!
 * @brief PlayerState identifies either which chip is positioned on a field or if a win by a player / a tie  has
 * occurred.
 */
enum class PlayerState
{
    none = 0,
    player1 = 1,
    player2 = 2,
    tie = 3
};


/*!
 * @brief SessionModel represents data associated with with a single ConnectFour round. It handles the state machine and
 * winning logic.
 */
class SessionModel : public BaseModel
{
    friend SessionController;


public:

    /*!
     * @brief Constructs a new and empty SessionModel.
     *
     * @param columns number of columns in the ConnectFour grid
     * @param rows number of rows in the ConnectFour grid
     */
    SessionModel(int columns, int rows);

    /*!
     * @brief Copy-Constructor constructs a new SessionModel by copying the color change data from the old session and
     * setting the SessionState to inGame.
     *
     * @param oldSessionModel SessionModel that will be copied
     */
    SessionModel(const SessionModel& oldSessionModel);

    /*!
     * @brief No-op
     */
    void Update() override;


private:

    /*!
     * @brief Handles every name enter. Only if two valid names were entered for the FIRST time, the SessionState will
     * be changed and true returned.
     *
     * @return Does the controller have to initialize the color pick prompt UI?
     */
    bool HandleInitialNameEnter();

    /*!
     * @brief Handles color pick by checking if the colors were changed or kept the same.
     *
     * @param color 0 (red) or 1 (blue)
     * @return Does the controller have to initialize the inGame UI?
     */
    bool HandleColorPick(int color);

    /*!
     * @brief Chooses a random player for a color pick and saves the corresponding INDEX (which text field?).
     *
     * @return name of the chosen player
     */
    std::string GetRandomPlayerForColorPick();

    /*!
     * @brief Computes the INDEX (which text field?) of the current player depending on if a color change has occurred.
     *
     * @return INDEX of the current player
     */
    int GetCurrentPlayerIndex() const;

    /*!
     * @brief Adds a chip to the specified column if the SessionState is in the correct state and the columns is not
     * full. Computes if the game was finished due to the added chip.
     *
     * @param column column that was clicked by one of the players.
     */
    void AddChip(int column);

    /*!
     * @brief Returns the chip at given coordinates. Returns none for out of bounds coordinates.
     *
     * @param column column where to determine the chip color
     * @param row row where to determine the chip color
     * @return none (no chip / out of bounds), player1 (red), player2 (blue)
     */
    PlayerState GetPlayerAt(int column, int row) const;

    /*!
     * @brief Determines if the game ended in a win, tie or none of that. Sends results to the SessionController if the
     * game has ended.
     *
     *
     * @param column column of the last added chip
     * @param row row of the last added chip
     * @return none, player1, player2 or tie
     */
    PlayerState GetWinState(int column, int row);

    /*!
     * @brief Checks if the previously checked chip is similar to the current one and counts the quantity of consecutive
     * similar chips whilst adding them to the m_WinningChips array.
     *
     * @param column column of the current chip
     * @param row row of the current chip
     * @param prev PlayerState (= color) of the previous chip
     * @param count quantity of consecutive similar chips
     */
    void CheckChips(int column, int row, PlayerState& prev, int& count);

    /*!
     * @brief Checks if there are 4 similar chips in a horizontal line within a radius of 3 fields around the last added
     * chip.
     *
     * @param column column of the last added chip
     * @param row row of the last added chip
     * @return none, player1 or player2
     */
    PlayerState CheckHorizontal(int column, int row);

    /*!
     * @brief Checks if there are 4 similar chips in a vertical line within a radius of 3 fields around the last added
     * chip.
     *
     * @param column column of the last added chip
     * @param row row of the last added chip
     * @return none, player1 or player2
     */
    PlayerState CheckVertical(int column, int row);

    /*!
     * @brief Checks if there are 4 similar chips in a diagonal line within a radius of 3 fields around the last added
     * chip.
     *
     * @param column column of the last added chip
     * @param row row of the last added chip
     * @return none, player1 or player2
     */
    PlayerState CheckDiagonal(int column, int row);

    /*!
     * @brief Checks if the grid field is completely filled with chips (tie), by checking the upper most row.
     *
     * @return none or tie
     */
    PlayerState CheckFieldFull() const;

    /*!
     * @brief weak pointer to the associated controller
     */
    std::weak_ptr<SessionController> m_SessionController;

    /*!
     * @brief number of columns in the ConnectFour grid
     */
    int m_Columns;

    /*!
     * @brief number of rows in the ConnectFour grid
     */
    int m_Rows;

    /*!
     * @brief current state of the SessionModel state machine
     */
    SessionState m_State = SessionState::nameEnter;

    /*!
     * @brief  current Player. Set to Player 1 by default
     */
    int m_CurrentPlayer = 1;

    /*!
     * @brief array that contains number of moves that each, player1 and player2, made
     */
    int m_Moves[2] = {0, 0};

    /*!
     * @brief contains randomly chosen player INDEX who may choose his/her color (0 or 1)
     */
    int m_RandomNameForColorPick = 0;

    /*!
     * @brief true if the colors associated with the player names have been changed
     */
    bool m_ColorsChanged = false;

    /*!
     * @brief array that contains x-y-coordinates of the 4 chips that lead to the victory
     */
    sf::Vector2i m_WinningChips[4];


};
