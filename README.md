# Algorithm Sorting Library

A small C++ library of sorting algorithms and related helpers, built by hand as
a learning exercise. Kept here as a legacy project.

> Note: identifiers and comments in the source are in Spanish. The project has
> not been translated.

## Contents

Everything lives under three namespaces (headers in `include/`):

### `Sorting`
- `counting_sort` — for `int` / `long long` vectors (with `max`, or `max` + `min`
  range), plus template overloads for `vector<pair<key, T>>`.
- `radix_sort` — for `int` / `long long` vectors.
- `selection_sort<T>`, `bubble_sort<T>` — in place, on `vector<T>`.
- `insertion_sort<T>` — on `list<T>`, returns a new sorted list.
- `quick_sort<T>` — **not implemented** (the body is stubbed out; calling it is
  currently a no-op).

### `Analytics`
- `binary_search` — returns the index of the first occurrence of a value in a
  sorted `int` vector.

### `Pointwise`
Vector utilities used by the sorting routines:
- `add_Acumulate` — in-place prefix sum.
- `add_Scalar`, `mul_Scalar` — add/multiply every element by a scalar.
- `get_cif` — extract the digit at a given power of ten.
- `show` — print a `vector` or `list`.

## Build

Requires a C++17 compiler (`g++` or `clang++`) and `make`.

```bash
make
```

This produces:
- `build/libsorting.a` — the static library.
- `build/demo` — a small demo program (from `examples/main.cpp`).

Run the demo:

```bash
./build/demo
```

`make clean` removes the `build/` directory.

## Using the library

Include the headers and link against the static library:

```bash
g++ -std=c++17 -Iinclude your_program.cpp -Lbuild -lsorting -o your_program
```

## License

MIT License — see [LICENSE](LICENSE).
