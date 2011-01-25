cmake_minimum_required(VERSION 2.8)

# Dependencies
find_package(Qt4 REQUIRED)

# Sources
set(widgetresizerdemo_SRCS
    main.cpp
    widgetresizer.cpp
    )

# Building
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${QT_INCLUDE_DIR}
    ${QT_QTCORE_INCLUDE_DIR}
    ${QT_QTGUI_INCLUDE_DIR}
    )

qt4_wrap_ui(widgetresizerdemo_UI_SRCS
    demowidget.ui
    )
qt4_automoc(${widgetresizerdemo_SRCS})
add_executable(widgetresizerdemo ${widgetresizerdemo_SRCS} ${widgetresizerdemo_UI_SRCS})

target_link_libraries(widgetresizerdemo
    ${QT_QTGUI_LIBRARIES}
    ${QT_QTCORE_LIBRARIES}
    )

# Install
install(TARGETS widgetresizerdemo
    RUNTIME DESTINATION bin
    )
