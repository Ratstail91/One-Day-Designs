@ECHO OFF
PATH=%PATH%;c:/mingw/bin
call g++ "palindrome.cpp"
SET /A loops = 10

copy palindrome.cpp 2.cpp

:lm
set /a loops = %loops% - 1
copy 2.cpp 1.cpp
a 1.cpp 2.cpp
del 1.cpp

if %loops% GTR 0 (

echo %loops%
goto lm
)

g++ "2.cpp"

pause