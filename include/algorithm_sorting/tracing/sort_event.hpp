#pragma once

#include <cstddef>
#include <optional>

namespace algorithm_sorting {

enum class sort_event_type {
	compare,
	swap,
	write,
	done
};

template<typename T>
struct sort_event {
	sort_event_type type;
	std::size_t first;
	std::size_t second;
	std::optional<T> value;
};

} // namespace algorithm_sorting
