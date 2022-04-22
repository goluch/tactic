#pragma once

template <typename T>
T maximum(T a, T b)
{
    return a > b ? a : b;
}

template <typename T>
T minimum(T a, T b)
{
    return a < b ? a : b;
}