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

if not exist %OUT_SCRIPTS_DIR% (
	echo mkdir %OUT_SCRIPTS_DIR%
	mkdir %OUT_SCRIPTS_DIR%
)

if %ACTION% == build (
	for %%f in (%SCRIPTS_DIR%\*.lua) do (
		echo %LUAC% -o %OUT_SCRIPTS_DIR%\%%~nf %SCRIPTS_DIR%\%%~nf.lua
		%LUAC% -o %OUT_SCRIPTS_DIR%\%%~nf %SCRIPTS_DIR%\%%~nf.lua
	)
)

if %ACTION% == clean (
	echo del /f /q %OUT_SCRIPTS_DIR%\*.*
	del /f /q %OUT_SCRIPTS_DIR%\*.*
)

exit /b 0