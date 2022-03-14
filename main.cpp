#include <cmath>
#include <iostream>

#include "AppDelegate.hpp"

#include "GameController.hpp"
#include "TextFieldController.hpp"
#include "TextView.hpp"

#include "vendor/tinyxml2/tinyxml2.h"

#include "LinkedList.h" //TEST

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

    if (false)
    {
        tinyxml2::XMLDocument doc;
        doc.LoadFile("ScoreBoard.xml");

        auto root = doc.FirstChild();

        auto session = root->FirstChild();
        while (session != nullptr)
        {
            std::cout << session->FirstChildElement("Player")->GetText() << std::endl;
            std::cout << session->FirstChildElement("Time")->GetText() << std::endl;
            session = session->NextSibling();
        }

        session = doc.NewElement("Game");
        root->InsertEndChild(session);

        auto element = doc.NewElement("Player");
        element->SetText("Philip");
        session->InsertEndChild(element);

        element = doc.NewElement("Time");
        element->SetText(312);
        session->InsertEndChild(element);

        doc.SaveFile("ScoreBoard.xml");
    }

    //TEST**********************************************************************************************

    LinkedList list; 

    GameData game1;
    GameData game2;
    GameData game3;

    game1.time = 100;
    game2.time = 50;
    game3.time = 20;

    list.addElement(game1);
    list.addElement(game2);
    list.addElement(game3);

    for (int i = 0; i < 3; i++) {
        
        std::cout << "Game " << i + 1 << " time: " << list.getElementAt(i)->time << std::endl;
 
    }

    list.sort(SortBy::time);

    std::cout << "sorted list: \n" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << "Game " << i + 1 << " time: " << list.getElementAt(i)->time << std::endl;
    }

    //**************************************************************************************************

    while (AppDelegate::Get()->Update());

    AppDelegate::Delete();

    return 0;
}
