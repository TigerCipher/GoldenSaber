//  ------------------------------------------------------------------------------
//
//  GoldenSaber
//     Copyright 2023 Matthew Rogers
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
//
//  File Name: Logger.cpp
//  Date File Created: 12/07/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Logger.h"

#if defined(_WIN32)
    #define WIN32_LEAN_AND_MEAN
    #include <Windows.h>

    #define LOG_OUTPUT(msg)                                                                                                      \
        OutputDebugStringA(msg);                                                                                                 \
        printf("%s", msg)
#else
    #define LOG_OUTPUT(msg) printf("%s", msg)
#endif

namespace saber::logger::detail
{

void output(level lvl, std::string_view msg)
{
    std::string str{};
    switch (lvl)
    {
    case level::trace: str = std::format("[ TRACE ]: {}\n", msg); break;
    case level::debug: str = std::format("[ DEBUG ]: {}\n", msg); break;
    case level::info: str = std::format("[ INFO ]: {}\n", msg); break;
    case level::warn: str = std::format("[ WARNING ]: {}\n", msg); break;
    case level::error: str = std::format("[ ERROR ]: {}\n", msg); break;
    }

    LOG_OUTPUT(str.c_str());
}

} // namespace saber::logger::detail