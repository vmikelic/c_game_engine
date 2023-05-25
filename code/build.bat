@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
set path=c:\Work\misc;c:\Work\code;%path%
cd C:\Work
cls

del C:\Work\build\*.pdb

set CommonCompilerFlags=-WL -Od -nologo /fp:except- -fp:fast -Gm- -GR- -EHa- -Zo -Oi -WX -W4 -wd4100 -wd4102 -wd4127 -wd4189 -wd4201 -wd4505 -wd4530 -FC -Z7

IF NOT EXIST C:\Work\build mkdir C:\Work\build
pushd C:\Work\build

cl %CommonCompilerFlags% -D_CRT_SECURE_NO_WARNINGS -DGPUDEBUG=0 C:\Work\code\win32_Game.cpp /link -incremental:no -opt:ref -PDB:win32_Game_%random%.pdb User32.lib Gdi32.lib opengl32.lib

popd
