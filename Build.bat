

::Set drive letter if no args given
::if [%1] == [] goto noArgs
::goto yesArgs

del RadixSortDriver.o

:noArgs
set DRIVE_LETTER=%CD:~0,2%
goto continue

:yesArgs
set DRIVE_LETTER=%1:
:continue
set PATH=%DRIVE_LETTER%\TDM-GCC-64\bin;c:\windows\system32;c:\"Program Files"\KDiff3
set PROJECT_PATH=.

mingw32-make DRIVE_LETTER="%DRIVE_LETTER%" CURRENT_DIR="%PROJECT_PATH%"
