@ECHO off

::Obtain the CMakeLists.txt path
SET filepath=%~dp0
SET template=%filepath%CMakeLists.txt

:: FOR each folder 
FOR /D %%f in (*) do (
ECHO %filepath%%%f\
:: Copy/Replace the CMakeLists inside the current folder (silent mode)
xcopy /y %template% %filepath%%%f\
)

ECHO "Made by Santiago Alvarez - santiagoalvarez.me"
pause