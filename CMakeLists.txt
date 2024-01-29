cmake_minimum_required(VERSION 3.28.0)
# Fix behavior of CMAKE_CXX_STANDARD when targeting macOS.
if (POLICY CMP0025)
    cmake_policy(SET CMP0025 NEW)
endif ()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
project(cdlib VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(dclib src/main.cpp)


target_include_directories(dclib PUBLIC include)
target_sources(dclib PUBLIC src/book-info.cpp)

add_subdirectory(extern/cxxopts)
target_include_directories(dclib PUBLIC cxxopts)
target_link_libraries(dclib PUBLIC cxxopts)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
