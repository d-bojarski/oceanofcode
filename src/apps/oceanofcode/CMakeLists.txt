file(GLOB SOURCES
    *.h
    *.cpp
    oceanofcode.qrc
    #../oceanofcode-ia/grid.cpp
)

#set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include oceanofcode-ia folder.
include_directories(../oceanofcode-ai)
link_directories(../../libraries/oceanofcode-ai-lib)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_executable(oceanofcode ${SOURCES})
target_link_libraries(oceanofcode Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Network)
target_link_libraries(oceanofcode oceanofcode-ai-lib)
