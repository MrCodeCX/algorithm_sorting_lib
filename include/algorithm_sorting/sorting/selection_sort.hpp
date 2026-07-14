#pragma once

#include "algorithm_sorting/tracing/sort_trace.hpp"

#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace algorithm_sorting {

namespace detail {

template<bool TraceEnabled, typename T, typename Compare>
void selection_sort_impl(std::vector<T>& values, Compare compare, sort_trace<T>* trace) {
	for (std::size_t i = 0; i < values.size(); ++i) {
		std::size_t selected = i;
		for (std::size_t j = i + 1; j < values.size(); ++j) {
			if constexpr (TraceEnabled) {
				trace->on_compare(j, selected);
			}

			if (compare(values[j], values[selected])) {
				selected = j;
			}
		}

		if (selected != i) {
			std::swap(values[i], values[selected]);
			if constexpr (TraceEnabled) {
				trace->on_swap(i, selected);
			}
		}
	}

	if constexpr (TraceEnabled) {
		trace->on_done();
	}
}

} // namespace detail

template<typename T, typename Compare = std::less<T>>
std::vector<T> selection_sort(const std::vector<T>& values, Compare compare = Compare{}) {
	std::vector<T> result = values;
	detail::selection_sort_impl<false>(result, compare, static_cast<sort_trace<T>*>(nullptr));
	return result;
}

template<typename T, typename Compare = std::less<T>>
std::vector<T> selection_sort(const std::vector<T>& values, sort_trace<T>& trace, Compare compare = Compare{}) {
	std::vector<T> result = values;
	detail::selection_sort_impl<true>(result, compare, &trace);
	return result;
}

} // namespace algorithm_sorting
