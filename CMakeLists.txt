cmake_minimum_required(VERSION 3.16)

project(webview_test)

set(CMAKE_CXX_STANDARD 20)

add_executable(webview_test main.cpp)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(choc_tests "-framework WebKit -framework CoreServices")
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules (gtk3 REQUIRED gtk+-3.0 IMPORTED_TARGET)
    pkg_check_modules (webkit2 REQUIRED webkit2gtk-4.1 IMPORTED_TARGET)
    target_link_libraries (webview_test PUBLIC pthread PkgConfig::gtk3 PkgConfig::webkit2)
endif()
