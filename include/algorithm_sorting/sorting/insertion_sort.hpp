#pragma once

#include "algorithm_sorting/tracing/sort_trace.hpp"

#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace algorithm_sorting {

namespace detail {

template<bool TraceEnabled, typename T, typename Compare>
void insertion_sort_impl(std::vector<T>& values, Compare compare, sort_trace<T>* trace) {
	for (std::size_t i = 1; i < values.size(); ++i) {
		std::size_t current = i;
		while (current > 0) {
			if constexpr (TraceEnabled) {
				trace->on_compare(current, current - 1);
			}

			if (!compare(values[current], values[current - 1])) {
				break;
			}

			std::swap(values[current], values[current - 1]);
			if constexpr (TraceEnabled) {
				trace->on_swap(current, current - 1);
			}
			--current;
		}
	}

	if constexpr (TraceEnabled) {
		trace->on_done();
	}
}

} // namespace detail

template<typename T, typename Compare = std::less<T>>
std::vector<T> insertion_sort(const std::vector<T>& values, Compare compare = Compare{}) {
	std::vector<T> result = values;
	detail::insertion_sort_impl<false>(result, compare, static_cast<sort_trace<T>*>(nullptr));
	return result;
}

template<typename T, typename Compare = std::less<T>>
std::vector<T> insertion_sort(const std::vector<T>& values, sort_trace<T>& trace, Compare compare = Compare{}) {
	std::vector<T> result = values;
	detail::insertion_sort_impl<true>(result, compare, &trace);
	return result;
}

} // namespace algorithm_sorting
