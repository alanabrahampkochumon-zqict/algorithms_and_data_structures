#pragma once
/**
 * @file Concepts.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 14, 2026
 *
 * @brief Concept definitions.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <concepts>


/**
 * @brief A union of `std::integral` and `std::floating_point` concept.
 * @tparam T template typename
 */
template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;
