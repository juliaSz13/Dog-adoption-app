cmake_minimum_required(VERSION 3.16)
project(DogShelter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ui)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(domain repository service ui tests)

add_executable(DogShelter
        main.cpp
        domain/Dog.cpp domain/Dog.h
        domain/Validator.cpp domain/Validator.h
        domain/Exceptions.h
        repository/Repository.cpp repository/Repository.h
        repository/AdoptionList.cpp repository/AdoptionList.h
        service/Service.cpp service/Service.h
        service/UserService.cpp service/UserService.h
        service/Command.h
        ui/MainWindow.cpp ui/MainWindow.h ui/MainWindow.ui
        ui/AdminWindow.cpp ui/AdminWindow.h
        ui/UserWindow.cpp ui/UserWindow.h
        ui/AdoptionModelTable.h
        tests/tests.cpp tests/tests.h
)
target_link_libraries(DogShelter Qt6::Widgets)
