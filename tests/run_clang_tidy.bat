@echo off
if not exist "..\build\build.ninja" (
    cmake -S .. -B ../build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
)
clang-tidy -p ../build --header-filter=.*nem/include.* dummy.cpp
pause