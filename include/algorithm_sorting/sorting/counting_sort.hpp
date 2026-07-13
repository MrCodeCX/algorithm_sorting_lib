#pragma once

#include "algorithm_sorting/detail/sorting.hpp"

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

namespace algorithm_sorting {

template<typename Int, detail::EnableIntegral<Int> = 0>
std::vector<Int> counting_sort(const std::vector<Int>& values, Int min_value, Int max_value) {
	if (values.empty()) {
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
		result[--counts[index]] = value;
	}

	return result;
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
std::vector<Int> counting_sort_with_max(const std::vector<Int>& values, Int max_value) {
	return counting_sort(values, Int{}, max_value);
}

template<typename Key, typename T, detail::EnableIntegral<Key> = 0>
std::vector<std::pair<Key, T>> counting_sort_by_key(const std::vector<std::pair<Key, T>>& values, Key min_key, Key max_key) {
	if (values.empty()) {
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
		result[--counts[index]] = value;
	}

	return result;
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

} // namespace algorithm_sorting
