@echo off

rem Get the full path of the batch file
set "SCRIPT_DIR=%~dp0"
rem Set PLUGIN_DIR to the parent directory of the batch file
set "PLUGIN_DIR=%SCRIPT_DIR%"

rem Set paths for Build and Repo
set "CPP_DIR=%PLUGIN_DIR%\QR-Code-generator\cpp"
set "REPO_DIR=%PLUGIN_DIR%\QR-Code-generator"

rem Set paths for Source directories
set "SOURCE_DIR=%PLUGIN_DIR%\Source\UQRCode"

rem Clone the repository
git clone https://github.com/nayuki/QR-Code-generator.git

rem Copy header files from the root of the project
cd %CPP_DIR%
xcopy qrcodegen.hpp "%SOURCE_DIR%" /Y
xcopy qrcodegen.cpp "%SOURCE_DIR%" /Y

cd "%PLUGIN_DIR%"
rem Remove the temporary Git repository folder
rmdir /s /q QR-Code-generator

pause