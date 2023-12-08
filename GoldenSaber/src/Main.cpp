// ------------------------------------------------------------------------------
//
// GoldenSaber
//    Copyright 2023 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: Main
// Date File Created: 12/07/2023
// Author: Matt
//
// ------------------------------------------------------------------------------


#include "Game.h"
#include "Window.h"


using namespace saber;

#if (defined(_DEBUG) && defined(_WIN32)) || (!defined(_DEBUG) && !defined(_WIN32))

int main(int argc, char* argv[])
{
    window::create(1920, 1080, "GoldenSaber", false);

    game::run();

    window::shutdown();

    return 0;
}


#else

    #ifdef _WIN32

        #define WIN32_LEAN_AND_MEAN
        #include <Windows.h>

// Windows entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    window::create(1280, 720, "GoldenSaber", false);

    game::run();

    window::shutdown();

    return 0;
}
    #else
        #error                                                                                                                   \
            "This error should not be reached. If it is reached, then the project is in release build and trying to use the Windows entry point but is not a Windows operating system"
    #endif


#endif
