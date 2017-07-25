@ECHO off

SET filepath=%~dp0
SET template=%filepath%_Template

:: FOR each folder here
FOR /D %%f in (*) do (
ECHO %filepath%%%f\
:: Copy the template to the folder
xcopy /s /e %template% %filepath%%%f\
:: MOVE to folder/Source/folderName/
IF EXIST %filepath%%%f\Source (
CD %filepath%%%f\Source\%%f
DEL *.filters 
DEL *.vcxproj
ls
FOR /r %%c in (*) do MOVE /y %%c %filepath%%%f\src
CD..
CD..
::Delete not required files
DEL *.exe
RMDIR Source /S /Q
)
)


ECHO "Made by Santiago Alvarez - santiagoalvarez.me"
pause