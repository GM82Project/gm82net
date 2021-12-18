@echo off

where /q msbuild
if errorlevel 1 (
	echo You need to run this from a MSVC command prompt.
	exit /b
)

mkdir build
cd build

set GM82NETPLAT=Win32
for /f %%v in ('msbuild -nologo -version') do set MSVCVER=%v
if "%MSVCVER%" == "15" (set GM82NETPLAT=x86)
if "%MSVCVER%" == "14" (set GM82NETPLAT=x86)
if "%MSVCVER%" == "13" (set GM82NETPLAT=x86)
if "%MSVCVER%" == "12" (set GM82NETPLAT=x86)
if "%MSVCVER%" == "11" (set GM82NETPLAT=x86)
if "%MSVCVER%" == "10" (set GM82NETPLAT=x86)

cmake ../ -A %GM82NETPLAT%
if errorlevel 1 (
	cd ..
	exit /b
)

msbuild gm82net.sln /p:Platform=%GM82NETPLAT% /p:Configuration=Release
cd ..

