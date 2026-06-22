# Compilador C++
CPP = g++

# Obtiene la ruta absoluta del directorio donde se encuentra el Makefile
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
ROOT_DIR := $(dir $(MKFILE_PATH))

# Ejecutable
TARGET = $(RELEASE_DIR)PacketSniffer.exe
ONLY_TARGET = PacketSniffer.exe

# Uso de rutas relativas con la variable raíz
SRC_DIR := $(ROOT_DIR)source/
CPP_DIR := $(SRC_DIR)cpp/
RELEASE_DIR := $(ROOT_DIR)release/

# Archivos fuente
SRC = $(CPP_DIR)main.cpp \
	$(CPP_DIR)get_device_by_index.cpp \
	$(CPP_DIR)list_devices.cpp \
	$(CPP_DIR)open_device.cpp \
	$(CPP_DIR)select_device.cpp \
	$(CPP_DIR)start_capture.cpp

# Objetos
OBJ = $(SRC:.cpp=.o)

# Includes
INCLUDES = -I"C:/npcap-sdk-1.16/Include"

# Librerías
LIBDIR = -L"C:/npcap-sdk-1.16/Lib/x64"
LIBS = -lwpcap -lPacket -lws2_32

# Flags
CPPFLAGS = -Wall -O2 $(INCLUDES)

# Regla principal
$(TARGET): $(OBJ)
	$(CPP) -o $@ $^ $(LIBDIR) $(LIBS)

# Compilación
%(CPP_DIR).o: %(CPP_DIR).cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

# Limpieza
clean:
	del /f source\cpp\*.o

# Limpieza incluyendo el ejecutable
cleanPlus:
	del /f source\cpp\*.o  release\$(ONLY_TARGET)