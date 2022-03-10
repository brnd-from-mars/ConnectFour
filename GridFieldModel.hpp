//
// Created by Brendan Berg on 10.03.22.
//

#pragma once

#include <memory>

#include "BaseModel.hpp"

class GridFieldController;


class GridFieldModel : public BaseModel
{
    friend GridFieldController;

public:

    GridFieldModel(int column, int row);


private:

    int m_Column;

    int m_Row;


};
