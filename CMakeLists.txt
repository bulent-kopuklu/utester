cmake_minimum_required(VERSION 3.0.0)
project(utester VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src include)

message("@@@project-dir    : ${PROJECT_SOURCE_DIR}")
message("@@@build-type     : ${CMAKE_BUILD_TYPE}")
message("@@@binary-dir     : ${CMAKE_BINARY_DIR}")
message("@@@cache-file-dir : ${CMAKE_CACHEFILE_DIR}")
message("@@@ext-install-dir: ${EXTERNAL_INSTALL_DIR}")
message("@@@ccxx           : ${CMAKE_CXX_COMPILER}")
message("@@@cc             : ${CMAKE_C_COMPILER}")
message("@@@asm            : ${CMAKE_ASM_COMPILER}")
message("@@@cxx-dbg-flags  : ${CMAKE_CXX_FLAGS_DEBUG}")
message("@@@cxx-rel-flags  : ${CMAKE_CXX_FLAGS_RELEASE}")
message("@@@cxx-rwd-flags  : ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message("@@@cxx-flags      : ${CMAKE_CXX_FLAGS}")
message("@@@exe-ld-flags   : ${CMAKE_EXE_LINKER_FLAGS}")
message("@@@so-ld-flags    : ${CMAKE_SHARED_LINKER_FLAGS}")

message("CMAKE_COMMAND: ${CMAKE_COMMAND}")
message("CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")


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

#target_include_directories(utester PUBLIC include)
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