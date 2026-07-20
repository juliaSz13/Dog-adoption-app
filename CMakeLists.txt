cmake_minimum_required(VERSION 3.16)
project(DogShelter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(DogShelter
        main.cpp
        Dog.cpp Dog.h
        Repository.cpp Repository.h
        Service.cpp Service.h
        UserService.cpp UserService.h
        AdoptionList.cpp AdoptionList.h
        Validator.cpp Validator.h
        Exceptions.h
        tests.cpp tests.h
        MainWindow.cpp MainWindow.h MainWindow.ui
        AdminWindow.cpp AdminWindow.h
        UserWindow.cpp UserWindow.h
        Command.h
        AdoptionModelTable.h
)
target_link_libraries(DogShelter Qt6::Widgets)