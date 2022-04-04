//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"

#include "ChipController.hpp"

class GridFieldModel;
class GridFieldView;

class SessionController;


/*!
 * @brief GridFieldController class represents a single field in the ConnectFour grid. It may or may not contain a
 * ChipController.
 */
class GridFieldController : public BaseController
{
    friend GridFieldModel;
    friend GridFieldView;


public:

    /*!
     * @brief Static factory function creates a new grid field and sets references between the MVC elements.
     *
     * @param session weak pointer to the parent SessionController in the MVC tree
     * @param column column where the field is positioned
     * @param row row where the field is positioned
     * @return shared pointer to the new GridFieldController
     */
    static std::shared_ptr<GridFieldController> MakeGridField(const std::weak_ptr<SessionController>& session,
                                                              int column, int row);

    /*!
     * @brief Constructor creates associated GridFieldModel and GridFieldView.
     *
     * @param session weak pointer to the parent SessionController in the MVC tree
     * @param column column where the field is positioned
     * @param row row where the field is positioned
     */
    GridFieldController(const std::weak_ptr<SessionController>& session, int column, int row);

    /*!
     * @brief No-op.
     */
    void Update() override;

    /*!
     * @brief Constructs a new chip by the specified player and places it at the center of the field.
     *
     * @param player 0 (red), 1 (blue)
     */
    void SetChip(int player);

    /*!
     * @brief Enable / Disable highlight of the current field
     *
     * @param highlight enable highlight?
     */
    void SetHighlightChip(bool highlight);

    /*!
     * @brief Does the field contain a chip?
     *
     * @return has chip?
     */
    bool HasChip() const;

    /*!
     * @brief Which player's chip is in the field?
     *
     * @return 0 (none), 1 (red), 2 (blue)
     */
    int GetPlayer() const;

    /*!
     * @brief Returns column of the field
     *
     * @return column
     */
    int GetColumn() const;

    /*!
     * @brief Returns row of the field
     *
     * @return row
     */
    int GetRow() const;


private:

    /*!
     * @brief Handles a click by forwarding the event to the SessionController.
     */
    void HandleClick();

    /*!
     * @brief shared pointer (ownership) to associated GridFieldModel
     */
    std::shared_ptr<GridFieldModel> m_GridFieldModel;

    /*!
     * @brief shared pointer (ownership) to associated GridFieldView
     */
    std::shared_ptr<GridFieldView> m_GridFieldView;

    /*!
     * weak pointer to the parent SessionController in the MVC-tree
     */
    std::weak_ptr<SessionController> m_Session;

    /*!
     * shared pointer (ownership) to the (maybe) contained ChipController
     */
    std::shared_ptr<ChipController> m_Chip;


};
