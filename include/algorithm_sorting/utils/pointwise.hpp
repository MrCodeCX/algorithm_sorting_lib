#pragma once

#include <cmath>
#include <cstddef>
#include <vector>

namespace algorithm_sorting::utils {

template<typename T>
void prefix_sum(std::vector<T>& values) {
	for (std::size_t i = 1; i < values.size(); ++i) {
		values[i] += values[i - 1];
	}
}

template<typename T>
void add_scalar(std::vector<T>& values, T scalar) {
	for (T& value : values) {
		value += scalar;
	}
}

template<typename T>
void multiply_scalar(std::vector<T>& values, T scalar) {
	for (T& value : values) {
		value *= scalar;
	}
}

template<typename Integer>
Integer digit_at(Integer value, int power_of_ten) {
	Integer divisor = static_cast<Integer>(std::pow(10, power_of_ten));
	return (value / divisor) % 10;
}

} // namespace algorithm_sorting::utils
