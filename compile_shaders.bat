@echo off
cd /d "%~dp0"

set GLSL_FOLDER=GoldenSaber\assets\shaders
set GLSL_VALIDATOR=glslangValidator

echo Compiling shaders...

for %%f in (%GLSL_FOLDER%\*.frag %GLSL_FOLDER%\*.vert) do (
    echo Compiling %%f...
    %GLSL_VALIDATOR% -V %%f -o %%f.spv --target-env opengl
    echo.
)

echo Shaders compilation completed.