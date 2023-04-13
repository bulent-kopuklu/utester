cmake_minimum_required(VERSION 3.0.0)
project(utester VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src include)

# message("CMAKE_COMMAND:                 ${CMAKE_COMMAND}")
# message("CMAKE_BUILD_TYPE:              ${CMAKE_BUILD_TYPE}")
# message("CMAKE_MAKE_PROGRAM:            ${CMAKE_MAKE_PROGRAM}")
# message("CMAKE_CXX_FLAGS_DEBUG:         ${CMAKE_CXX_FLAGS_DEBUG}")
# message("CMAKE_CXX_FLAGS_RELEASE:       ${CMAKE_CXX_FLAGS_RELEASE}")
# message("CMAKE_CXX_FLAGS_RELWITHDEBINFO:${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
# message("CMAKE_CXX_FLAGS:               ${CMAKE_CXX_FLAGS}")
# message("CMAKE_TOOLCHAIN_FILE:          ${CMAKE_TOOLCHAIN_FILE}")
# message("ANDROID_PLATFORM:              ${ANDROID_PLATFORM}")
# message("CMAKE_EXTERNAL_ARGS:           ${CMAKE_EXTERNAL_ARGS}")


add_library(
    utester
    STATIC
    "src/exec/TestExecuter.cpp"
    "src/exec/ScopeExecuter.cpp"
    "src/util.cpp"
    "src/Output.cpp"
    "src/TestEngine.cpp"
    "src/main.cpp"
    )

target_include_directories(utester PUBLIC include)
#target_link_libraries(utester)

set_target_properties(utester PROPERTIES PUBLIC_HEADER include/utester.h)

install(
    TARGETS ${PROJECT_NAME} ARCHIVE PUBLIC_HEADER    
)

# install(
#     FILES 
#     include/utester.h
#     PUBLIC_HEADER
#     DESTINATION ${CMAKE_INSTALL_PREFIX}/utester
# )