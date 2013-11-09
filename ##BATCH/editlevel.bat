
color 70


cls

@set root=c:%~p1..\..\

@set file=%~n1


echo OPEN TMX FILE IN TILED:
PAUSE
"c:\Program Files (x86)\Tiled\tiled.exe" %root%##LEVELS\%file%\%file%.tmx
echo .

echo DELETE OLD BIN FILES IN LEVEL FOLDER:
pause
del %root%##LEVELS\%file%\*.bin /Q

echo DELETE OLD BIN FILES IN DATA FOLDER:
pause
del %root%data\%file%*.* /Q
echo.

echo CONVERT TMX FILE TO BINARY:
PAUSE
tmx2bin %root%##LEVELS\%file%\%file%
echo .




echo COPY ALL LEVEL FILES TO DATA DIRECTORY:
PAUSE
copy %root%##LEVELS\%file%\*.bin %root%data
echo .



echo EVERYTHING WENT FINE!!!!

:ende
