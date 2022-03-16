#include <cmath>
#include <iostream>

#include "AppDelegate.hpp"

#include "GameController.hpp"


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

    AppDelegate::Get()->SetWindow(1200, 700, "Connect Four");
    AppDelegate::Get()->SetBackgroundColor(ColorPalette::Basestar);
    AppDelegate::Get()->SetFrameRate(60);

    auto game = GameController::MakeGameController(columns, rows);

    try
    {
        while (AppDelegate::Get()->Update());
    }
    catch (const std::runtime_error& error)
    {
        std::cerr << "AppDelegate Update failed: " << error.what() << std::endl;
    }


    AppDelegate::Delete();

    return 0;
}
