@echo off

set ACTION=%1
set BUILD_CONF=%2
set BUILD_ARCH=%3
set SCRIPTS_DIR=%4

if %ACTION% == rebuild (
	set ACTION=build
)

set BUILD_ARCH_ALT=%BUILD_ARCH%
if %BUILD_ARCH% == Win32 (
    set BUILD_ARCH_ALT=x86
)

set LUAC=..\Tools\Lua\%BUILD_ARCH_ALT%\luac.exe
set OUT_SCRIPTS_DIR=..\Build\%BUILD_CONF%\%BUILD_ARCH%\Scripts
set OUT_SCRIPT=%OUT_SCRIPTS_DIR%\Dusk

if not exist %OUT_SCRIPTS_DIR% (
	echo mkdir %OUT_SCRIPTS_DIR%
	mkdir %OUT_SCRIPTS_DIR%
)

if %ACTION% == build (
	echo %LUAC% -o %OUT_SCRIPT% %SCRIPTS_DIR%\*.lua
)

if %ACTION% == clean (
	echo del /f /q %OUT_SCRIPT%
	del /f /q %OUT_SCRIPT%
)

exit /b 0