//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>
#include <vector>

#include "BaseController.hpp"

#include "ArrowView.hpp"
#include "TextView.hpp"
#include "ClockController.hpp"
#include "ButtonController.hpp"
#include "TextFieldController.hpp"
#include "GridFieldController.hpp"
#include "ConnectFourUtility.hpp"


class SessionModel;
enum class PlayerState;

class GameController;


/*!
 * @brief SessionController class represents a game round from start to finish. It gets destroyed after a game ends.
 */
class SessionController : public BaseController
{
    friend SessionModel;


public:


    /*!
     * @brief Static factory function creates a new empty session, sets references between MCV SessionController and
     * SessionModel as well as initiates the grid, terminate button and name text fields.
     *
     * @param game weak pointer to the parent in the MVC tree GameController
     * @param columns number of columns in the ConnectFour grid
     * @param rows number of rows in the ConnectFour grid
     * @return shared pointer to the new SessionController
     */
    static std::shared_ptr<SessionController> MakeSessionController(const std::weak_ptr<GameController>& game,
                                                                    int columns, int rows);

    /*!
     * @brief Static factory function creates a new session from an existing one (the entered player names and color
     * choice will be copied), sets references between MCV SessionController and SessionModel as well as initiates the
     * grid, terminate and restart buttons, name text fields, current player arrow and clock.
     *
     * @param oldSessionController SessionController that will be copied
     * @return shared pointer to the new SessionController
     */
    static std::shared_ptr<SessionController> MakeSessionController(const SessionController& oldSessionController);

    /*!
     * @brief Constructor creates associated SessionModel.
     *
     * @param game weak pointer to the parent in the MVC tree GameController
     * @param columns number of columns in the ConnectFour grid
     * @param rows number of rows in the ConnectFour grid
     */
    SessionController(std::weak_ptr<GameController> game, int columns, int rows);

    /*!
     * @brief Copy-Constructor creates associated SessionModel
     *
     * @param oldSessionController SessionController that will be copied
     */
    SessionController(const SessionController& oldSessionController);

    /*!
     * @brief No-op
     */
    virtual ~SessionController();

    /*!
     * @brief If SessionState inGame: Positions the arrow at current player's name text field.
     */
    void Update() override;

    /*!
     * @brief Calls the SessionModel::AddChip function in the SessionModel to handle the click of a column by a player.
     * HandleColumnClick gets called from the event handling in the GridFieldController.
     *
     * @param column column that has been clicked by a player
     */
    void HandleColumnClick(int column);

    /*!
     * @brief Checks whether the game is neither restarted nor terminated.
     *
     * @return is the game neither restarted nor terminated
     */
    bool IsOngoing() const;

    /*!
     * @brief Checks whether the game is terminated.
     *
     * @return is the game terminated
     */
    bool IsTerminated() const;


private:

    /*!
     * @brief Initiated the m_Columns x m_Rows GridFieldController vector m_Grid.
     */
    void InitGrid();

    /*!
     * @brief Initiates the m_GameTerminateButton and registers the HandleGameTerminatePress function as its callback.
     */
    void InitGameTerminateButton();

    /*!
     * @brief Initiates the m_NameTextFields for both player names and registers the HandleNameEnter function as
     * their callback.
     */
    void InitNameTextFields();

    /*!
     * @brief Initiates the m_ColorPickButtons and chooses a random player who can pick his/her color. Registers the
     * HandleColorPick function as their callback
     */
    void InitColorPickPrompt();

    /*!
     * @brief Initiates the m_CurrentPlayerArrow.
     */
    void InitArrow();

    /*!
     * @brief Initiates the m_Clock.
     */
    void InitClock();

    /*!
     * @brief Initiates the m_GameRestartButton and registers the HandleGameRestartPress function as its callback.
     */
    void InitGameRestartButton();

    /*!
     * @brief Sets the SessionState to terminated after terminate button was pressed.
     */
    void HandleGameTerminatePress();

    /*!
     * @brief Calls SessionModel::HandleInitialNameEnter function and if it is handled for the first time, the color
     * pick menu will be initiated (InitColorPickPrompt).
     */
    void HandleNameEnter();

    /*!
     * @brief Calls SessionModel::HandleColorPick function and if it is successful the UI will be adapted to reflect the
     * color change. The arrow, clock and restart button will be initiated afterwards.
     *
     * @param color 0 (red) or 1 (blue)
     */
    void HandleColorPick(int color);

    /*!
     * @brief Sets the SessionState to restarted.
     */
    void HandleGameRestartPress();

    /*!
     * @brief Gets called by the SessionModel in case a move lead to a victory or tie. The session time will be
     * measured. The results will be send to the GameController which handles the saving of the data. In case of a
     * victory, the 4 chips that lead to the victory will get highlighted.
     *
     * @param winState player1, player2 or tie
     * @param game GameData containing the results of the game that were identified by the SessionModel (moves, players)
     */
    void HandleGameEnd(PlayerState winState, GameData game);

    /*!
     * @brief Gets the currently typed name in a text field
     *
     * @param index 0 (upper text field) or 1 (lower text field)
     * @return std::string of the player name
     */
    std::string GetName(int index);

    /*!
     * @brief Calls GridFieldController::GetPlayer at the specified position to check which chip is inside a specific
     * grid field.
     *
     * @param column column where to determine the chip color
     * @param row row where to determine the chip color
     * @return 0 (no chip), 1 (red), 2 (blue)
     */
    int GetPlayerAt(int column, int row) const;

    /*!
     * @brief Shared pointer (ownership) to associated SessionModel
     */
    std::shared_ptr<SessionModel> m_SessionModel;

    /*!
     * @brief Weak pointer to this. Use of weak pointer avoids reference cycle
     */
    std::weak_ptr<SessionController> m_SessionController;

    /*!
     * @brief Weak pointer to parent GameController
     */
    std::weak_ptr<GameController> m_Game;

    /*!
     * @brief Shared pointer (ownership) to all grid fields in a 2D vector [m_Columns x m_Rows]
     */
    std::vector<std::vector<std::shared_ptr<GridFieldController>>> m_Grid;

    /*!
     * @brief Shared pointer (ownership) to ButtonController for a game termination
     */
    std::shared_ptr<ButtonController> m_GameTerminateButton;

    /*!
     * @brief Shared pointer (ownership) to ButtonController for a game restart
     */
    std::shared_ptr<ButtonController> m_GameRestartButton;

    /*!
     * @brief Array of shared pointers (ownership) to TextFieldController for entering player names
     */
    std::shared_ptr<TextFieldController> m_NameTextFields[2];

    /*!
     * @brief Shared pointer (ownership) to TextView for small "vs." text between names
     */
    std::shared_ptr<TextView> m_VSTextView;

    /*!
     * @brief Shared pointer (ownership) to TextView for showing the player name associated with status prompt
     */
    std::shared_ptr<TextView> m_StatusNameText;

    /*!
     * @brief Shared pointer (ownership) to TextView for showing a status message.
     */
    std::shared_ptr<TextView> m_StatusMessageText;

    /*!
     * @brief Array of shared pointer (ownership) to ButtonController for entering color choice
     */
    std::shared_ptr<ButtonController> m_ColorPickButtons[2];

    /*!
     * @brief Shared pointer (ownership) to ArrowView for pointing to text field of the current player
     */
    std::shared_ptr<ArrowView> m_CurrentPlayerArrow;

    /*!
     * @brief Shared pointer (ownership) to ClockController for showing the current inGame time or total time after
     * game ended
     */
    std::shared_ptr<ClockController> m_Clock;
};
