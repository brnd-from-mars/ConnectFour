//
// Created by Brendan Berg on 09.03.22.
//

#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "BaseController.hpp"

class ChipModel;
class ChipView;


class ChipController : public BaseController
{
    friend ChipModel;
    friend ChipView;

public:

    static std::shared_ptr<ChipController> MakeChip(int player, int column, int row);

    ChipController(int player, int column, int row);

    void HandleResetFocus();

    void HandleClick();

    void UpdateView();

    void Update() override;


private:

    std::shared_ptr<ChipModel> m_ChipModel;
    std::shared_ptr<ChipView> m_ChipView;


};