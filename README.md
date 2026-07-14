# Algorithm Sorting Library

A small header-only C++ library with classic sorting algorithms, binary search,
and supporting utilities. Requires C++17 or newer.

**Live demo:** [mrcodecx.github.io/algorithm_sorting_lib](https://mrcodecx.github.io/algorithm_sorting_lib/)

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
- Bubble sort, selection sort, insertion sort, and quick sort for `std::vector<T>`.
- Sorting functions return sorted vectors and leave the input unchanged.
- Binary search returning the first matching index as `std::optional<std::size_t>`.
- Optional typed tracing support for visualization or WebAssembly demos.
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
#include "algorithm_sorting/tracing.hpp"
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

Tracing can be enabled when a caller needs execution events for visualization:

```cpp
#include "algorithm_sorting/sorting/bubble_sort.hpp"
#include "algorithm_sorting/tracing.hpp"

#include <vector>

int main() {
	std::vector<int> values = { 4, 2, 3, 1 };
	algorithm_sorting::sort_trace<int> trace;

	algorithm_sorting::bubble_sort(values, trace);

	const auto& events = trace.events();
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

## WebAssembly Demo

The `site/` folder contains a static portfolio demo for the library. It compiles
the C++ sorting code to WebAssembly, runs the selected algorithm in the browser,
and replays the emitted trace events as a bar visualization.

Build the WebAssembly files with Emscripten:

```bash
bash site/src/build-wasm.sh
```

The script writes:

```text
site/src/sorting.js
```

The generated file is committed so GitHub Pages can publish the static site
without installing Emscripten on every deployment. The build uses Emscripten's
single-file output so the WebAssembly payload is embedded in `sorting.js`.

GitHub Pages is deployed from `site/` using the minimal workflow in
`.github/workflows/pages.yml`. The workflow only uploads and publishes the
static site folder.

## Project Structure

```text
.
|-- CMakeLists.txt
|-- .github
|   `-- workflows
|       `-- pages.yml
|-- include
|   `-- algorithm_sorting
|       |-- algorithm_sorting.hpp
|       |-- analytics.hpp
|       |-- sorting.hpp
|       |-- tracing.hpp
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
|       |-- tracing
|       |   |-- sort_event.hpp
|       |   `-- sort_trace.hpp
|       `-- utils
|           |-- io.hpp
|           `-- pointwise.hpp
|-- tests
|   `-- test.cpp
|-- site
|   |-- app.js
|   |-- favicon.svg
|   |-- index.html
|   |-- style.css
|   `-- src
|       |-- build-wasm.sh
|       |-- sorting.js
|       `-- sorting_wasm.cpp
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

Tracing is optional. The normal sorting overloads do not call a tracer. Traced
overloads use a shared internal implementation with compile-time branching, so
the non-tracing path stays separate from per-step event emission.

Trace events are typed with the sorted value type. For example,
`sort_trace<int>` stores `sort_event<int>` values, and `sort_trace<std::string>`
can be used with traced string sorting.

## License

MIT License. See [LICENSE](LICENSE).
