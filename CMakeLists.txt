# Windows
cmake_minimum_required(VERSION 3.16)
project(flappy_bird)

set(CMAKE_CXX_STANDARD 20)

set(SFML_INCLUDE_DIR "C:/SFML/include")
set(SFML_LIB_DIR "C:/SFML/lib")


add_executable(flappy_bird main.cpp)

target_include_directories(flappy_bird PRIVATE
        ${SFML_INCLUDE_DIR}
        headers
)

target_link_directories(flappy_bird PRIVATE ${SFML_LIB_DIR})

# Link libraries (add -d for Debug builds)
target_link_libraries(flappy_bird PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
)

#############################################################


## Linux
#cmake_minimum_required(VERSION 3.16)
#project(SFMLTest)
#
#set(CMAKE_CXX_STANDARD 17)
#
#include_directories(/usr/local/include)
#link_directories(/usr/local/lib)
#
#add_executable(SFMLTest main.cpp)
#
#target_link_libraries(SFMLTest
#        sfml-graphics
#        sfml-window
#        sfml-system
#)
#############################################################
