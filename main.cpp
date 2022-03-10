#include <string>
#include <cmath>
#include <iostream>
#include <vector>

#include "AppDelegate.hpp"

#include "GameController.hpp"
#include "ChipController.hpp"
#include "TextFieldView.hpp"
#include "TextFieldController.hpp"
#include "ButtonView.hpp"


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

    AppDelegate::Get()->SetWindow(1250, 700, "Connect Four!");

    auto game = GameController::MakeGameController(columns, rows);

    auto tf = TextFieldController::MakeTextField(725.0f, 50.0f, 200.0f);

    while (AppDelegate::Get()->Update())
    {
    }

    AppDelegate::Delete();

    return 0;
}
