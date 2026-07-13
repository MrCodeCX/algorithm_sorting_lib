#pragma once

#include <iostream>
#include <list>
#include <vector>

namespace algorithm_sorting::utils {

template<typename T>
void print(const std::vector<T>& values, std::ostream& output = std::cout) {
	for (const T& value : values) {
		output << value << " ";
	}
	output << '\n';
}

template<typename T>
void print(const std::list<T>& values, std::ostream& output = std::cout) {
	for (const T& value : values) {
		output << value << " ";
	}
	output << '\n';
}

} // namespace algorithm_sorting::utils
