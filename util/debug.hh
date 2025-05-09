#pragma once

#include <fmt/core.h>
#include <string_view>

void debug_str( std::string_view message );

template<typename... Args>
void debug( fmt::format_string<Args...> fmt, Args&&... args )
{
#ifndef NDEBUG
  debug_str( fmt::format( fmt, std::forward<Args>( args )... ) );
#endif
}

void set_debug_handler( void ( * )( void*, std::string_view ), void* arg );
void reset_debug_handler();