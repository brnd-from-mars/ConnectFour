#include <string>
#include <cmath>
#include <iostream>

#include "AppDelegate.hpp"

#include "ChipModel.hpp"
#include "ChipView.hpp"
#include "ChipController.hpp"


int main()
{
    AppDelegate::Get()->SetWindow(2560, 1440, "Four Wins!");

    auto chip1 = ChipController::MakeChip(1, 0, 0);
    auto chip2 = ChipController::MakeChip(1, 1, 0);
    auto chip3 = ChipController::MakeChip(2, 1, 1);

    while (AppDelegate::Get()->Update())
    {
    }

    AppDelegate::Delete();

    return 0;
}
