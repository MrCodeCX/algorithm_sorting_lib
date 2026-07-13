# Algorithm Sorting Library

A small header-only C++ library with classic sorting algorithms, binary search,
and supporting utilities. Requires C++17 or newer.

## About

This project implements a compact set of algorithms using templates and standard
C++ containers. It is organized as a reusable header-only library with a CMake
target and a small test suite.

The public API is namespaced under `algorithm_sorting`. The main algorithms can
be included as a full module or individually by header.

## Features

- Header-only C++ library requiring C++17 or newer.
- CMake `INTERFACE` target for easy integration.
- Stable counting sort for integral vectors.
- Counting sort by integral key for `std::vector<std::pair<Key, T>>`.
- Byte-based radix sort for signed and unsigned integral types.
- Bubble sort and selection sort for `std::vector<T>`.
- Insertion sort and quick sort for `std::list<T>`.
- Binary search returning the first matching index.
- Utility helpers kept separate from the core sorting headers.
- Tests with CTest.

## Using the Library

Because the project is header-only, there is no library binary to build or link.
Include the headers and compile your program with the `include/` directory in
the include path.

Include the full library:

```cpp
#include "algorithm_sorting/algorithm_sorting.hpp"
```

Or include only the module you need:

```cpp
#include "algorithm_sorting/sorting.hpp"
#include "algorithm_sorting/analytics.hpp"
#include "algorithm_sorting/utils.hpp"
```

You can also include a single algorithm:

```cpp
#include "algorithm_sorting/sorting/radix_sort.hpp"
```

Example:

```cpp
#include "algorithm_sorting/sorting/radix_sort.hpp"

#include <vector>

int main() {
	std::vector<int> values = { 5, -1, 3, 0 };
	auto sorted = algorithm_sorting::radix_sort(values);
}
```

Compile directly:

```bash
g++ -std=c++17 -Iinclude your_program.cpp -o your_program
```

## Running Tests

Configure, build, and run the tests:

```bash
cmake -S . -B build-cmake
cmake --build build-cmake
ctest --test-dir build-cmake
```

CMake is only needed for building and running this repository's test suite. It
exposes the `algorithm_sorting` interface target for CMake-based consumers.

## Project Structure

```text
.
|-- CMakeLists.txt
|-- include
|   `-- algorithm_sorting
|       |-- algorithm_sorting.hpp
|       |-- analytics.hpp
|       |-- sorting.hpp
|       |-- utils.hpp
|       |-- analytics
|       |   `-- binary_search.hpp
|       |-- detail
|       |   `-- sorting.hpp
|       |-- sorting
|       |   |-- bubble_sort.hpp
|       |   |-- counting_sort.hpp
|       |   |-- insertion_sort.hpp
|       |   |-- quick_sort.hpp
|       |   |-- radix_sort.hpp
|       |   `-- selection_sort.hpp
|       `-- utils
|           |-- io.hpp
|           `-- pointwise.hpp
|-- tests
|   `-- test.cpp
|-- README.md
`-- LICENSE
```

## Technical Notes

Most functions are templates, so their implementations live in headers. The
`detail` directory contains implementation helpers that are not intended as
public API.

`utils/io.hpp` is separate from the algorithm headers so environments that do
not need stream output, such as a future WebAssembly demo, can avoid including
I/O-related code.

## License

MIT License. See [LICENSE](LICENSE).
