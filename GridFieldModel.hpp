//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseModel.hpp"

class GridFieldController;


/*!
 * @brief GridFieldModel represents data associated with a single field in the ConnectFour grid.
 */
class GridFieldModel : public BaseModel
{
    friend GridFieldController;


public:

    /*!
     * @brief Constructor constructs the GridFieldModel with the given column and row position.
     *
     * @param column column where the field is positioned
     * @param row row where the field is positioned
     */
    GridFieldModel(int column, int row);

    /*!
     * @brief No-op.
     */
    void Update() override;


private:

    /*!
     * @brief Weak pointer to the associated controller.
     */
    std::weak_ptr<GridFieldController> m_GridFieldController;

    /*!
     * @brief Column where the filed is positioned.
     */
    int m_Column;

    /*!
     * @brief Row where the field is positioned.
     */
    int m_Row;


};
