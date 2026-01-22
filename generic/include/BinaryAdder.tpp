
namespace Algorithms::Generic
{
	/**
	 * Adds two binary numbers that are represented as arrays.
	 * @tparam Size Size of the array
	 * @param first one of the binary array
	 * @param second the other binary array
	 * @return the resultant array of size + 1
	 */
	template<std::size_t Size>
	std::optional<std::array<int, Size + 1>> binaryAdd(std::array<int, Size> first, std::array<int, Size> second)
	{
		std::array<int, Size + 1> res = {};
		int remainder = 0;
		for (int i = static_cast<int>(Size) - 1; i > -1; --i)
		{
			if (first[i] > 1 || first[i] < 0 || second[i] > 1 || second[i] < 0) return std::nullopt;

			res[i + 1] = first[i] ^ second[i] ^ remainder;
			remainder = (first[i] & second[i]) || (first[i] & remainder) || (second[i] & remainder);
		}
		res[0] = remainder;

		return res;
	}
}
