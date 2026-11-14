cmake_minimum_required(VERSION 3.24)
project(lab_4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Задаем параметр для корректной работы со временем скачивания архивов (решает ошибку CMP0135)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Укажите ваш main файл (проверьте, в какой папке он лежит: src/main.cpp или просто main.cpp)
add_executable(lab_4 src/main.cpp)

# Подключение папки с заголовочными файлами
target_include_directories(lab_4 PRIVATE include)

target_link_libraries(lab_4 PRIVATE GTest::gtest GTest::gtest_main)