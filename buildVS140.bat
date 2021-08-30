@echo off

rem Sorry, since the project is targeting VS140, it's Visual Studio 2015 only :(

call "%VS140COMNTOOLS%vsvars32.bat"

MSBuild vs\vs.sln /t:Rebuild /p:Configuration=Release /p:Platform=x86


