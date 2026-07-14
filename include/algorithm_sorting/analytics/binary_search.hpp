#pragma once

#include <functional>
#include <optional>
#include <cstddef>
#include <vector>

namespace algorithm_sorting {

template<typename T, typename Compare = std::less<T>>
std::optional<std::size_t> binary_search_first(const std::vector<T>& values, const T& target, Compare compare = Compare{}) {
	if (values.empty()) {
		return std::nullopt;
	}

	std::size_t start = 0;
	std::size_t end = values.size();
	std::optional<std::size_t> result;

	while (start < end) {
		std::size_t middle = start + (end - start) / 2;
		if (compare(values[middle], target)) {
			start = middle + 1;
		}
		else if (compare(target, values[middle])) {
			end = middle;
		}
		else {
			result = middle;
			end = middle;
		}
	}

	return result;
}

} // namespace algorithm_sorting
