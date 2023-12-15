cmake_minimum_required(VERSION 3.14)
project(Project1 VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

include(FetchContent)
FetchContent_Declare( 
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)

# include(CTest)
enable_testing()

add_executable(Main src/main.cpp)
add_executable(test-unit test-unit/test.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
include_directories(test-unit)

target_link_libraries(test-unit PRIVATE Catch2::Catch2WithMain)