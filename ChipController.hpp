//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseController.hpp"

class ChipModel;
class ChipView;


/*!
 * @brief ChipController class represents a single chip in a GridFieldController.
 */
class ChipController : public BaseController
{
    friend ChipModel;
    friend ChipView;


public:

    /*!
     * @brief Static factory function creates a new chip for the specified player at the given coordinates and sets
     * references between the MVC elements
     *
     * @param player 0 (red), 1 (blue)
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     * @return shared pointer to the new ChipController
     */
    static std::shared_ptr<ChipController> MakeChip(int player, float x, float y);

    /*!
     * @brief Constructor creates associated ChipModel and ChipView
     *
     * @param player 0 (red), 1 (blue)
     * @param x x-coordinate on the screen
     * @param y y-coordinate on the screen
     */
    ChipController(int player, float x, float y);

    /*!
     * @brief No-op.
     */
    void Update() override;

    /*!
     * @brief Enable / disable highlight of the chip
     *
     * @param highlight enable highlight?
     */
    void SetHighlight(bool highlight);

    /*!
     * @brief Which player's chip is this?
     *
     * @return 1 (red), 2 (blue)
     */
    int GetPlayer() const;


private:

    /*!
     * @brief Push highlight setting to the view
     */
    void UpdateView();

    /*!
     * @brief shared pointer (ownership) to associated ChipModel
     */
    std::shared_ptr<ChipModel> m_ChipModel;

    /*!
     * @brief shared pointer (ownership) to associated ChipView
     */
    std::shared_ptr<ChipView> m_ChipView;


};
