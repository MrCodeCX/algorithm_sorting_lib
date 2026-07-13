#pragma once

#include <functional>
#include <list>

namespace algorithm_sorting {

template<typename T, typename Compare = std::less<T>>
std::list<T> insertion_sort(const std::list<T>& values, Compare compare = Compare{}) {
	std::list<T> result;

	for (const T& value : values) {
		auto position = result.begin();
		while (position != result.end() && !compare(value, *position)) {
			++position;
		}
		result.insert(position, value);
	}

	return result;
}

} // namespace algorithm_sorting
