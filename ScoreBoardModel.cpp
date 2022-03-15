//
// Created by Brendan Berg on 15.03.22.
//

#include "ScoreBoardModel.hpp"

#include "vendor/tinyxml2/tinyxml2.h"

#include <iostream>


ScoreBoardModel::ScoreBoardModel()
{
    tinyxml2::XMLDocument saveFile;
    if (saveFile.LoadFile("ScoreBoard.xml") != tinyxml2::XML_SUCCESS)
    {
        std::cout << "ScoreBoard.xml not found" << std::endl;
    }
}


void ScoreBoardModel::Update()
{

}
