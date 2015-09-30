@echo off

set ACTION=%1
set BUILD_CONF=%2
set BUILD_ARCH=%3

if %ACTION% == rebuild (
	set ACTION=build
)

set BUILD_ARCH_ALT=%BUILD_ARCH%
if %BUILD_ARCH% == Win32 (
    set BUILD_ARCH_ALT=x86
)

set BUILD_DIR=..\Build\%BUILD_CONF%\%BUILD_ARCH%

set LUAC=%~dp0\Lua\%BUILD_ARCH_ALT%\luac.exe
set COPY=xcopy /s /e /y /i

set SCRIPTS_DIR=Scripts
set OUT_SCRIPTS_DIR=%BUILD_DIR%\Scripts

set TEXTURES_DIR=Textures
set OUT_TEXTURES_DIR=%BUILD_DIR%\Textures

set FONTS_DIR=Fonts
set OUT_FONTS_DIR=%BUILD_DIR%\Fonts

if not exist %OUT_SCRIPTS_DIR% (
	echo mkdir %OUT_SCRIPTS_DIR%
	mkdir %OUT_SCRIPTS_DIR% || exit /b 1
)

if not exist %OUT_TEXTURES_DIR% (
	echo mkdir %OUT_TEXTURES_DIR%
	mkdir %OUT_TEXTURES_DIR% || exit /b 1
)

if %ACTION% == build (
	if exist %SCRIPTS_DIR% (
		for /d %%f in (%SCRIPTS_DIR%\*) do (
			echo %LUAC% -o %OUT_SCRIPTS_DIR%\%%~nxf.luac %SCRIPTS_DIR%\%%~nxf\*.lua
			%LUAC% -o %OUT_SCRIPTS_DIR%\%%~nxf.luac %SCRIPTS_DIR%\%%~nxf\*.lua || exit /b 1
		)
		for %%f in (%SCRIPTS_DIR%\*.lua) do (
			echo %LUAC% -o %OUT_SCRIPTS_DIR%\%%~nf.luac %SCRIPTS_DIR%\%%~nf.lua
			%LUAC% -o %OUT_SCRIPTS_DIR%\%%~nf.luac %SCRIPTS_DIR%\%%~nf.lua || exit /b 1
		)
	)

	if exist %TEXTURES_DIR% (
		echo %COPY% %TEXTURES_DIR% %OUT_TEXTURES_DIR%
		%COPY% %TEXTURES_DIR% %OUT_TEXTURES_DIR% || exit /b 1
	)

	if exist %FONTS_DIR% (
		echo %COPY% %FONTS_DIR% %OUT_FONTS_DIR%
		%COPY% %FONTS_DIR% %OUT_FONTS_DIR% || exit /b 1
	)
)

if %ACTION% == clean (
	echo del /f /q %OUT_SCRIPTS_DIR%\*.*
	del /f /q %OUT_SCRIPTS_DIR%\*.* || exit /b 1

	echo del /f /q %OUT_TEXTURES_DIR%\*.*
	del /f /q %OUT_TEXTURES_DIR%\*.* || exit /b 1

	echo del /f /q %OUT_FONTS_DIR%\*.*
	del /f /q %OUT_FONTS_DIR%\*.* || exit /b 1
)

exit /b 0
