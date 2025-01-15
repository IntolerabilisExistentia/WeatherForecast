cmake_minimum_required(VERSION 3.12)

project(
    labwork7
    VERSION 1.0
    DESCRIPTION "C++ Year 2023 labwork6"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} bin/main.cpp lib/weather.cpp lib/cities.cpp lib/tui.cpp)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)

FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui GIT_TAG d301fab1f4ecdd3544ed99b9c98e647d5804c341)

FetchContent_MakeAvailable(cpr json ftxui)

target_link_libraries(${PROJECT_NAME} PUBLIC cpr::cpr nlohmann_json::nlohmann_json ftxui::screen ftxui::dom ftxui::component)

