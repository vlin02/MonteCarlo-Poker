cmake_minimum_required(VERSION 3.16)
project(MonteCarloPoker)

set(CMAKE_CXX_STANDARD 17)

add_executable(MonteCarloPoker main.cpp samples.cpp simulator.cpp tables.cpp tools.cpp cards.cpp cards.h)