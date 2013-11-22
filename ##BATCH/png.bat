
color 70
cls



@set root=c:%~p1..\..\


@SET /P file=Please enter a name for this level: 

cls

:freelevelfound
IF EXIST %root%##\levels\%file% goto levelexists

@echo CHECK IF TEMP FOLDER EXISTS:
PAUSE
@IF EXIST %root%##LEVELS\temp goto tempfolderexists

@echo Tempfolder doesn't exist!
echo.

@echo CREATE TEMP FOLDER:
PAUSE
md %root%##LEVELS\temp
echo. 

@echo COPY TILESET TO TEMP FOLDER:
PAUSE
copy %1 %root%##LEVELS\temp\%file%.png
echo. 

@echo SET 2.TXT: 	
PAUSE
echo ^<image source="%file%.png" width="256" height="256"/^>  > %root%##BATCH\data\2.txt
echo. 

@echo CREATE TMX-FILE:
PAUSE
copy %root%##BATCH\data\1.txt+%root%\##BATCH\data\2.txt+%root%\##BATCH\data\3.txt %root%\##LEVELS\temp\%file%.tmx
echo.

echo CONVERT TILESET TO BINARY USING GRIT:
PAUSE
C:
cd %root%\##LEVELS\temp

grit %root%##LEVELS\temp\%file%.png -g -gt -gB8 -gz! -m -mLf -mR! -mz0  -p -ftb 
echo.

@echo DELETE MAP FILE:
PAUSE
del %root%##LEVELS\temp\%file%.map.bin
echo. 

@echo RENAME PAL AND IMG FILES:
PAUSE
ren %file%.img.bin %file%_tiles.bin
ren %file%.pal.bin %file%_pal.bin 
echo.

@echo OPEN TMX FILE IN TILED:
PAUSE
"c:\Program Files (x86)\Tiled\tiled.exe" %root%##LEVELS\temp\%file%.tmx
echo.

@echo CONVERT TMX FILE TO BINARY:
PAUSE
tmx2bin %root%##LEVELS\temp\%file%
echo.


:checkdata

@IF EXIST %root%data\%file%*.* goto warning

@echo COPY ALL LEVEL FILES TO DATA DIRECTORY:
PAUSE
copy %root%##LEVELS\temp\*.bin %root%data
echo.

@echo RENAME TEMP DIRECTORY TO LEVEL DIRECTORY:
PAUSE
cd..

ren temp %file%
echo done
echo.


@echo EVERYTHING WENT FINE!!!!
echo.

cd..
cd data

@echo BACKUP LEVELS.H:
pause

SET tm=h%TIME:~-11,2%_m%TIME:~-8,2%_s%TIME:~-5,2%

@echo %tm%
pause

copy "%root%include\levels.h" "%root%include\backup\levels_h_backup_%tm%_%DATE%.h"
@
@echo WRITE LIST OF PROJECTS BINARIES TO 2.TXT:
pause
dir /B %file%*.* > %root%##BATCH\2.txt
echo.

@echo ADD LEVEL TO LEVELS.H:
pause
%root%##PC-Tools\bin\createhfile %root%##BATCH\2.txt %root%include\levels.h
echo.

@echo Press button to close.


pause
goto ende


:levelexists

cls 
@echo Level named %file% already exists.
echo.
@echo Choose a name that doesn't match one of this folders:
dir %root%##levels
echo.
SET /P file Enter the new name for your level: 
goto freelevelfound


:tempfolderexists

cls
@echo ERROR!
@echo TEMP FOLDER EXISTS! Check, remove and start again!
echo.
@echo Press Key to open temp folder in explorer.
pause
start explorer %root%##LEVELS\temp
goto ende


:warning

cls
@echo WARNING!!!	
@echo files with %file%-prefix found in data folder!
echo Temp folder not deleted!
pause
goto ende

goto checkdata

pause
goto ende

:folderexists
@echo Folder %file% exists in levels directory!
@echo Temp folder not deleted!
pause
goto ende	


:ende
