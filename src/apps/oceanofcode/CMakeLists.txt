file(GLOB SOURCES
    *.h
    *.cpp
    oceanofcode.qrc
)
add_definitions(-DLIBRARY)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include oceanofcode-ia folder.
include_directories(../oceanofcode-ai)
link_directories(../../libraries/oceanofcode-ai-lib)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
add_executable(oceanofcode ${SOURCES})
target_link_libraries(oceanofcode Qt5::Widgets)
target_link_libraries(oceanofcode Qt5::Core)
target_link_libraries(oceanofcode Qt5::Gui)
target_link_libraries(oceanofcode Qt5::Network)
target_link_libraries(oceanofcode oceanofcode-ai-lib)
