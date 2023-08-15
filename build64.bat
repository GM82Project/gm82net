del build\src\release\gm82core.dll

cmake -B build -A Win32 -DNO_GEX=ON && cmake --build build --config Release
copy build\src\Release\gm82net.dll .
pause