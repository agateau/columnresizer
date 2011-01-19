cmake_minimum_required(VERSION 2.8)

# Dependencies
find_package(Qt4 REQUIRED)

# Sources
set(qtsizegroupdemo_SRCS
    main.cpp
    qtsizegroup.cpp
    )

# Building
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
    )

qt4_automoc(${qtsizegroupdemo_SRCS})
add_executable(qtsizegroupdemo ${qtsizegroupdemo_SRCS})

target_link_libraries(qtsizegroupdemo
    ${QT_QTGUI_LIBRARIES}
    ${QT_QTCORE_LIBRARIES}
    )

# Install
install(TARGETS qtsizegroupdemo
    RUNTIME DESTINATION bin
    )
