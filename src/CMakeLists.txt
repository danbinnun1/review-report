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
include_directories(${CMAKE_SOURCE_DIR}/searching_data_parser)


link_directories(${CMAKE_SOURCE_DIR})
#link_directories(/usr/local/Cellar/curlpp/0.8.1/lib/)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED) 
find_package (Threads)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBXMLXX REQUIRED IMPORTED_TARGET libxml++-2.6)


add_executable(a.out main.cpp grade/cache-grading/links-cache/LinksTextCache.cpp grade/cache-grading/links-cache/split.cpp grade/cache-grading/webpage-grading/WebPageGrader.cpp
grade/cache-grading/LinksCacheGrader.cpp grade/cache-grading/webpage-grading/AskReviewType.cpp grade/cache-grading/webpage-grading/open-url/LinuxURLOpener.cpp 
search/get_html.cpp search/extract_links.cpp search/google_search.cpp searching_data_parser/CsvParser.cpp searching_data_parser/file_reading.cpp)

include_directories("/usr/include/libxml++-2.6/libxml++")
target_link_libraries(a.out PkgConfig::LIBXMLXX)
include_directories(${LIBXML2_INCLUDE_DIR})
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(a.out ${CURL_LIBRARIES})
target_link_libraries (a.out ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(a.out curlpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)