#pragma once
/**
 * @file Concepts.h
 * @author Alan Abraham P Kochumon
 * @date Created on: March 14, 2026
 *
 * @brief Constraints (C++ concepts) for semantically categorizing templates.
 * 
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


#include <concepts>


/**
 * @addtogroup Concepts
 * @{
 */

/**
 * @brief A union of @ref `std::integral` and @ref `std::floating_point` concept.
 * @tparam T The type to constraint.
 */
template <typename T>
concept Arithmetic = std::integral<T> || std::floating_point<T>;

/** @} */