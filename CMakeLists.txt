cmake_minimum_required(VERSION 3.29)
project(FoodApp)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(FoodApp
    .idea/.gitignore
    .idea/editor.xml
    .idea/FoodApp.iml
    .idea/misc.xml
    .idea/modules.xml
    .idea/workspace.xml
    cart.cpp
    cart.h
    cli.cpp
    cli.h
    fileio.cpp
    fileio.h
    main.cpp
    menu.txt)
