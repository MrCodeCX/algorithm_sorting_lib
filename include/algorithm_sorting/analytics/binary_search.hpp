#pragma once

#include <functional>
#include <vector>

namespace algorithm_sorting {

template<typename T, typename Compare = std::less<T>>
int binary_search_first(const std::vector<T>& values, const T& target, Compare compare = Compare{}) {
	if (values.empty()) {
		return -1;
	}

	int start = 0;
	int end = static_cast<int>(values.size()) - 1;
	int result = -1;

	while (start <= end) {
		int middle = start + (end - start) / 2;
		if (compare(values[middle], target)) {
			start = middle + 1;
		}
		else if (compare(target, values[middle])) {
			end = middle - 1;
		}
		else {
			result = middle;
			end = middle - 1;
		}
	}

	return result;
}

} // namespace algorithm_sorting
