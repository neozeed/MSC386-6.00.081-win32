@echo off
echo C3 long-double /Fa test
cl386 /c /Faastro.asm astro.c
echo ERRORLEVEL=%ERRORLEVEL%
if exist astro.asm dir astro.asm
