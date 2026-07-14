#include "algorithm_sorting/sorting/bubble_sort.hpp"
#include "algorithm_sorting/sorting/counting_sort.hpp"
#include "algorithm_sorting/sorting/insertion_sort.hpp"
#include "algorithm_sorting/sorting/quick_sort.hpp"
#include "algorithm_sorting/sorting/radix_sort.hpp"
#include "algorithm_sorting/sorting/selection_sort.hpp"
#include "algorithm_sorting/tracing.hpp"

#include <cstddef>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#define WASM_EXPORT extern "C" EMSCRIPTEN_KEEPALIVE
#else
#define WASM_EXPORT extern "C"
#endif

namespace {

enum class sort_algorithm {
	bubble = 0,
	selection = 1,
	insertion = 2,
	quick = 3,
	counting = 4,
	radix = 5
};

std::string event_type_to_string(algorithm_sorting::sort_event_type type) {
	switch (type) {
	case algorithm_sorting::sort_event_type::compare:
		return "compare";
	case algorithm_sorting::sort_event_type::swap:
		return "swap";
	case algorithm_sorting::sort_event_type::write:
		return "write";
	case algorithm_sorting::sort_event_type::done:
		return "done";
	}
	return "unknown";
}

std::string algorithm_name(sort_algorithm algorithm) {
	switch (algorithm) {
	case sort_algorithm::bubble:
		return "Bubble sort";
	case sort_algorithm::selection:
		return "Selection sort";
	case sort_algorithm::insertion:
		return "Insertion sort";
	case sort_algorithm::quick:
		return "Quick sort";
	case sort_algorithm::counting:
		return "Counting sort";
	case sort_algorithm::radix:
		return "Radix sort";
	}
	return "Unknown";
}

std::vector<int> run_sort(sort_algorithm algorithm, const std::vector<int>& values, algorithm_sorting::sort_trace<int>& trace) {
	switch (algorithm) {
	case sort_algorithm::bubble:
		return algorithm_sorting::bubble_sort(values, trace);
	case sort_algorithm::selection:
		return algorithm_sorting::selection_sort(values, trace);
	case sort_algorithm::insertion:
		return algorithm_sorting::insertion_sort(values, trace);
	case sort_algorithm::quick:
		return algorithm_sorting::quick_sort(values, trace);
	case sort_algorithm::counting:
		return algorithm_sorting::counting_sort(values, trace);
	case sort_algorithm::radix:
		return algorithm_sorting::radix_sort(values, trace);
	}

	trace.on_done();
	return values;
}

void write_int_array(std::ostringstream& output, const std::vector<int>& values) {
	output << "[";
	for (std::size_t i = 0; i < values.size(); ++i) {
		if (i > 0) {
			output << ",";
		}
		output << values[i];
	}
	output << "]";
}

std::string sort_trace_json(int algorithm_id, const int* data, int size) {
	sort_algorithm algorithm = sort_algorithm::bubble;
	if (algorithm_id >= static_cast<int>(sort_algorithm::bubble) && algorithm_id <= static_cast<int>(sort_algorithm::radix)) {
		algorithm = static_cast<sort_algorithm>(algorithm_id);
	}

	std::vector<int> values;
	if (data != nullptr && size > 0) {
		values.assign(data, data + size);
	}

	algorithm_sorting::sort_trace<int> trace;
	std::vector<int> sorted = run_sort(algorithm, values, trace);
	std::vector<int> replay = values;

	std::ostringstream output;
	output << "{\"algorithm\":\"" << algorithm_name(algorithm) << "\",\"input\":";
	write_int_array(output, values);
	output << ",\"sorted\":";
	write_int_array(output, sorted);
	output << ",\"events\":[";
	const auto& events = trace.events();
	for (std::size_t i = 0; i < events.size(); ++i) {
		const auto& event = events[i];
		if (i > 0) {
			output << ",";
		}

		if (event.type == algorithm_sorting::sort_event_type::swap
			&& event.first < replay.size()
			&& event.second < replay.size()) {
			std::swap(replay[event.first], replay[event.second]);
		} else if (event.type == algorithm_sorting::sort_event_type::write
			&& event.first < replay.size()
			&& event.value.has_value()) {
			replay[event.first] = event.value.value();
		} else if (event.type == algorithm_sorting::sort_event_type::done) {
			replay = sorted;
		}

		output << "{\"type\":\"" << event_type_to_string(event.type) << "\"";
		if (event.first != algorithm_sorting::sort_trace<int>::npos) {
			output << ",\"first\":" << event.first;
		}
		if (event.second != algorithm_sorting::sort_trace<int>::npos) {
			output << ",\"second\":" << event.second;
		}
		if (event.value.has_value()) {
			output << ",\"value\":" << event.value.value();
		}
		output << ",\"state\":";
		write_int_array(output, replay);
		output << "}";
	}
	output << "]}";
	return output.str();
}

} // namespace

WASM_EXPORT char* sort_trace_json_alloc(int algorithm_id, const int* data, int size) {
	std::string json = sort_trace_json(algorithm_id, data, size);
	char* buffer = static_cast<char*>(std::malloc(json.size() + 1));
	if (buffer == nullptr) {
		return nullptr;
	}

	for (std::size_t i = 0; i < json.size(); ++i) {
		buffer[i] = json[i];
	}
	buffer[json.size()] = '\0';
	return buffer;
}

WASM_EXPORT char* bubble_sort_trace_json_alloc(const int* data, int size) {
	std::string json = sort_trace_json(static_cast<int>(sort_algorithm::bubble), data, size);
	char* buffer = static_cast<char*>(std::malloc(json.size() + 1));
	if (buffer == nullptr) {
		return nullptr;
	}

	for (std::size_t i = 0; i < json.size(); ++i) {
		buffer[i] = json[i];
	}
	buffer[json.size()] = '\0';
	return buffer;
}

WASM_EXPORT void free_string(char* value) {
	std::free(value);
}
