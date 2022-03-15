//
// Created by Brendan Berg on 15.03.22.
//

#pragma once

#include <string>


struct GameData
{
    std::string winningPlayer;
    std::string loosingPlayer;
    int moves;
    int time;
};


struct PlayerData
{
    std::string name;
    int games;
    int victories;
};


// TODO: add fonts
// TODO: add color palette
// TODO: add view coordinates and sizes