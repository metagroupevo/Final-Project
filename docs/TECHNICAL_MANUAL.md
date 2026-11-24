# Technical Manual

## Description and objectives

The **Smart City Infrastructure System** is a menu-driven C++ application that manages roads, facilities, emergency units, utilities, and citizen requests while visibly demonstrating course data structures and algorithms.

Objectives:

1. Represent related city fields with structures and arrays.
2. demonstrate zero-based traversal, right-shift insertion, left-shift deletion, and record counts.
3. Apply pointers, dynamic allocation, manual searching, Merge Sort, and memory cleanup safely.
4. Model two-way district connectivity with a stable symmetric matrix.
5. Validate inputs and calculate current statistics through loops.

## Data structures and algorithms

Four modules use fixed arrays of capacity 100. Utilities use `Utility* utilities = new Utility[capacity]`, where capacity is selected and validated at runtime. Count means occupied elements; capacity means allocated slots. A dynamic allocation does not grow automatically.

Road insertion accepts a logical position, shifts elements from the end toward that position, assigns the record, then increments count. Deletion finds an ID and shifts later records left. Searches and sorts are manually implemented without STL algorithms or containers.

## Pointer and memory explanation

`&record` produces its address. A pointer stores that address. `*pointer` dereferences it, while `pointer->field` is a convenient form of `(*pointer).field`. For arrays, `utilities[i]` and `*(utilities + i)` mean the same element. Pointer arithmetic automatically advances by `sizeof(Utility)`, not one byte.

`new` allocates one object and pairs with `delete`; `new[]` allocates an array and pairs with `delete[]`. Mixing the forms is undefined behavior. Not releasing allocated memory causes a memory leak. Accessing an address after release is invalid because it is dangling. The program calls `delete[]`, immediately sets pointers to `nullptr`, and never accesses them afterward. Merge Sort treats every temporary array the same way.

## Matrix explanation

Row and column indices 0–4 identify stable named districts. A cell contains 0 for no direct connection and 1 for a connection. Nested loops traverse each row and then each column, matching row-major storage: all cells of one row are contiguous before the next row. Diagonal connections are rejected and two symmetric cells are changed together.

## Validation

All input begins with `getline`, so names and locations can contain spaces and no newline is accidentally skipped. `stringstream` accepts a number only when the complete line is numeric. Menus, IDs, capacities, and percentages have ranges. Required text, enum choices, duplicates, full arrays, empty arrays, and missing IDs are checked before mutation.

## Suggested example challenges to adapt

These are examples, not claims about the group's experience:

1. **Example—binary search failed after name sorting:** sort by ID immediately before every binary search.
2. **Example—record fields separated during sorting:** copy and merge complete structures rather than individual IDs.
3. **Example—memory leak in Merge Sort:** pair each temporary `new[]` with `delete[]` and set the released pointer to `nullptr`.
4. **Example—matrix labels changed after road deletion:** keep district identifiers separate from road-array indices.

## Conclusion

The project emphasizes visible lecture methods over shortcuts. Students can trace each index, shift, pointer expression, recursive division, merge, matrix cell, and complexity directly in the source.
