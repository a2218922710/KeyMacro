@echo off
rem 传入的第一个参数为lupdate所在目录，如已配置环境变量，双击运行即可
set LUPDATE_BIN=%1
if "%LUPDATE_BIN%" == "" set LUPDATE_BIN=lupdate.exe
set projectPath=%cd%\..
set ts_file=%projectPath%\languages\tr-zh_CN.ts
rem FILTER_LIST 需要过滤的文件夹
set FILTER_LIST = ""

%LUPDATE_BIN% -source-language zh_CN   -no-obsolete -extensions "cpp,h" ^
                -recursive %projectPath%\services\ %projectPath%\widgets\ ^
                -no-recursive %FILTER_LIST% ^
                -ts %ts_file%
