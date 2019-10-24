@echo off

call "%VS140COMNTOOLS%\vsvars32.bat"

mkdir build
mkdir build\VisualStudio2015

cd build\VisualStudio2015
cmake -G"Visual Studio 14" ..\..

cd ..\..

@echo Done.
timeout /t 15
