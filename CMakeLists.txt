cmake_minimum_required(VERSION 3.5)

project(file_system_statistics LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(file_system_statistics SHARED
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/filedirinfo.cpp
    src/filedirinfo.h
    src/statisticscollector.cpp
    src/statisticscollector.h
    src/statisticsmodel.cpp
    src/statisticsmodel.h
  )
else()
  add_executable(file_system_statistics
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/mainwindow.ui
    src/filedirinfo.cpp
    src/filedirinfo.h
    src/statisticscollector.cpp
    src/statisticscollector.h
    src/statisticsmodel.cpp
    src/statisticsmodel.h
  )
endif()

target_link_libraries(file_system_statistics PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
