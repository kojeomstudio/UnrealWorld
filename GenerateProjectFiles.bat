@echo off

setlocal

set GEN_PATH=.\UECustom\GenerateProjectFiles.bat

call %GEN_PATH% %~dp0UnrealWorld.uproject -Game -Engine

endlocal