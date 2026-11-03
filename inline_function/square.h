#pragma once
#include <cstdint>

// Defined in the header: the compiler can see the body and inline it
inline std::uint32_t inlineSquare(std::uint32_t x)
{
    return x * x;
}

// Only declared here: the body lives in square.cpp
std::uint32_t normalSquare(std::uint32_t x);