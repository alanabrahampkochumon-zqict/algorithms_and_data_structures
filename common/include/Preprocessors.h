#pragma once
/**
 * @file Preprocessors.h
 * @author Alan Abraham P Kochumon
 * @date Created on: April 16, 2026
 *
 * @brief Preprocessor definition for entire solution.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


/** 
 * @brief Declare an execution path as unreachable during program normal execution.
 *
 * @par Example UseCase:
 *      When a function returns an object depending on a condition but the doesn't run any in the default execution
 *      pathway. @see @ref datastructures::Matrix::multiply for a concrete example.
 */
#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)
    #define UNREACHABLE __builtin_unreachable()
#elif _MSC_VER
    #define UNREACHABLE __assume(0)
#else
    #define UNREACHABLE abort()
#endif