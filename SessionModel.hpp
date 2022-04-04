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
     * @brief   Handles the any name enter. Only if two valid names were entered for the FIRST time, the SessionState will
     * be changed and true returned.
     *
     * @return  Does the controller have to initialize the color pick prompt UI?
     */
    bool HandleInitialNameEnter();

    /*!
     * @brief   Handles color pick by checking if the colors were changed or kept the same.
     *
     * @param   color 0 (red) or 1 (blue)
     * @return  Does the controller have to initialize the inGame UI?
     */
    bool HandleColorPick(int color);

    /*!
     * @brief   Chooses a random player for a color pick and saves the corresponding INDEX (which text field?).
     *
     * @return  name of the chosen player
     */
    std::string GetRandomPlayerForColorPick();

    /*!
     * @brief   Computes the INDEX (which text field?) of the current player depending on if a color change has occurred.
     *
     * @return  INDEX of the current player
     */
    int GetCurrentPlayerIndex() const;

    /*!
     * @brief   Adds a chip to the specified column if the SessionState is in the correct state and the columns is not
     *          full. Computes if the game was finished due to the added chip.
     *
     * @param   column  column that was clicked by one of the players.
     */
    void AddChip(int column);

    /*!
     * @brief   Returns the chip at given coordinates. Returns none for out of bounds coordinates.
     *
     * @param   column  column where to determine the chip color
     * @param   row     row where to determine the chip color
     * @return  none (no chip / out of bounds), player1 (red), player2 (blue)
     */
    PlayerState GetPlayerAt(int column, int row) const;

    /*!
    *   @brief  Function that returns if either player 1 won,
    *           player 2 won or there is a tie as an enum PlayerState
    *
    *   @return PlayerState
    *   @param  column  Column of the last set Chip
    *   @param  row     Row of the last set Chip
    */
    PlayerState GetWinState(int column, int row);

    /*!
    *   @brief  Function checks if the previous Chip was similar to
    *           the current one and counts the quantity of consecutive similar Chips
    *
    *   @param  column  column of the current Chip
    *   @param  row     row of the current Chip
    *   @param  prev    contains the Playerstate (color) of the previous chip
    *   @param  count   saves the quantity of consecutive similar chips
    */
    void CheckChips(int column, int row, PlayerState& prev, int& count);

    /*!
    *   @brief  Function checks, if there are 4 similar Chips
    *           in a horizontal line within a radius of 3 fields around the last set Chip
    *
    *   @return PlayerState (color) of the winning chips or none
    *   @param  column  column of the last set Chip
    *   @param  row     row of the last set Chip
    */
    PlayerState CheckHorizontal(int column, int row);

    /*!
    *   @brief  Function checks, if there are 4 similar Chips
    *           in a vertical line within a radius of 3 fields around the last set Chip
    *
    *   @return PlayerState (color) of the winning chips or none
    *   @param  column  column of the last set Chip
    *   @param  row     row of the last set Chip
    */
    PlayerState CheckVertical(int column, int row);

    /*!
    *   @brief  Function checks, if there are 4 similar Chips
    *           in a diagonal line within a radius of 3 fields around the last set Chip
    *
    *   @return PlayerState (color) of the winning chips or none
    *   @param  column  column of the last set Chip
    *   @param  row     row of the last set Chip
    */
    PlayerState CheckDiagonal(int column, int row);

    /*!
    *   @brief  Function checks, if the Gridfield is completely filled with chips (tie)
    *
    *   @return PlayerState either 'tie' or 'none'
    */
    PlayerState CheckFieldFull() const;

    /*!
    *   @brief   weak pointer on object SessionController
    */
    std::weak_ptr<SessionController> m_SessionController;

    /*!
    *   @brief  number of columns in Gridfield
    */
    int m_Columns;

    /*!
    *   @brief  number of rows in Gridfield
    */
    int m_Rows;

    /*!
    *   @brief  current State of Session. Set to entering playernames by default
    */
    SessionState m_State = SessionState::nameEnter;

    /*!
    *   @brief  current Player. Set to Player 1 by default
    */
    int m_CurrentPlayer = 1;

    /*!
    *   @brief  2x1 array which contains number of moves player 1 and player 2 made each
    */
    int m_Moves[2] = {0, 0};

    /*!
    *   @brief  contains randomly chosen player who may choose his/her color
    *           1 - player 1
    *           2 - player 2
    */
    int m_RandomNameForColorPick = 0;

    /*!
    *   @brief  default color allocation: player 1 blue; player 2 red;
    *           set to false by default;
    *           set to true if colors were inverted by player choosing his/her color
    */
    bool m_ColorsChanged = false;

    /*!
    *   @brief  4x2 vector that contains x-y-coordinates of the 4 winning cips
    */
    sf::Vector2i m_WinningChips[4];


};
