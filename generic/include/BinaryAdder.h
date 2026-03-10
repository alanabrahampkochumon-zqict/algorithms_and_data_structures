#pragma once
/**
 * @file BinaryAdder.h
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Algorithm for adding two binary numbers.
 * @note Only supports std::array currently.
 *
 * @par Usage
 * To add binary number 11011 + 10111, pass them as {1, 1, 0, 1, 1}, {1, 0, 1, 1, 1}
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <array>
#include <cstddef>


namespace algorithms
{


    /**
     * Adds two binary numbers that are represented as arrays.
     * @tparam Size Size of the array
     * @param first one of the binary array
     * @param second the other binary array
     * @return the resultant array of size + 1
     */
    template <std::size_t Size>
    std::optional<std::array<int, Size + 1>> binaryAdd(std::array<int, Size> first, std::array<int, Size> second);

} // namespace algorithms

#include "BinaryAdder.tpp"