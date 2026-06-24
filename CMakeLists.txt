cmake_minimum_required(VERSION 3.19)
project(PacketSnifferGUI LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(PacketSnifferGUI
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
	
    backend/estructuras.h
    backend/funciones.h
    backend/libreria.h
    backend/get_device_by_index.cpp
    backend/open_device.cpp
    backend/start_capture.cpp
    backend/list_devices.cpp
    backend/export_csv.h
    backend/export_csv.cpp
)

target_include_directories(PacketSnifferGUI PRIVATE
    backend
    "C:/Users/emald/Downloads/npcap-sdk-1.16/Include"
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
