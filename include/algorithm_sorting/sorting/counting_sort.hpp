#pragma once

#include "algorithm_sorting/detail/sorting.hpp"
#include "algorithm_sorting/tracing/sort_trace.hpp"

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

namespace algorithm_sorting {

namespace detail {

template<bool TraceEnabled, typename Int, typename Tracer>
std::vector<Int> counting_sort_impl(const std::vector<Int>& values, Int min_value, Int max_value, Tracer* tracer) {
	if (values.empty()) {
		if constexpr (TraceEnabled) {
			tracer->on_done();
		}
		return {};
	}

	const std::size_t range_size = detail::checked_range_size(min_value, max_value);
	std::vector<std::size_t> counts(range_size, 0);
	std::vector<Int> result(values.size());

	for (Int value : values) {
		++counts[detail::counting_index(value, min_value, range_size)];
	}

	for (std::size_t i = 1; i < counts.size(); ++i) {
		counts[i] += counts[i - 1];
	}

	for (std::size_t i = values.size(); i > 0; --i) {
		Int value = values[i - 1];
		std::size_t index = detail::counting_index(value, min_value, range_size);
		std::size_t output_index = --counts[index];
		result[output_index] = value;
		if constexpr (TraceEnabled) {
			tracer->on_write(output_index, value);
		}
	}

	if constexpr (TraceEnabled) {
		tracer->on_done();
	}

	return result;
}

} // namespace detail

template<typename Int, detail::EnableIntegral<Int> = 0>
std::vector<Int> counting_sort(const std::vector<Int>& values, Int min_value, Int max_value) {
	return detail::counting_sort_impl<false>(values, min_value, max_value, static_cast<sort_trace<Int>*>(nullptr));
}

template<typename Int, detail::EnableIntegral<Int> = 0>
std::vector<Int> counting_sort(const std::vector<Int>& values, Int min_value, Int max_value, sort_trace<Int>& trace) {
	return detail::counting_sort_impl<true>(values, min_value, max_value, &trace);
}

template<typename Int, detail::EnableIntegral<Int> = 0>
std::vector<Int> counting_sort(const std::vector<Int>& values) {
	if (values.empty()) {
		return {};
	}

	auto bounds = std::minmax_element(values.begin(), values.end());
	return counting_sort(values, *bounds.first, *bounds.second);
}

template<typename Int, detail::EnableIntegral<Int> = 0>
std::vector<Int> counting_sort(const std::vector<Int>& values, sort_trace<Int>& trace) {
	if (values.empty()) {
		trace.on_done();
		return {};
	}

	auto bounds = std::minmax_element(values.begin(), values.end());
	return counting_sort(values, *bounds.first, *bounds.second, trace);
}

template<typename Int, detail::EnableIntegral<Int> = 0>
std::vector<Int> counting_sort_with_max(const std::vector<Int>& values, Int max_value) {
	return counting_sort(values, Int{}, max_value);
}

template<typename Int, detail::EnableIntegral<Int> = 0>
std::vector<Int> counting_sort_with_max(const std::vector<Int>& values, Int max_value, sort_trace<Int>& trace) {
	return counting_sort(values, Int{}, max_value, trace);
}

namespace detail {

template<bool TraceEnabled, typename Key, typename T, typename Tracer>
std::vector<std::pair<Key, T>> counting_sort_by_key_impl(const std::vector<std::pair<Key, T>>& values, Key min_key, Key max_key, Tracer* trace) {
	if (values.empty()) {
		if constexpr (TraceEnabled) {
			trace->on_done();
		}
		return {};
	}

	const std::size_t range_size = detail::checked_range_size(min_key, max_key);
	std::vector<std::size_t> counts(range_size, 0);
	std::vector<std::pair<Key, T>> result(values.size());

	for (const auto& value : values) {
		++counts[detail::counting_index(value.first, min_key, range_size)];
	}

	for (std::size_t i = 1; i < counts.size(); ++i) {
		counts[i] += counts[i - 1];
	}

	for (std::size_t i = values.size(); i > 0; --i) {
		const auto& value = values[i - 1];
		std::size_t index = detail::counting_index(value.first, min_key, range_size);
		std::size_t output_index = --counts[index];
		result[output_index] = value;
		if constexpr (TraceEnabled) {
			trace->on_write(output_index, value);
		}
	}

	if constexpr (TraceEnabled) {
		trace->on_done();
	}

	return result;
}

} // namespace detail

template<typename Key, typename T, detail::EnableIntegral<Key> = 0>
std::vector<std::pair<Key, T>> counting_sort_by_key(const std::vector<std::pair<Key, T>>& values, Key min_key, Key max_key) {
	return detail::counting_sort_by_key_impl<false>(values, min_key, max_key, static_cast<sort_trace<std::pair<Key, T>>*>(nullptr));
}

template<typename Key, typename T, detail::EnableIntegral<Key> = 0>
std::vector<std::pair<Key, T>> counting_sort_by_key(const std::vector<std::pair<Key, T>>& values, Key min_key, Key max_key, sort_trace<std::pair<Key, T>>& trace) {
	return detail::counting_sort_by_key_impl<true>(values, min_key, max_key, &trace);
}

template<typename Key, typename T, detail::EnableIntegral<Key> = 0>
std::vector<std::pair<Key, T>> counting_sort_by_key(const std::vector<std::pair<Key, T>>& values) {
	if (values.empty()) {
		return {};
	}

	auto bounds = std::minmax_element(values.begin(), values.end(), [](const auto& left, const auto& right) {
		return left.first < right.first;
	});
	return counting_sort_by_key(values, bounds.first->first, bounds.second->first);
}

template<typename Key, typename T, detail::EnableIntegral<Key> = 0>
std::vector<std::pair<Key, T>> counting_sort_by_key(const std::vector<std::pair<Key, T>>& values, sort_trace<std::pair<Key, T>>& trace) {
	if (values.empty()) {
		trace.on_done();
		return {};
	}

	auto bounds = std::minmax_element(values.begin(), values.end(), [](const auto& left, const auto& right) {
		return left.first < right.first;
	});
	return counting_sort_by_key(values, bounds.first->first, bounds.second->first, trace);
}

} // namespace algorithm_sorting
