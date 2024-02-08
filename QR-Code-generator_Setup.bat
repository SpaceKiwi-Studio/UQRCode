@echo off

rem Get the full path of the batch file
set "SCRIPT_DIR=%~dp0"
rem Set PLUGIN_DIR to the parent directory of the batch file
set "PLUGIN_DIR=%SCRIPT_DIR%"

rem Set paths for Build and Repo
set "CPP_DIR=%PLUGIN_DIR%\QR-Code-generator\cpp"
set "REPO_DIR=%PLUGIN_DIR%\QR-Code-generator"

rem Set paths for ThirdParty directories
set "THIRD_PARTY_DIR=%PLUGIN_DIR%\Source\ThirdParty\QR-Code-generator"
set "THIRD_PARTY_INCLUDES_DIR=%THIRD_PARTY_DIR%\Includes"

rem Ensure ThirdParty directories exist
for %%D in ("%THIRD_PARTY_DIR%" "%THIRD_PARTY_INCLUDES_DIR%") do (
    if not exist "%%~D" mkdir "%%~D"
)

rem Clone the repository
git clone https://github.com/nayuki/QR-Code-generator.git
cd QR-Code-generator

rem Copy header files from the root of the project
cd %CPP_DIR%
xcopy *.hpp "%THIRD_PARTY_INCLUDES_DIR%" /Y

cd "%PLUGIN_DIR%"
rem Remove the temporary Git repository folder
rmdir /s /q QR-Code-generator

pause
