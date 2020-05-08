include_directories(../../apps/oceanofcode-ai)

add_definitions(-DLIBRARY)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB SOURCES_LIB
    ../../apps/oceanofcode-ai/point.h
    ../../apps/oceanofcode-ai/point.cpp
    ../../apps/oceanofcode-ai/ai.h
    ../../apps/oceanofcode-ai/ai.cpp
    ../../apps/oceanofcode-ai/grid.h
    ../../apps/oceanofcode-ai/grid.cpp
    ../../apps/oceanofcode-ai/player.h
    ../../apps/oceanofcode-ai/player.cpp
    ../../apps/oceanofcode-ai/messagemanager.h
    ../../apps/oceanofcode-ai/messagemanager.cpp
    ../../apps/oceanofcode-ai/node.h
    ../../apps/oceanofcode-ai/node.cpp
    ../../apps/oceanofcode-ai/path.h
    ../../apps/oceanofcode-ai/path.cpp
)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
add_library(oceanofcode-ai-lib ${SOURCES_LIB})
target_link_libraries(oceanofcode-ai-lib Qt5::Core)