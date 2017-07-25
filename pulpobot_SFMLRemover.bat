@ECHO off

:: FOR each folder here
FOR /D %%f in (*) do (
IF EXIST %%f\deps (
CD %%f\deps
ECHO %%f\deps
::Delete SFML files, to avoid a "The directory is not empty" error, first we delete all internal files recursively.
IF EXIST SFML-2.4.2 (
DEL /f /s /q SFML-2.4.2 1>nul
RMDIR /s /q SFML-2.4.2
)
)
::Return to the root, and loop
CD ..
CD ..
)

ECHO "Made by Santiago Alvarez - santiagoalvarez.me"
pause