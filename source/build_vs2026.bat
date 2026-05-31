mkdir VS2026_solution
cd VS2026_solution
cmake .. -G "Visual Studio 18 2026" -A x64
cmake --build . --config Release
cmake --build . --config Debug
pause