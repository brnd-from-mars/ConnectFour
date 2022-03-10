//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseController.hpp"


class GridFieldController : public BaseController
{

public:

    static std::shared_ptr<GridFieldController> MakeGridFieldController(int column, int row);

    GridFieldController(int column, int row);

    void Update() override;

};
