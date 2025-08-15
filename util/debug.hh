#pragma once

// #include <fmt/core.h>
// #include <string_view>

// void debug_str( std::string_view message );

// template<typename... Args>
// void debug( fmt::v8::format_string<Args...> fmt [[maybe_unused]], Args&&... args [[maybe_unused]] )
// {
// #ifndef NDEBUG
//   debug_str( fmt::format( fmt, std::forward<Args>( args )... ) );
// #endif
// }

// void set_debug_handler( void ( * )( void*, std::string_view ), void* arg );
// void reset_debug_handler();
#include <sstream>
#include <string_view>

void debug_str(std::string_view message);

// 这是一个重载的 << 运算符，用于处理多个参数
template <typename T>
void append_to_stream(std::stringstream& ss, const T& arg) {
    ss << arg;
}

// 这是一个重载的 << 运算符，用于递归地处理参数包
template <typename T, typename... Args>
void append_to_stream(std::stringstream& ss, const T& arg, const Args&... args) {
    ss << arg;
    append_to_stream(ss, args...);
}

// debug 函数现在接受可变参数，并使用 stringstream 进行拼接
template <typename... Args>
void debug(const Args&... args) {
#ifndef NDEBUG
    std::stringstream ss;
    append_to_stream(ss, args...);
    debug_str(ss.str());
#endif
}

void set_debug_handler(void (*)(void*, std::string_view), void* arg);
void reset_debug_handler();