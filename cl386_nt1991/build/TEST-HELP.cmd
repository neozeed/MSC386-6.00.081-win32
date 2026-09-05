@echo off
rem Keep CL386COMPAT.DLL, CL386.ERR and CL386.MSG beside CL386-WIN32.EXE.
CL386-WIN32.EXE -help
echo.
echo CL386 exit code: %ERRORLEVEL%
