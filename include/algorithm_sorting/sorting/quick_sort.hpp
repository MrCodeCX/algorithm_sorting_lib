#pragma once

#include "algorithm_sorting/tracing/sort_trace.hpp"

#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

namespace algorithm_sorting {

namespace detail {

template<bool TraceEnabled, typename T, typename Compare>
std::size_t partition(std::vector<T>& values, std::size_t low, std::size_t high, Compare compare, sort_trace<T>* trace) {
	std::size_t pivot_index = high;
	std::size_t store_index = low;

	for (std::size_t i = low; i < high; ++i) {
		if constexpr (TraceEnabled) {
			trace->on_compare(i, pivot_index);
		}

		if (compare(values[i], values[pivot_index])) {
			if (i != store_index) {
				std::swap(values[i], values[store_index]);
				if constexpr (TraceEnabled) {
					trace->on_swap(i, store_index);
				}
			}
			++store_index;
		}
	}

	if (store_index != pivot_index) {
		std::swap(values[store_index], values[pivot_index]);
		if constexpr (TraceEnabled) {
			trace->on_swap(store_index, pivot_index);
		}
	}

	return store_index;
}

template<bool TraceEnabled, typename T, typename Compare>
void quick_sort_impl(std::vector<T>& values, std::size_t low, std::size_t high, Compare compare, sort_trace<T>* trace) {
	if (low >= high) {
		return;
	}

	std::size_t pivot = partition<TraceEnabled>(values, low, high, compare, trace);
	if (pivot > 0) {
		quick_sort_impl<TraceEnabled>(values, low, pivot - 1, compare, trace);
	}
	quick_sort_impl<TraceEnabled>(values, pivot + 1, high, compare, trace);
}

} // namespace detail

template<typename T, typename Compare = std::less<T>>
std::vector<T> quick_sort(const std::vector<T>& values, Compare compare = Compare{}) {
	std::vector<T> result = values;
	if (!result.empty()) {
		detail::quick_sort_impl<false>(result, 0, result.size() - 1, compare, static_cast<sort_trace<T>*>(nullptr));
	}
	return result;
}

template<typename T, typename Compare = std::less<T>>
std::vector<T> quick_sort(const std::vector<T>& values, sort_trace<T>& trace, Compare compare = Compare{}) {
	std::vector<T> result = values;
	if (!result.empty()) {
		detail::quick_sort_impl<true>(result, 0, result.size() - 1, compare, &trace);
	}
	trace.on_done();
	return result;
}

} // namespace algorithm_sorting
