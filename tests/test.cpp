#include "algorithm_sorting/analytics.hpp"
#include "algorithm_sorting/sorting.hpp"
#include "algorithm_sorting/tracing.hpp"
#include "algorithm_sorting/utils.hpp"

#include <cassert>
#include <functional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int main() {
	std::vector<int> values = { 5, 1, 3, 3, 2 };
	std::vector<int> expected = { 1, 2, 3, 3, 5 };

	assert(algorithm_sorting::bubble_sort(values) == expected);
	assert(algorithm_sorting::selection_sort(values) == expected);
	assert(algorithm_sorting::insertion_sort(values) == expected);
	assert(algorithm_sorting::quick_sort(values) == expected);
	assert(values == (std::vector<int>{ 5, 1, 3, 3, 2 }));

	algorithm_sorting::sort_trace<int> bubble_trace;
	assert(algorithm_sorting::bubble_sort(values, bubble_trace) == expected);
	assert(!bubble_trace.events().empty());
	assert(bubble_trace.events().back().type == algorithm_sorting::sort_event_type::done);

	algorithm_sorting::sort_trace<int> selection_trace;
	assert(algorithm_sorting::selection_sort(values, selection_trace) == expected);
	assert(!selection_trace.events().empty());
	assert(selection_trace.events().back().type == algorithm_sorting::sort_event_type::done);

	algorithm_sorting::sort_trace<int> insertion_trace;
	assert(algorithm_sorting::insertion_sort(values, insertion_trace) == expected);
	assert(!insertion_trace.events().empty());
	assert(insertion_trace.events().back().type == algorithm_sorting::sort_event_type::done);

	algorithm_sorting::sort_trace<int> quick_trace;
	assert(algorithm_sorting::quick_sort(values, quick_trace) == expected);
	assert(!quick_trace.events().empty());
	assert(quick_trace.events().back().type == algorithm_sorting::sort_event_type::done);

	std::vector<std::string> words = { "delta", "alpha", "charlie", "bravo" };
	std::vector<std::string> sorted_words = { "alpha", "bravo", "charlie", "delta" };
	assert(algorithm_sorting::selection_sort(words) == sorted_words);

	algorithm_sorting::sort_trace<std::string> string_trace;
	assert(algorithm_sorting::selection_sort(words, string_trace) == sorted_words);
	assert(!string_trace.events().empty());

	assert(algorithm_sorting::bubble_sort(values, std::greater<int>{}) == (std::vector<int>{ 5, 3, 3, 2, 1 }));
	algorithm_sorting::sort_trace<int> descending_trace;
	assert(algorithm_sorting::bubble_sort(values, descending_trace, std::greater<int>{}) == (std::vector<int>{ 5, 3, 3, 2, 1 }));

	assert(algorithm_sorting::counting_sort(values) == expected);
	assert(algorithm_sorting::counting_sort_with_max(values, 5) == expected);

	algorithm_sorting::sort_trace<int> counting_trace;
	assert(algorithm_sorting::counting_sort(values, counting_trace) == expected);
	assert(!counting_trace.events().empty());
	assert(counting_trace.events().back().type == algorithm_sorting::sort_event_type::done);

	std::vector<int> ranged_values = { -3, 5, 0, -3, 2 };
	std::vector<int> ranged_expected = { -3, -3, 0, 2, 5 };
	assert(algorithm_sorting::counting_sort(ranged_values) == ranged_expected);
	assert(algorithm_sorting::counting_sort(ranged_values, -3, 5) == ranged_expected);

	std::vector<long long> long_values = { 9LL, -1LL, 4LL, 4LL, 0LL };
	std::vector<long long> long_expected = { -1LL, 0LL, 4LL, 4LL, 9LL };
	assert(algorithm_sorting::counting_sort(long_values) == long_expected);
	assert(algorithm_sorting::radix_sort(long_values) == long_expected);

	algorithm_sorting::sort_trace<long long> radix_trace;
	assert(algorithm_sorting::radix_sort(long_values, radix_trace) == long_expected);
	assert(!radix_trace.events().empty());
	assert(radix_trace.events().back().type == algorithm_sorting::sort_event_type::done);

	std::vector<unsigned int> unsigned_values = { 3u, 0u, 2u, 1u };
	assert(algorithm_sorting::counting_sort(unsigned_values) == (std::vector<unsigned int>{ 0u, 1u, 2u, 3u }));
	assert(algorithm_sorting::radix_sort(unsigned_values) == (std::vector<unsigned int>{ 0u, 1u, 2u, 3u }));

	std::vector<std::pair<int, char>> keyed = { { 2, 'b' }, { 1, 'a' }, { 2, 'c' } };
	std::vector<std::pair<int, char>> keyed_expected = { { 1, 'a' }, { 2, 'b' }, { 2, 'c' } };
	assert(algorithm_sorting::counting_sort_by_key(keyed) == keyed_expected);

	algorithm_sorting::sort_trace<std::pair<int, char>> keyed_trace;
	assert(algorithm_sorting::counting_sort_by_key(keyed, keyed_trace) == keyed_expected);
	assert(!keyed_trace.events().empty());
	assert(keyed_trace.events().back().type == algorithm_sorting::sort_event_type::done);

	std::vector<int> search_values = { 1, 2, 3, 3, 5 };
	assert(algorithm_sorting::binary_search_first(search_values, 3).value() == 2);
	assert(!algorithm_sorting::binary_search_first(search_values, 4).has_value());
	assert(!algorithm_sorting::binary_search_first(std::vector<int>{}, 4).has_value());

	std::vector<int> pointwise_values = { 1, 2, 3 };
	algorithm_sorting::utils::prefix_sum(pointwise_values);
	assert((pointwise_values == std::vector<int>{ 1, 3, 6 }));
	algorithm_sorting::utils::add_scalar(pointwise_values, 1);
	assert((pointwise_values == std::vector<int>{ 2, 4, 7 }));
	algorithm_sorting::utils::multiply_scalar(pointwise_values, 2);
	assert((pointwise_values == std::vector<int>{ 4, 8, 14 }));
	assert(algorithm_sorting::utils::digit_at(1234, 2) == 2);

	std::ostringstream output;
	algorithm_sorting::utils::print(pointwise_values, output);
	assert(output.str() == "4 8 14 \n");

	return 0;
}
