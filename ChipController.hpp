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

    static std::shared_ptr<ChipController> MakeChip(int player, float x, float y);

    ChipController(int player, float x, float y);

    void Update() override;

    void SetHighlight(bool highlight);

    int GetPlayer() const;


private:

    void UpdateView();

    std::shared_ptr<ChipModel> m_ChipModel;
    std::shared_ptr<ChipView> m_ChipView;


};
