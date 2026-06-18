mkdir Debug
cd Debug
cmake .. -DCMAKE_BUILD_TYPE=Debug -G "MinGW Makefiles"
cmake --build . --config Debug
ARKANOID.exe
pause