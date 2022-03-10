#include <string>
#include <cmath>
#include <iostream>
#include <vector>

#include "AppDelegate.hpp"

#include "GameController.hpp"
#include "ChipController.hpp"
#include "TextFieldController.hpp"


int ParseIntegerArgument(int argc, const char** argv, int n, int min, int max)
{
    if (n >= argc)
    {
        return max;
    }

    auto m = strtol(argv[n], nullptr, 10);

    if (min > m)
    {
        return min;
    }
    if (m > max)
    {
        return max;
    }

    return m;
}


int main(int argc, const char** argv)
{
    auto columns = ParseIntegerArgument(argc, argv, 1, 4, 25);
    auto rows = ParseIntegerArgument(argc, argv, 2, 4, 20);

    AppDelegate::Get()->SetWindow(1280, 720, "Four Wins!");

    auto game = GameController::MakeGameController(columns, rows);

    /*std::vector<std::shared_ptr<ChipController>> chips;
    for (int x = 0; x < 20; ++x)
    {
        for (int y = 0; y < 10; ++y)
        {
            chips.push_back(ChipController::MakeChip(1, x, y));
        }
    }*/

    /*auto tf = TextFieldController::MakeTextField(100.0f, 100.0f, 400.0f);
    tf->HandleTextEntry('4');
    tf->HandleTextEntry('2');
    tf->HandleTextEntry('0');
    tf->HandleDeleteKeyPress();*/

    while (AppDelegate::Get()->Update())
    {
    }

    AppDelegate::Delete();

    return 0;
}
