# Site Runtime Bridge

This folder contains the C++ to WebAssembly bridge used by the static demo page.

The page layer consumes the generated runtime from `site/app.js`. Files in this
folder are maintained as part of the C++ project integration.

## Files

- `sorting_wasm.cpp`: C++ adapter exposed to JavaScript through Emscripten.
- `sorting.js`: generated Emscripten runtime committed for GitHub Pages.
- `build-wasm.sh`: local build script that regenerates `sorting.js`.

Regenerate the runtime with:

```bash
bash site/src/build-wasm.sh
```

## Browser Entry Point

```js
const module = await createSortingModule();
```

## Exported Runtime API

```js
module._sort_trace_json_alloc(algorithmId, inputPointer, size)
module._free_string(pointer)
module._malloc(bytes)
module._free(pointer)
module.HEAP32
module.UTF8ToString(pointer)
```

## Algorithm IDs

```text
0 Bubble sort
1 Selection sort
2 Insertion sort
3 Quick sort
4 Counting sort
5 Radix sort
```

## JSON Response

`_sort_trace_json_alloc` returns a pointer to a UTF-8 JSON string with this
shape:

```js
{
  algorithm: "Quick sort",
  input: [42, 7, 19],
  sorted: [7, 19, 42],
  events: [
    {
      type: "compare",
      first: 0,
      second: 1,
      state: [42, 7, 19]
    }
  ]
}
```

Event types are:

```text
compare
swap
write
done
```

For `write` events, `value` is also included.

## Maintenance Notes

- Do not edit `sorting.js` manually.
- If `sorting_wasm.cpp` changes, run `bash site/src/build-wasm.sh`.
- Commit the regenerated `site/src/sorting.js` so GitHub Pages can deploy the
  static site without installing Emscripten.
