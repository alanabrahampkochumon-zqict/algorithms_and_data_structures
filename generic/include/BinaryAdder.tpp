#pragma once
/**
 * @file BinaryAdder.tpp
 * @author Alan Abraham P Kochumon
 * @date Created on: February 24, 2026
 *
 * @brief Binary Adder implementation.
 *
 * @copyright Copyright (c) 2026 Alan Abraham P Kochumon
 */


namespace algorithms
{

    template <std::size_t Size>
    std::optional<std::array<int, Size + 1>> binaryAdd(std::array<int, Size> first, std::array<int, Size> second)
    {
        std::array<int, Size + 1> res = {};
        int remainder = 0;
        for (int i = static_cast<int>(Size) - 1; i > -1; --i)
        {
            if (first[i] > 1 || first[i] < 0 || second[i] > 1 || second[i] < 0)
                return std::nullopt;

            res[i + 1] = first[i] ^ second[i] ^ remainder;
            remainder = (first[i] & second[i]) || (first[i] & remainder) || (second[i] & remainder);
        }
        res[0] = remainder;

        return res;
    }
} // namespace algorithms
