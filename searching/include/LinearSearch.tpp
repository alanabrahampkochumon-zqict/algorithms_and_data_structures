#pragma once
/**
 * @file LinearSearch.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Linear Search implementation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include "LinearSearch.h"


namespace algorithms
{
    template <typename T>
    std::optional<size_t> _linearSearch(const T* searchable, size_t size, const T& element)
    {
        for (std::size_t i = 0; i < size; i++)
        {
            if (element == searchable[i])
            {
                return i;
            }
        }

        return std::nullopt;
    }


    template <typename T, std::size_t Size>
    std::optional<size_t> algorithms::linearSearch(const T (&array)[Size], const T& element)
    {
        return _linearSearch(array, Size, element);
    }


    template <typename T>
    std::optional<size_t> algorithms::linearSearch(const std::vector<T>& vector, const T& element)
    {
        return _linearSearch(vector.data(), vector.size(), element);
    }
} // namespace algorithms
