#pragma once

#include "algorithm_sorting/tracing/sort_trace.hpp"

#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace algorithm_sorting {

namespace detail {

template<bool TraceEnabled, typename T, typename Compare>
void bubble_sort_impl(std::vector<T>& values, Compare compare, sort_trace<T>* trace) {
	if (values.size() < 2) {
		if constexpr (TraceEnabled) {
			trace->on_done();
		}
		return;
	}

	for (std::size_t unsorted = values.size(); unsorted > 1; --unsorted) {
		bool swapped = false;
		for (std::size_t i = 0; i + 1 < unsorted; ++i) {
			if constexpr (TraceEnabled) {
				trace->on_compare(i, i + 1);
			}

			if (compare(values[i + 1], values[i])) {
				std::swap(values[i], values[i + 1]);
				swapped = true;
				if constexpr (TraceEnabled) {
					trace->on_swap(i, i + 1);
				}
			}
		}

		if (!swapped) {
			break;
		}
	}

	if constexpr (TraceEnabled) {
		trace->on_done();
	}
}

} // namespace detail

template<typename T, typename Compare = std::less<T>>
std::vector<T> bubble_sort(const std::vector<T>& values, Compare compare = Compare{}) {
	std::vector<T> result = values;
	detail::bubble_sort_impl<false>(result, compare, static_cast<sort_trace<T>*>(nullptr));
	return result;
}

template<typename T, typename Compare = std::less<T>>
std::vector<T> bubble_sort(const std::vector<T>& values, sort_trace<T>& trace, Compare compare = Compare{}) {
	std::vector<T> result = values;
	detail::bubble_sort_impl<true>(result, compare, &trace);
	return result;
}

} // namespace algorithm_sorting
