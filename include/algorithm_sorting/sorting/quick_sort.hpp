#pragma once

#include <functional>
#include <list>

namespace algorithm_sorting {

template<typename T, typename Compare = std::less<T>>
std::list<T> quick_sort_copy(const std::list<T>& values, Compare compare = Compare{}) {
	if (values.size() < 2) {
		return values;
	}

	const T pivot = values.back();
	std::list<T> lower;
	std::list<T> equal;
	std::list<T> higher;

	for (const T& value : values) {
		if (compare(value, pivot)) {
			lower.push_back(value);
		}
		else if (compare(pivot, value)) {
			higher.push_back(value);
		}
		else {
			equal.push_back(value);
		}
	}

	lower = quick_sort_copy(lower, compare);
	higher = quick_sort_copy(higher, compare);
	lower.splice(lower.end(), equal);
	lower.splice(lower.end(), higher);
	return lower;
}

template<typename T, typename Compare = std::less<T>>
void quick_sort(std::list<T>& values, Compare compare = Compare{}) {
	values = quick_sort_copy(values, compare);
}

} // namespace algorithm_sorting
