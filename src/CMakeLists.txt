cmake_minimum_required(VERSION 3.0.0)
project(ex2 VERSION 0.1.0)

include(CTest)
set(C_STANDARD C99)
set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic)
enable_testing()

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/grade)
include_directories(${CMAKE_SOURCE_DIR}/search)
include_directories(${CMAKE_SOURCE_DIR}/grade/cache-grading)
include_directories(${CMAKE_SOURCE_DIR}/grade/cache-grading/links-cache)
include_directories(${CMAKE_SOURCE_DIR}/grade/cache-grading/webpage-grading)
include_directories(${CMAKE_SOURCE_DIR}/grade/cache-grading/webpage-grading/open-url)


link_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")
add_executable(a.out main.cpp grade/cache-grading/links-cache/LinksTextCache.cpp grade/cache-grading/links-cache/split.cpp grade/cache-grading/webpage-grading/WebPageGrader.cpp
grade/cache-grading/LinksCacheGrader.cpp grade/cache-grading/webpage-grading/AskReviewType.cpp)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)