#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
OUTPUT_DIR="$ROOT_DIR/site/wasm"

mkdir -p "$OUTPUT_DIR"

em++ "$ROOT_DIR/site/src/sorting_wasm.cpp" \
	-std=c++17 \
	-O2 \
	-I"$ROOT_DIR/include" \
	-sMODULARIZE=1 \
	-sEXPORT_NAME=createSortingModule \
	-sENVIRONMENT=web \
	-sSINGLE_FILE=1 \
	-sALLOW_MEMORY_GROWTH=1 \
	-sEXPORTED_FUNCTIONS='["_sort_trace_json_alloc","_bubble_sort_trace_json_alloc","_free_string","_malloc","_free"]' \
	-sEXPORTED_RUNTIME_METHODS='["ccall","cwrap","HEAP32","UTF8ToString"]' \
	-o "$OUTPUT_DIR/sorting.js"
