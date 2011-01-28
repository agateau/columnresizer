cmake_minimum_required(VERSION 2.8)

# Dependencies
find_package(Qt4 REQUIRED)

# Sources
set(columnresizerdemo_SRCS
    main.cpp
    columnresizer.cpp
    )

# Building
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
    )

qt4_wrap_ui(columnresizerdemo_UI_SRCS
    demowidget.ui
    )
qt4_automoc(${columnresizerdemo_SRCS})
add_executable(columnresizerdemo ${columnresizerdemo_SRCS} ${columnresizerdemo_UI_SRCS})

target_link_libraries(columnresizerdemo
    ${QT_QTGUI_LIBRARIES}
    ${QT_QTCORE_LIBRARIES}
    )

# Install
install(TARGETS columnresizerdemo
    RUNTIME DESTINATION bin
    )
