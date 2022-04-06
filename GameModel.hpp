//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseModel.hpp"

class GameController;


/*!
 * @brief GameModel represents data associated with the entire ConnectFour game.
 */
class GameModel : public BaseModel
{
    friend GameController;


public:

    /*!
     * @brief Constructor constructs the GameModel with given number of columns and rows.
     *
     * @param columns number of columns in the ConnectFour grid
     * @param rows number of rows in the ConnectFour grid
     */
    GameModel(int columns, int rows);


    /*!
     * @brief No-op.
     */
    void Update() override;


private:

    /*!
     * @brief Weak pointer to the associated controller.
     */
    std::weak_ptr<GameController> m_GameController;

    /*!
     * @brief Number of columns in the ConnectFour grid.
     */
    int m_Columns;

    /*!
     * @brief Number of rows in the ConnectFour grid.
     */
    int m_Rows;


};
