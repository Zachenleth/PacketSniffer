@echo off
setlocal enabledelayedexpansion
echo ========= COMPILANDO PROYECTO =========

set ROOT=%~dp0..
set CPP=%ROOT%\source\cpp\
set C=%ROOT%\source\c\
set INCLUDE=%ROOT%\external\npcap-sdk\Include\
set LIB=%ROOT%\external\npcap-sdk\Lib\x64\
set OUTPUT=%ROOT%\release\PacketSniffer.exe

echo ============ PROBANDO G++ =============
g++.exe --version

::junta todos los c
::set "CSRC="
::for %%F in (%C%\*.c) do (
    ::set "CSRC=!CSRC! %%F"
::)

::junta todos los cpp
set "CPPSOURCE="
for %%F in (%CPP%\*.cpp) do (
    set "CPPSOURCE=!CPPSOURCE! %%F"
)

::g++.exe -I%INCLUDE% -L%LIB% %CPPSOURCE% -lwpcap -o %OUTPUT%
g++.exe -I%INCLUDE% -L%LIB% %CPPSOURCE% -lwpcap -lPacket -o %OUTPUT% -std=c++17 -Wall
::%BIN%\g++.exe -I%INCLUDE% -L%LIB% %CPPSOURCE% -lwpcap -lPacket -o %OUTPUT% -std=c++17 -Wall


if %errorlevel% neq 0 (
    echo ========= ERROR DE COMPILACION ========
    exit /b %errorlevel%
    pause
)

echo ========== TERMINANDO BUILD ===========
pause
endlocal