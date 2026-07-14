#pragma once

#include "algorithm_sorting/tracing/sort_event.hpp"

#include <cstddef>
#include <vector>

namespace algorithm_sorting {

template<typename T>
class sort_trace {
public:
	void on_compare(std::size_t first, std::size_t second) {
		events_.push_back({ sort_event_type::compare, first, second, std::nullopt });
	}

	void on_swap(std::size_t first, std::size_t second) {
		events_.push_back({ sort_event_type::swap, first, second, std::nullopt });
	}

	void on_write(std::size_t index, const T& value) {
		events_.push_back({ sort_event_type::write, index, npos, value });
	}

	void on_done() {
		events_.push_back({ sort_event_type::done, npos, npos, std::nullopt });
	}

	const std::vector<sort_event<T>>& events() const {
		return events_;
	}

	void clear() {
		events_.clear();
	}

	static constexpr std::size_t npos = static_cast<std::size_t>(-1);

private:
	std::vector<sort_event<T>> events_;
};

} // namespace algorithm_sorting
