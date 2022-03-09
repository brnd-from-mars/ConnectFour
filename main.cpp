#include <string>
#include <cmath>
#include <iostream>
#include <vector>

#include "AppDelegate.hpp"

#include "ChipController.hpp"

#include "TextFieldController.hpp"


int main()
{
    AppDelegate::Get()->SetWindow(1280, 720, "Four Wins!");

    std::vector<std::shared_ptr<ChipController>> chips;

    for (int x = 0; x < 20; ++x)
    {
        for (int y = 0; y < 10; ++y)
        {
            chips.push_back(ChipController::MakeChip(1, x, y));
        }
    }

    auto tf = TextFieldController::MakeTextField(100.0f, 100.0f, 400.0f);
    tf->HandleTextEntry('4');
    tf->HandleTextEntry('2');
    tf->HandleTextEntry('0');
    tf->HandleDeleteKeyPress();

    while (AppDelegate::Get()->Update())
    {
    }

    AppDelegate::Delete();

    return 0;
}
