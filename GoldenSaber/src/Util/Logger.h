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
// File Name: Logger
// Date File Created: 12/07/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Types.h"
#include <format>

namespace saber::logger
{

enum class level : u8
{
    trace,
    debug,
    info,
    warn,
    error,
};

namespace detail
{
void output(level lvl, std::string_view msg);
} // namespace detail

} // namespace saber::logger

#ifdef _DEBUG
    #define LOG_TRACE(msg, ...) saber::logger::detail::output(saber::logger::level::trace, std::format(msg, ##__VA_ARGS__))
    #define LOG_DEBUG(msg, ...) saber::logger::detail::output(saber::logger::level::debug, std::format(msg, ##__VA_ARGS__))
    #define LOG_INFO(msg, ...)  saber::logger::detail::output(saber::logger::level::info, std::format(msg, ##__VA_ARGS__))
    #define LOG_WARN(msg, ...)  saber::logger::detail::output(saber::logger::level::warn, std::format(msg, ##__VA_ARGS__))
    #define LOG_ERROR(msg, ...) saber::logger::detail::output(saber::logger::level::error, std::format(msg, ##__VA_ARGS__))
#else
    #define LOG_TRACE(msg, ...)
    #define LOG_DEBUG(msg, ...)
    #define LOG_INFO(msg, ...)
    #define LOG_WARN(msg, ...)
    #define LOG_ERROR(msg, ...)
#endif
