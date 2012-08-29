@ECHO OFF

REM I don't know how portible this is, but it was written on Windows 7

REM This batch file builds the library directory from *.h and *.cpp, which is a convenience, not a necessity
REM Simply call this script; the Visual Studio solution calls this after the library is built

REM parameter list:
REM %0 $(SolutionDir)dir-build

ECHO Copying scripts
XCOPY "%~p0Sketch\*.lua" "%~p0Release\" /D /S /Y /I
