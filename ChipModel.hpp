//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>

#include "BaseModel.hpp"

class ChipController;


/*!
 * @brief ChipModel represents data associated with a single chip in a GridFieldController.
 */
class ChipModel : public BaseModel
{
    friend ChipController;


public:

    /*!
     * @brief Constructor constructs the ChipModel for the given player
     *
     * @param player 0 (red), 1 (blue)
     */
    explicit ChipModel(int player);

    /*!
     * @brief No-op.
     */
    void Update() override;


private:

    /*!
     * @brief Enable / disable highlight of the chip
     *
     * @param highlight enable highlight?
     */
    void SetHighlight(bool highlight);

    /*!
     * @brief weak pointer to the associated controller
     */
    std::weak_ptr<ChipController> m_ChipController;

    /*!
     * @brief 0 (red), 1 (blue)
     */
    int m_Player;

    /*!
     * @brief highlight enabled?
     */
    bool m_Highlighted = false;


};
