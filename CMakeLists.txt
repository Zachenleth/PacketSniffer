cmake_minimum_required(VERSION 3.19)
project(PacketSnifferGUI LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(PacketSnifferGUI
    WIN32 MACOSX_BUNDLE
    source/cpp/main.cpp
    source/cpp/mainwindow.cpp
    source/headers/mainwindow.h
    mainwindow.ui
	
    source/headers/estructuras.h
    source/headers/funciones.h
    source/headers/libreria.h
    source/cpp/get_device_by_index.cpp
    source/cpp/open_device.cpp
    source/cpp/start_capture.cpp
    source/cpp/list_devices.cpp
    source/headers/export_csv.h
    source/cpp/export_csv.cpp
)

target_include_directories(PacketSnifferGUI PRIVATE
    source/cpp
    source/headers
    "C:/npcap-sdk-1.16/Include"
)

target_link_libraries(PacketSnifferGUI PRIVATE
    Qt6::Widgets
    "C:/Windows/System32/wpcap.dll"
    "C:/Windows/System32/Packet.dll"
    ws2_32
)

target_link_libraries(PacketSnifferGUI
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS PacketSnifferGUI
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET PacketSnifferGUI
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
