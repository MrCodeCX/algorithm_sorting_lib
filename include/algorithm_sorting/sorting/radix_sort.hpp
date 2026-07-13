#pragma once

#include "algorithm_sorting/detail/sorting.hpp"

#include <cstddef>
#include <type_traits>
#include <vector>

namespace algorithm_sorting {

template<typename Int, detail::EnableIntegral<Int> = 0>
std::vector<Int> radix_sort(const std::vector<Int>& values) {
	using Unsigned = typename std::make_unsigned<Int>::type;

	std::vector<Int> result = values;
	std::vector<Int> buffer(values.size());
	constexpr std::size_t bucket_count = 256;
	constexpr std::size_t passes = sizeof(Int);

	for (std::size_t pass = 0; pass < passes; ++pass) {
		std::vector<std::size_t> counts(bucket_count, 0);
		const std::size_t shift = pass * 8;

		for (Int value : result) {
			Unsigned key = detail::radix_key(value);
			++counts[(key >> shift) & 0xFFu];
		}

		for (std::size_t i = 1; i < counts.size(); ++i) {
			counts[i] += counts[i - 1];
		}

		for (std::size_t i = result.size(); i > 0; --i) {
			Int value = result[i - 1];
			Unsigned key = detail::radix_key(value);
			std::size_t bucket = (key >> shift) & 0xFFu;
			buffer[--counts[bucket]] = value;
		}

		result.swap(buffer);
	}

	return result;
}

} // namespace algorithm_sorting
