cmake_minimum_required(VERSION 3.17)
project(FourWins)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

add_executable(FourWins main.cpp AppDelegate.cpp
        GameModel.cpp GameController.cpp
        SessionModel.cpp SessionController.cpp
        GridFieldModel.cpp GridFieldView.cpp GridFieldController.cpp
        ChipModel.cpp ChipView.cpp ChipController.cpp
        TextFieldModel.cpp TextFieldView.cpp TextFieldController.cpp
        ButtonView.cpp ButtonController.cpp
        TextView.cpp
        ArrowView.cpp
        ScoreBoardView.cpp)
target_link_libraries(FourWins sfml-graphics sfml-window)
