//
// Created by Brendan Berg on 15.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"

#include "ConnectFourUtility.hpp"

#include "ButtonController.hpp"

class ScoreBoardModel;
class ScoreBoardView;


/*!
 * @brief ScoreBoardController class represents the scoreboard.
 */
class ScoreBoardController : public BaseController
{
    friend ScoreBoardView;


public:

    /*!
     * @brief Static factory function creates a new empty session, sets references between the MVC elements and\
     * initializes the buttons to switch between the displayed score types.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width total width of the scoreboard
     * @return shared pointer to the new ScoreBoardController
     */
    static std::shared_ptr<ScoreBoardController>MakeScoreBoard(float x, float y, float width);

    /*!
     * @brief Constructor creates associated ScoreBoardModel and ScoreBoardView.
     *
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @param width total width of the scoreboard
     */
    ScoreBoardController(float x, float y, float width);

    /*!
     * @brief No-op.
     */
    void Update() override;

    /*!
     * @brief Adds the results of a game with a victory to the database in the associated model.
     *
     * @param game results of the played game
     */
    void AddGame(GameData game);

    /*!
     * @brief Adds the results of a game with a tie to the database in the associated model.
     *
     * @param game results of the played game
     */
    void AddTie(const GameData& game);


private:

    /*!
     * @brief Initiates the m_PrevScoreBoardButton and m_NextScoreBoardButton and registers the PrevScoreBoard and
     * NextScoreBoard functions as their respective callbacks.
     */
    void InitButtons();

    /*!
     * @brief Loads the previous scoreboard and updates the view.
     */
    void PrevScoreBoard();

    /*!
     * @brief Loads the next scoreboard and updates the view.
     */
    void NextScoreBoard();

    /*!
     * @brief Loads the top 5 players for the currently displayed scoreboard from the associated model and formats the
     * data to be forwarded to the associated view.
     */
    void UpdateView();

    /*!
     * @brief Shared pointer (ownership) to the associated model.
     */
    std::shared_ptr<ScoreBoardModel> m_ScoreBoardModel;

    /*!
     * @brief Shared pointer (ownership) to the associated view.
     */
    std::shared_ptr<ScoreBoardView> m_ScoreBoardView;

    /*!
     * @brief Weak pointer to this. Use of weak pointer avoids reference cycle.
     */
    std::weak_ptr<ScoreBoardController> m_ScoreBoardController;

    /*!
     * @brief Shared pointer (ownership) to ButtonController for going to the previous scoreboard.
     */
    std::shared_ptr<ButtonController> m_PrevScoreBoardButton;

    /*!
     * @brief Shared pointer (ownership) to ButtonController for going to the next scoreboard.
     */
    std::shared_ptr<ButtonController> m_NextScoreBoardButton;

    /*!
     * @brief Type of scoreboard to be shown. count is used to determine the total number of scoreboard types.
     */
    enum class ScoreBoardType
    {
        mostVictories,
        bestKD,
        leastMoves,
        leastTime,
        count
    } m_CurrentScoreBoard = ScoreBoardType::bestKD;


};
