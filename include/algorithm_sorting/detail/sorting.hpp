#pragma once

#include <cstddef>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace algorithm_sorting::detail {

template<typename Int>
using EnableIntegral = typename std::enable_if<std::is_integral<Int>::value, int>::type;

template<typename Int>
std::size_t checked_range_size(Int min_value, Int max_value) {
	if (max_value < min_value) {
		throw std::invalid_argument("max_value must be greater than or equal to min_value");
	}

	using Wide = long long;
	const auto range = static_cast<Wide>(max_value) - static_cast<Wide>(min_value);
	if (range < 0 || static_cast<unsigned long long>(range) > static_cast<unsigned long long>(std::numeric_limits<std::size_t>::max() - 1)) {
		throw std::length_error("counting sort range is too large");
	}

	return static_cast<std::size_t>(range) + 1;
}

template<typename Int>
std::size_t counting_index(Int value, Int min_value, std::size_t range_size) {
	const auto index = static_cast<long long>(value) - static_cast<long long>(min_value);
	if (index < 0 || static_cast<std::size_t>(index) >= range_size) {
		throw std::out_of_range("value is outside the counting sort range");
	}
	return static_cast<std::size_t>(index);
}

template<typename Int>
typename std::make_unsigned<Int>::type radix_key(Int value) {
	using Unsigned = typename std::make_unsigned<Int>::type;
	Unsigned key = static_cast<Unsigned>(value);
	if (std::is_signed<Int>::value) {
		key ^= (Unsigned{1} << (sizeof(Int) * 8 - 1));
	}
	return key;
}

} // namespace algorithm_sorting::detail
