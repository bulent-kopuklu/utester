cmake_minimum_required(VERSION 3.0.0)
project(utester VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src)

add_library(
    utester
    STATIC
    "src/lib/Object.cpp"
    "src/lib/Scope.cpp"
    "src/lib/Suit.cpp"
    "src/exec/TestExecuter.cpp"
    "src/exec/ScopeExecuter.cpp"
    "src/util.cpp"
    "src/Output.cpp"
    "src/TestEngine.cpp"
    "src/main.cpp"
    )

target_include_directories(utester PUBLIC include)
target_link_libraries(utester)

include(GNUInstallDirs)
install(
    TARGETS ${PROJECT_NAME} 
    DESTINATION ${CMAKE_INSTALL_PREFIX}/utester
)

install(
    FILES 
    include/utester.h
    DESTINATION ${CMAKE_INSTALL_PREFIX}/utester/include
)