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


class GridFieldController : public BaseController
{

public:

    static std::shared_ptr<GridFieldController> MakeGridFieldController(const std::weak_ptr<SessionController>& sessionController, int column, int row);

    GridFieldController(const std::weak_ptr<SessionController>& sessionController, int column, int row);

    void Update() override;

    void HandleClick();

    void SetChip(int player);

    bool HasChip() const;

    int GetPlayer() const;


private:

    std::shared_ptr<GridFieldModel> m_GridFieldModel;
    std::shared_ptr<GridFieldView> m_GridFieldView;

    std::weak_ptr<SessionController> m_SessionController;

    std::shared_ptr<ChipController> m_Chip;


};
