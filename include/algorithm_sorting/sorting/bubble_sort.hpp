#pragma once

#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace algorithm_sorting {

template<typename T, typename Compare = std::less<T>>
void bubble_sort(std::vector<T>& values, Compare compare = Compare{}) {
	if (values.size() < 2) {
		return;
	}

	for (std::size_t unsorted = values.size(); unsorted > 1; --unsorted) {
		bool swapped = false;
		for (std::size_t i = 0; i + 1 < unsorted; ++i) {
			if (compare(values[i + 1], values[i])) {
				std::swap(values[i], values[i + 1]);
				swapped = true;
			}
		}

		if (!swapped) {
			return;
		}
	}
}

} // namespace algorithm_sorting
