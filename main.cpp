#include <cmath>

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

    auto game = GameController::MakeGameController(columns, rows);

    while (AppDelegate::Get()->Update());

    AppDelegate::Delete();

    return 0;
}
