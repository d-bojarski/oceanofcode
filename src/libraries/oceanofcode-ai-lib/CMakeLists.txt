include_directories(../../apps/oceanofcode-ai)

file(GLOB SOURCES_LIB
    ../../apps/oceanofcode-ai/point.h
    ../../apps/oceanofcode-ai/point.cpp
    ../../apps/oceanofcode-ai/ai.h
    ../../apps/oceanofcode-ai/ai.cpp
    ../../apps/oceanofcode-ai/grid.h
    ../../apps/oceanofcode-ai/grid.cpp
    ../../apps/oceanofcode-ai/player.h
    ../../apps/oceanofcode-ai/player.cpp
)
add_library(oceanofcode-ai-lib ${SOURCES_LIB})