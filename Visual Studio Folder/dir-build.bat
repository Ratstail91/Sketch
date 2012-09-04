@ECHO OFF

REM I don't know how portible this is, but it was written on Windows 7

REM This batch file builds the library directory from *.h and *.cpp, which is a convenience, not a necessity
REM Simply call this script; the Visual Studio solution calls this after the library is built

REM parameter list:
REM %0 $(SolutionDir)dir-build

ECHO Copying scripts

REM These are the specific files being copied to the correct directories


REM Documentation
XCOPY "%~p0Sketch\README.txt" "%~p0Release\" /D /Y


REM Scripts
XCOPY "%~p0Sketch\startup.lua" "%~p0Release\rsc\scripts\" /D /Y
XCOPY "%~p0Sketch\shutdown.lua" "%~p0Release\rsc\scripts\" /D /Y
XCOPY "%~p0Sketch\save_format.lua" "%~p0Release\rsc\scripts\" /D /Y


REM Brushes
XCOPY "%~p0Sketch\brush.lua" "%~p0Release\rsc\brushes\" /D /Y


REM Filters
XCOPY "%~p0Sketch\filter.lua" "%~p0Release\rsc\filters\" /D /Y

