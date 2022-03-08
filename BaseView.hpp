//
// Created by Brendan Berg on 08.03.22.
//

#pragma once

#include <iostream>

class AppDelegate;


class BaseView
{

public:

    BaseView()
        : m_Layer(0)
    {}

    virtual void Draw() = 0;

    int GetLayer() const
    {
        return m_Layer;
    }




protected:

    int m_Layer;


};
