@echo off

RMDIR dist /S /Q

cmake -S . --preset=ALL --check-stamp-file "build\CMakeFiles\generate.stamp"
if %ERRORLEVEL% NEQ 0 exit 1
cmake --build build --config Debug
if %ERRORLEVEL% NEQ 0 exit 1

xcopy "build\debug\*.dll" "dist\SKSE\Plugins\" /I /Y
xcopy "build\debug\*.pdb" "dist\SKSE\Plugins\" /I /Y

xcopy "package" "dist" /I /Y /E

pause