cmake_minimum_required(VERSION 3.17)
project(ConnectFour)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

add_executable(ConnectFour main.cpp AppDelegate.cpp
        GameModel.cpp GameController.cpp
        SessionModel.cpp SessionController.cpp
        ScoreBoardModel.cpp ScoreBoardView.cpp ScoreBoardController.cpp
        GridFieldModel.cpp GridFieldView.cpp GridFieldController.cpp
        ChipModel.cpp ChipView.cpp ChipController.cpp
        TextFieldModel.cpp TextFieldView.cpp TextFieldController.cpp
        ClockModel.cpp ClockView.cpp ClockController.cpp
        ButtonView.cpp ButtonController.cpp
        TextView.cpp
        ArrowView.cpp
        vendor/tinyxml2/tinyxml2.cpp)
target_link_libraries(ConnectFour sfml-graphics sfml-window)
