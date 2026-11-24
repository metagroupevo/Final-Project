# Big-O Analysis

Let `n` be a module's record count and `D` the district count.

| Actual operation | Time | Auxiliary space | Reason |
|---|---:|---:|---|
| Direct `array[i]` or `*(array+i)` | O(1) | O(1) | Address calculated directly |
| Full traversal/display | O(n) | O(1) | Visits each valid record |
| Add at end after duplicate check | O(n) | O(1) | ID scan dominates assignment |
| Road positional insertion | O(n) | O(1) | Duplicate scan plus right shifting |
| Delete | O(n) | O(1) | ID search plus left shifting |
| Update | O(n) | O(1) | ID search, then O(1) replacement |
| Linear Search | O(n) | O(1) | Sequential comparisons |
| Binary Search on sorted records | O(log n) | O(1) | Iterative range halving |
| Merge Sort | O(n log n) | O(n) | Recursive halves and temporary arrays |
| Binary-search menu workflow | O(n log n) | O(n) | Sort first, then O(log n) search |
| One matrix row count | O(D) | O(1) | Visits one row |
| Full matrix display/all row counts | O(D²) | O(1) | Visits D by D cells |
| Statistics | O(R + E + Q) | O(1) | Traverses relevant live arrays |

Merge Sort's base case is `left >= right`: zero or one record is already sorted. Otherwise it calculates the midpoint, recursively sorts both halves, and merges them. Temporary left/right arrays preserve complete records, not isolated fields. Each merge calls `delete[]` and sets its temporary pointers to `nullptr`.

Binary Search uses `low`, `high`, and `mid = low + (high - low) / 2`. Its search is O(log n), but the application deliberately re-sorts by ID first so a previous name/status sort cannot invalidate its prerequisite. The complete action is therefore O(n log n), not O(log n).
