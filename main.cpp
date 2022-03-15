#include <cmath>
#include <iostream>

#include "AppDelegate.hpp"

#include "GameController.hpp"

#include "ConnectFourUtility.hpp"
#include "SessionModel.hpp"
#include "LinkedList.hpp"

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

    if (true)
    {
        LinkedList<GameData> list;

        GameData game1;
        GameData game2;
        GameData game3;

        game1.time = 100;
        game2.time = 50;
        game3.time = 20;

        list.addElement(game1);
        list.addElement(game2);
        list.addElement(game3);

        for (int i = 0; i < 3; i++)
        {
            std::cout << "game" << i + 1 << " time: " << list[i]->time << std::endl;
        }

        auto sortAfterTime = [](GameData* data) -> int {
            return data->time;
        };
        list.sort(sortAfterTime);

        std::cout << std::endl << "Sorted list:" << std::endl;
        for (int i = 0; i < 3; i++)
        {
            std::cout << "game" << i + 1 << " time: " << list[i]->time << std::endl;
        }
    }

    while (AppDelegate::Get()->Update());

    AppDelegate::Delete();

    return 0;
}
