#pragma once

#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace algorithm_sorting {

template<typename T, typename Compare = std::less<T>>
void selection_sort(std::vector<T>& values, Compare compare = Compare{}) {
	for (std::size_t i = 0; i < values.size(); ++i) {
		std::size_t selected = i;
		for (std::size_t j = i + 1; j < values.size(); ++j) {
			if (compare(values[j], values[selected])) {
				selected = j;
			}
		}

		if (selected != i) {
			std::swap(values[i], values[selected]);
		}
	}
}

} // namespace algorithm_sorting
