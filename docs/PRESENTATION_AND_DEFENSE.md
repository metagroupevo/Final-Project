# Presentation and Defense Preparation

## Suggested responsibilities

1. Main dashboard, integration, and validation.
2. Road CRUD, positional insertion, and district matrix.
3. Facilities and emergency modules.
4. Dynamic utility array, pointers, and cleanup.
5. Requests, statistics, and test evidence.
6. Merge Sort, searches, Big-O, and documentation. For five members, combine roles 5 and 6.

Everyone should be able to explain one module outside their assigned area.

## 2–3 minute introduction

“Our project is the Smart City Infrastructure System, a standard C++ console application managing roads, facilities, emergency units, utilities, and citizen requests. It applies our Data Structures lectures directly. Structures keep each record's fields together. Fixed arrays demonstrate zero-based traversal, counts, capacity, right-shift insertion, and left-shift deletion. Utility Monitoring uses a runtime-sized array allocated with `new[]`, accessed through indexing and pointer arithmetic, and released using `delete[]`.

The Search and Sort Center includes manual Linear Search, iterative Binary Search, and recursive Merge Sort. Every binary search first sorts by ID so its prerequisite remains correct even after another ordering. The road module also contains a fixed symmetric district matrix processed with nested loops. Statistics are calculated from live records, and line-based validation handles invalid numbers, duplicate IDs, empty values, and full arrays.

We intentionally avoided GUI, databases, STL containers, and built-in algorithms so the operations taught in class remain visible and explainable.”

## 8–10 minute demonstration

1. Show dashboard and select a small utility capacity.
2. Display empty roads, then add IDs 10 and 30.
3. Insert ID 20 in position 2 to demonstrate right shifting.
4. Update through a pointer, then delete ID 20 to demonstrate left shifting.
5. Add and display a utility; explain its address, `*(pointer+i)`, count, and capacity. Attempt one beyond capacity.
6. Add emergency units and requests with different statuses.
7. Set two matrix connections, display symmetry, and count rows.
8. Run reverse-order Merge Sort, Linear Search, name/status sorts, then Binary Search to show automatic ID re-sort.
9. Display statistics and relate counts to entered data.
10. Exit and point out `delete[]`/`nullptr` cleanup.

## 5–7 minute code walkthrough

1. `models.h`: structures, fixed arrays, utility pointer, counts/capacity, matrix.
2. `input.cpp`: `getline`, `stringstream`, ranges, required strings, choices.
3. `modules.cpp`: right shift, left shift, address/dereference, pointer arithmetic, nested matrix loops.
4. `search.cpp`: base case, midpoint, recursive halves, merge loops, temporary `new[]`/`delete[]`, `low/high/mid` search.
5. `main.cpp`: validated allocation, dashboard routing, cleanup.

## Likely defense questions

**Why have count and capacity?** Count is occupied records; capacity is available slots. Valid indices end at `count - 1`.

**How does insertion shift right?** Starting at count, copy each element from its left neighbor while moving backward to the selected position. Moving backward prevents overwriting unread records.

**Why is deletion O(n)?** Finding the ID and shifting later elements may each inspect most records.

**What do `&` and `*` mean?** `&` obtains an address; `*` follows that address to the stored object. `->` dereferences and selects a field.

**Is `array[i]` different from `*(array+i)`?** They access the same element. Pointer arithmetic scales by the element type's size.

**Why doesn't a dynamic array grow automatically?** `new[]` chooses capacity at runtime, but it reserves one fixed block. Growing requires allocating another block and copying; this project demonstrates the fixed-capacity behavior required by the lesson.

**Why use `delete[]` instead of `delete`?** The allocation used `new[]`, so all array elements must be destroyed and the array block released with the matching `delete[]`.

**What is a leak or dangling pointer?** A leak is allocated memory that is never released. A pointer becomes dangling after release; accessing it is invalid. Setting it to `nullptr` clearly marks no valid target.

**What is Merge Sort's base case?** A section with zero or one element (`left >= right`) is already sorted.

**Why move complete records?** Moving only IDs would detach IDs from their names and statuses. Merge Sort copies whole structures.

**What is Merge Sort's complexity?** O(n log n) time and O(n) auxiliary memory for temporary arrays, plus O(log n) recursion depth.

**Why sort before Binary Search?** Its half-discard decisions require ordered IDs. Name/status sorting could break that order, so each binary search restores it.

**Is the complete binary-search action O(log n)?** No. Search is O(log n), but sorting first is O(n log n), which dominates the full action.

**Why is matrix traversal O(D²)?** D rows each contain D columns. One row alone is O(D).

**What is row-major storage?** C++ stores one entire row's elements next to each other, followed by the next row.

**How is invalid input prevented from skipping prompts?** Every value is first read as a complete line. Numeric parsing accepts it only when the entire line is a valid in-range number.
