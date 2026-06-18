mkdir VS2022_solution
cd VS2022_solution
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
cmake --build . --config Debug
pause