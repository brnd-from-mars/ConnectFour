#include <string>
#include <cmath>
#include <iostream>
#include <vector>

#include "AppDelegate.hpp"

#include "ChipModel.hpp"
#include "ChipView.hpp"
#include "ChipController.hpp"


int main()
{
    AppDelegate::Get()->SetWindow(1280, 720, "Four Wins!");

    std::vector<std::shared_ptr<ChipController>> chips;

    for (int x = 0; x < 25; ++x)
    {
        for (int y = 0; y < 20; ++y)
        {
            chips.push_back(ChipController::MakeChip(1, x, y));
        }
    }

    while (AppDelegate::Get()->Update())
    {
    }

    AppDelegate::Delete();

    return 0;
}
