del build\src\release\gm82net.dll

cmake -B build -T v141_xp -A Win32 -DINSTALL_GEX=ON && cmake --build build --config Release

pause