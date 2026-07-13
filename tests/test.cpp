#include "algorithm_sorting/analytics.hpp"
#include "algorithm_sorting/sorting.hpp"
#include "algorithm_sorting/utils.hpp"

#include <cassert>
#include <functional>
#include <sstream>
#include <string>

int main() {
	std::vector<int> values = { 5, 1, 3, 3, 2 };
	std::vector<int> expected = { 1, 2, 3, 3, 5 };

	std::vector<int> bubble_values = values;
	algorithm_sorting::bubble_sort(bubble_values);
	assert(bubble_values == expected);

	std::vector<int> selection_values = values;
	algorithm_sorting::selection_sort(selection_values);
	assert(selection_values == expected);

	std::vector<std::string> words = { "delta", "alpha", "charlie", "bravo" };
	algorithm_sorting::selection_sort(words);
	assert((words == std::vector<std::string>{ "alpha", "bravo", "charlie", "delta" }));

	std::vector<int> descending = values;
	algorithm_sorting::bubble_sort(descending, std::greater<int>{});
	assert((descending == std::vector<int>{ 5, 3, 3, 2, 1 }));

	assert(algorithm_sorting::counting_sort(values) == expected);
	assert(algorithm_sorting::counting_sort_with_max(values, 5) == expected);

	std::vector<int> ranged_values = { -3, 5, 0, -3, 2 };
	std::vector<int> ranged_expected = { -3, -3, 0, 2, 5 };
	assert(algorithm_sorting::counting_sort(ranged_values) == ranged_expected);
	assert(algorithm_sorting::counting_sort(ranged_values, -3, 5) == ranged_expected);

	std::vector<long long> long_values = { 9LL, -1LL, 4LL, 4LL, 0LL };
	std::vector<long long> long_expected = { -1LL, 0LL, 4LL, 4LL, 9LL };
	assert(algorithm_sorting::counting_sort(long_values) == long_expected);
	assert(algorithm_sorting::radix_sort(long_values) == long_expected);

	std::vector<std::pair<int, char>> keyed = { {2, 'b'}, {1, 'a'}, {2, 'c'} };
	std::vector<std::pair<int, char>> keyed_expected = { {1, 'a'}, {2, 'b'}, {2, 'c'} };
	assert(algorithm_sorting::counting_sort_by_key(keyed) == keyed_expected);

	std::list<int> list_values = { 5, 1, 3, 3, 2 };
	std::list<int> list_expected = { 1, 2, 3, 3, 5 };
	assert(algorithm_sorting::insertion_sort(list_values) == list_expected);

	algorithm_sorting::quick_sort(list_values);
	assert(list_values == list_expected);

	std::vector<int> search_values = { 1, 2, 3, 3, 5 };
	assert(algorithm_sorting::binary_search_first(search_values, 3) == 2);
	assert(algorithm_sorting::binary_search_first(search_values, 4) == -1);
	assert(algorithm_sorting::binary_search_first(std::vector<int>{}, 4) == -1);

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
