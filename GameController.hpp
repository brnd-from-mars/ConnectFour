//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"

#include "GameModel.hpp"

#include "SessionController.hpp"
#include "ScoreBoardController.hpp"
#include "TextView.hpp"


/*!
 * @brief GameController controls the ConnectFour game from game startup to window close. Owns ScoreBoardController
 * and current SessionController. Root class of the MVC tree.
 */
class GameController : public BaseController
{
    friend GameModel;


public:

    /*
     * @brief Static factory function for GameController sets references between the MVC elements.
     *
     * @param columns number of columns in the ConnectFour grid
     * @param rows number of rows in the ConnectFour grid
     * @return Shared pointer to the new GameController
    */
    static std::shared_ptr<GameController> MakeGameController(int columns, int rows);

    /*!
     * @brief Constructor creates associated GameModel. Initializes Headline views and ScoreBoard.
     *
     * @param columns number of columns in the ConnectFour grid
     * @param rows number of rows in the ConnectFour grid
     */
    GameController(int columns, int rows);

    /*!
     * @brief Destructor destructs GameController.
     */
    virtual ~GameController();

    /*!
     * @brief Checks if session is (still) valid and (re-)constructs a new one after game is terminated. Copies old game
     * (player names and colors are preserved) in case the game was restarted.
     */
    void Update() override;

    /*!
     * @brief Add results of finished game (with winning and loosing player) to the ScoreBoard.
     *
     * @param game GameData with the results of the played game
     */
    void AddGameToScoreBoard(GameData game);

    /*!
     * @brief Add results of finished game (that resulted in a tie) to the ScoreBoard.
     *
     * @param game GameData with the results of the played game. Distinction in WinningPLayer and LoosingPlayer is not
     * relevant
     */
    void AddTieToScoreBoard(const GameData& game);


private:

    /*!
     * @brief Shared pointer (ownership) to associated GameModel
     */
    std::shared_ptr<GameModel> m_GameModel;

    /*!
     * @brief Weak pointer to this. Use of weak pointer avoids reference cycle
     */
    std::weak_ptr<GameController> m_GameController;

    /*!
     * @brief Shared pointer (ownership) to current SessionController
     */
    std::shared_ptr<SessionController> m_Session;

    /*!
     * @brief Shared pointer (ownership) to ScoreBoardController
     */
    std::shared_ptr<ScoreBoardController> m_ScoreBoard;

    /*!
     * @brief Shared pointer (ownership) to TextView to output headline ("Connect Four") in cyan
     */
    std::shared_ptr<TextView> m_HeadlineCyan;

    /*!
     * @brief Shared pointer (ownership) to TextView to output headline ("Connect Four") in orange
     */
    std::shared_ptr<TextView> m_HeadlineOrange;


};
