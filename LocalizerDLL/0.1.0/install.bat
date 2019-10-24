@echo off

set PROJECT=LocalizerDLL
set VERSION=0.1.0

echo ############################################################
echo ### Installation script for targeting MEDITEC_LIBS       ###
echo ############################################################
echo.
echo Subject to installation: %PROJECT% %VERSION%
timeout /t 5

xcopy . "%MEDITEC_LIBS%\%PROJECT%\%VERSION%\" /f /y /e
xcopy bin\*.dll "%MEDITEC_LIBS%\bin\" /f /y
xcopy bin\*.pdb "%MEDITEC_LIBS%\bin\" /f /y
