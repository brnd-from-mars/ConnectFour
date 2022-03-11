#include <cmath>
#include <vector>

#include "AppDelegate.hpp"

#include "GameController.hpp"
#include "TextFieldController.hpp"
#include "TextView.hpp"


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

    AppDelegate::Get()->SetWindow(1250, 700, "Connect Four");

    auto game = GameController::MakeGameController(columns, rows);

    auto tf = TextFieldController::MakeTextField(750.0f, 170.0f, 200.0f);

    auto text1 = std::make_shared<TextView>(48.0f, 22.0f, 75.0f, "Tron", "C0nnect F0ur", ColorPalette::Cyan);
    AppDelegate::Get()->RegisterView(text1);
    auto text2 = std::make_shared<TextView>(52.0f, 26.0f, 75.0f, "Tron", "C0nnect F0ur", ColorPalette::Orange);
    AppDelegate::Get()->RegisterView(text2);

    while (AppDelegate::Get()->Update())
    {
    }

    AppDelegate::Delete();

    return 0;
}
