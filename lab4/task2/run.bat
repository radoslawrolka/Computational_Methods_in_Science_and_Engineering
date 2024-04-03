@echo off

REM Loop through arguments 1 to 7
for %%i in (1 2 3 4 5 6 7) do (
    start "" /B ".\build\bin\Release\BITMAP_Annealing.exe" %%i
)
