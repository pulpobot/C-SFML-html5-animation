@ECHO off

SET filepath=%~dp0
SET buildsfolder=%filepath%_builds

:: FOR each folder here
FOR /D %%f in (*) do (
ECHO %%f\build
CD %%f
IF EXIST build (
CD build
xcopy /y /e	".\*" %buildsfolder%

::Delete Build files, to avoid a "The directory is not empty" error, first we delete all internal files recursively.
CD ..
DEL /f /s /q build 1>nul
RMDIR /s /q build
)

CD ..
)
::Return to the root, and loop

ECHO "Made by Santiago Alvarez - santiagoalvarez.me"
pause